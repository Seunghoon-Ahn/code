#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <syslog.h>
#include <signal.h>
#include <limits.h>
#include <utime.h>

#define PATHMAX 1024
#define FILEMAX 256

void print_usage(char *str); //사용법 출력
void make_sync(void); //동기화를 진행하는 함수
int dir_check(const struct dirent *info); //scandir 필터함수
void signal_handler(int signo); //시그널 핸들러 함수
void write_log(char *fname, struct stat *statbuf); //로그 작성 함수
void ssu_runtime(struct timeval *begin_t, struct timeval *end_t); //프로그램 수행 시간 측정

char src[PATHMAX];
char dst[PATHMAX];
char command[PATHMAX];
FILE *fp;

int main(int argc, char *argv[]) 
{
	struct timeval begin_t, end_t;
	gettimeofday(&begin_t, NULL); //시작시간 저장

	struct stat statbuf;
	setbuf(stdout, NULL);
	time_t now;
	//struct tm *t;
	char timestring[FILEMAX];


	memset(src, 0, PATHMAX);
	memset(dst, 0, PATHMAX);
	memset(command, 0, PATHMAX);
	memset(timestring, 0, FILEMAX);

	if(!(argc == 3 || argc == 4)) {
		print_usage(argv[0]);
		exit(1);
	}
	//인자가 잘못들어온 경우 예외처리
	for(int i = 0; i < argc; i++) {
		strcat(command, argv[i]);
		if(i < argc-1)
			strcat(command, " ");
	}
	//main 함수 인자로 들어온 명령어를 저장해둠
	time(&now);
	sprintf(timestring, "[%s", ctime(&now));
	timestring[strlen(timestring) - 1] = '\0';
	strcat(timestring, "]");

	if((fp = fopen("ssu_rsync_log", "a+")) < 0) {
		fprintf(stderr, "fopen error\n");
		exit(1);
	}

	fprintf(fp, "%s %s\n", timestring, command); //로그 첫줄 작성

	if(argc == 3) {
		realpath(argv[1], src);
		realpath(argv[2], dst);
	}
	else if (argc == 4) {
		realpath(argv[2], src);
		realpath(argv[3], dst);
	}
	//인자로 입력받은 src dst를 절대경로로 저장

	if(signal(SIGINT, signal_handler) == SIG_ERR) {
		fprintf(stderr, "SIGINT handle error\n");
		exit(1);
	} //SIGINT 입력되면 핸들러 함수 호출해서 원래 파일로 다시 바꿈

	if(lstat(dst, &statbuf) < 0) {
		print_usage(argv[0]);
		exit(1);
	} //dst가 없는 경우 에러처리 후 종료

	if(!S_ISDIR(statbuf.st_mode) || access(dst, W_OK) || access(dst, R_OK) || access(dst, X_OK)) {
		print_usage(argv[0]);
		exit(1);
	} //dst가 디렉토리가 아니고, 쓸수 없고, 읽을수 없고 실행할 수 없으면 에러처리 후 종료

	if(lstat(src, &statbuf) < 0) {
		print_usage(argv[0]);
		exit(1);
	} //src를 찾을수 없는 경우 에러처리 후 종료

	if(access(src, W_OK) || access(src, R_OK) || (S_ISDIR(statbuf.st_mode) && access(src, X_OK))) {
		print_usage(argv[0]);
		exit(1);
	} //src가 쓸수 없고, 읽을수 없고, 실행할 수 없으면 에러처리 후 종료

	make_sync(); //동기화 함수 호출

	fclose(fp);

	gettimeofday(&end_t, NULL); //끝시간 저장
	ssu_runtime(&begin_t, &end_t); //시간계산, 끝시간 - 처음 시간

	return 0;
}

void make_sync(void) { //동기화 하는 함수
	struct dirent **namelist_src; //src가 디렉토리일때 내부 파일 목록
	struct dirent **namelist_dst; //dst의 파일 목록
	int src_count, dst_count; //src dst의 파일 갯수
	struct stat statbuf;
	struct stat src_statbuf;
	struct utimbuf timebuf;
	int index_src;
	char src_fname[FILEMAX]; //src가 파일일 때 파일 이름을 저장함
	char src_check[PATHMAX]; //src의 파일 이름을 절대 경로로 바꿔서 저장함
	char dst_check[PATHMAX]; //dst의 파일 이름을 절대 경로로 바꿔서 저장함
	char orifile_rename[PATHMAX]; //dst에 있는 이름이 같은 파일을 이름을 바꿔서 저장
	int loc, readcnt;
	int fd_sync, fd_src;
	char buf[PATHMAX]; //read_write용 버퍼
	int checksum = 0;

	memset(src_fname, 0, FILEMAX);

	for(int i = 0; i < strlen(src); i++)
		if(src[i] == '/')
			loc = i;

	strcpy(src_fname, src+loc+1); //src가 파일 이름일때 파일 이름만 추출

	if(lstat(src, &statbuf) < 0) {
		fprintf(stderr, "lstat error for %s\n", src);
		exit(1);
	}

	if(S_ISDIR(statbuf.st_mode))
		index_src = 1;
	else
		index_src = 0;
	//index_src 가 1이면 src가 디렉토리, 0이면 파일

	if(index_src) { //src가 디렉토리 일때
		if((src_count = scandir(src, &namelist_src, dir_check, alphasort)) == -1) {
			return;
		}
		if((dst_count = scandir(dst, &namelist_dst, dir_check, alphasort)) == -1) {
			return;
		}

		for(int i = 0; i < src_count; i++) { //src 디렉토리 내의 파일 갯수만큼
			checksum = 0;
			memset(src_check, 0, PATHMAX);
			strcpy(src_check, src);
			strcat(src_check, "/");
			strcat(src_check, namelist_src[i]->d_name);

			if(lstat(src_check, &src_statbuf) < 0) {
				fprintf(stderr, "lstat error2\n");
				return;
			}
			if(S_ISDIR(src_statbuf.st_mode))
				continue;
			//디렉토리면 패스

			for(int j = 0; j < dst_count; j++) { //dst 디렉토리 순회
				memset(dst_check, 0, PATHMAX);
				strcpy(dst_check, dst);
				strcat(dst_check, "/");
				strcat(dst_check, namelist_dst[j]->d_name);
				//dst의 파일을 절대경로로 만듬

				//printf("%s\n%s\n\n", src_check, dst_check);

				if(lstat(dst_check, &statbuf) < 0) {
					fprintf(stderr, "lstat error3\n");
					exit(1);
				}
				if(S_ISDIR(statbuf.st_mode))
					continue;
				//디렉토리면 패스
				
				if(!strcmp(namelist_src[i]->d_name, namelist_dst[j]->d_name)){
					checksum = 1;

					if(src_statbuf.st_size == statbuf.st_size && src_statbuf.st_mtime == statbuf.st_mtime)
						continue;
					//파일 크기가 같고 최종 수정시간이 같으면 패스

					memset(orifile_rename, 0, PATHMAX);
					strcpy(orifile_rename, dst);
					strcat(orifile_rename, "/_");
					strcat(orifile_rename, namelist_dst[j]->d_name);
					//rename할꺼 만듬

					rename(dst_check, orifile_rename);

					if((fd_sync = creat(dst_check, 0644)) < 0) {
					fprintf(stderr, "creat error\n");
					return;
					}

					if((fd_src = open(src_check, O_RDONLY)) < 0) {
						fprintf(stderr, "open error for src");
						return;
					}

					memset(buf, 0, PATHMAX);
					while((readcnt = read(fd_src, buf, PATHMAX)) > 0) {
						write(fd_sync, buf, readcnt);
						memset(buf, 0, PATHMAX);
					} //동기화 대상 파일을 읽어서 새로 만든 파일에 씀

					close(fd_sync);
					close(fd_src);

					timebuf.actime = src_statbuf.st_atime;
					timebuf.modtime = src_statbuf.st_mtime;

					if(utime(dst_check, &timebuf) < 0) {
						fprintf(stderr, "utime error for dst_check\n");
						return;
					}
					unlink(orifile_rename);
					write_log(namelist_src[i]->d_name, &src_statbuf);
					break;
				}
			}

			if(checksum == 0) { //dst에 파일이 없는 경우
				memset(dst_check, 0, PATHMAX);
				strcpy(dst_check, dst);
				strcat(dst_check, "/");
				strcat(dst_check, namelist_src[i]->d_name);
				//dst 디렉토리에 만들 파일 경로

				if((fd_sync = creat(dst_check, 0644)) < 0) {
					fprintf(stderr, "creat error\n");
					return;
				}

				if((fd_src = open(src_check, O_RDONLY)) < 0) {
					fprintf(stderr, "open error for src");
					return;
				}

				memset(buf, 0, PATHMAX);
				while((readcnt = read(fd_src, buf, PATHMAX)) > 0) {
					write(fd_sync, buf, readcnt);
					memset(buf, 0, PATHMAX);
				} //동기화 대상 파일을 읽어서 새로 만든 파일에 씀

				close(fd_sync);
				close(fd_src);

				timebuf.actime = src_statbuf.st_atime;
				timebuf.modtime = src_statbuf.st_mtime;

				if(utime(dst_check, &timebuf) < 0) {
					fprintf(stderr, "utime error for dst_check\n");
					return;
				}
				write_log(namelist_src[i]->d_name, &src_statbuf);			
			}

		}
	}
	else { //src가 파일일때
		if(lstat(src, &src_statbuf) < 0) {
			fprintf(stderr, "lstat error for src");
			return;
		}

		if((dst_count = scandir(dst, &namelist_dst, dir_check, alphasort)) == -1) {
			return;
		}

		for(int i = 0; i < dst_count; i++) { //dst 디렉토리 순회
			memset(dst_check, 0, PATHMAX);
			strcpy(dst_check, dst);
			strcat(dst_check, "/");
			strcat(dst_check, namelist_dst[i]->d_name);
			//dst 파일의 절대경로 생성
		
			if(lstat(dst_check, &statbuf) < 0) {
				fprintf(stderr, "lstat error1\n");
				return;
			}
			if(S_ISDIR(statbuf.st_mode))
				continue;
			//디렉토리일 경우 패스함
			if(!strcmp(src_fname, namelist_dst[i]->d_name)) { //파일 이름이 같은게 있는 경우
				checksum = 1;

				if(src_statbuf.st_size == statbuf.st_size && src_statbuf.st_mtime == statbuf.st_mtime)
					continue;
				//파일 크기가 같고 최종 수정시간이 같으면 패스


				memset(orifile_rename, 0, PATHMAX);
				strcpy(orifile_rename, dst);
				strcat(orifile_rename, "/_");
				strcat(orifile_rename, namelist_dst[i]->d_name);

				rename(dst_check, orifile_rename); //dst에 원래 있던 파일을 _(파일) 로 만듦

				if((fd_sync = creat(dst_check, 0644)) < 0) {
					fprintf(stderr, "creat error\n");
					return;
				}

				if((fd_src = open(src, O_RDONLY)) < 0) {
					fprintf(stderr, "open error for src");
					return;
				}

				memset(buf, 0, PATHMAX);
				while((readcnt = read(fd_src, buf, PATHMAX)) > 0) {
					write(fd_sync, buf, readcnt);
					memset(buf, 0, PATHMAX);
				} //동기화 대상 파일을 읽어서 새로 만든 파일에 씀

				close(fd_sync);
				close(fd_src);

				timebuf.actime = src_statbuf.st_atime;
				timebuf.modtime = src_statbuf.st_mtime;

				if(utime(dst_check, &timebuf) < 0) {
					fprintf(stderr, "utime error for dst_check\n");
					return;
				}

				unlink(orifile_rename);
				write_log(src_fname, &src_statbuf);
				return;
			}
		}

		if(checksum == 0) { //이름이 일치하는 파일이 없는 경우
			memset(dst_check, 0, PATHMAX);
			strcpy(dst_check, dst);
			strcat(dst_check, "/");
			strcat(dst_check, src_fname);
			//dst 디렉토리에 만들 파일 경로

			if((fd_sync = creat(dst_check, 0644)) < 0) {
				fprintf(stderr, "creat error\n");
				return;
			}

			if((fd_src = open(src, O_RDONLY)) < 0) {
				fprintf(stderr, "open error for src");
				return;
			}

			memset(buf, 0, PATHMAX);
			while((readcnt = read(fd_src, buf, PATHMAX)) > 0) {
				write(fd_sync, buf, readcnt);
				memset(buf, 0, PATHMAX);
			} //동기화 대상 파일을 읽어서 새로 만든 파일에 씀

			close(fd_sync);
			close(fd_src);

			timebuf.actime = src_statbuf.st_atime;
			timebuf.modtime = src_statbuf.st_mtime;

			if(utime(dst_check, &timebuf) < 0) {
				fprintf(stderr, "utime error for dst_check\n");
				return;
			}
			write_log(src_fname, &src_statbuf);		
		}

		return;
	}

}

void signal_handler(int signo) { //SIGINT의 핸들러 함수

}

void write_log(char *fname, struct stat *statbuf) {
	fprintf(fp, "    %s %ldbytes\n", fname, statbuf->st_size);
	return;
} //로그를 작성하는 함수

int dir_check(const struct dirent *info) {
	if(!strncmp(info->d_name, ".", 1))
		return 0;
	else 
		return 1;
} //scandir 필터함수

void print_usage(char *str) {
	printf("Usage : %s <option> <src file or directory> <dst directory>\n", str);
	printf("  <option>\n");
	printf("	-r : Make sync <src>'s sub directory\n");
	printf("	-t : Make sync with .tar file\n");
	printf("	-m : Delete <dst>'s files that not exist in <src>\n");
	return;
} //사용법 출력 함수

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t)
{ //프로그램 수행시간 측정
	end_t->tv_sec -= begin_t->tv_sec; //끝난 시간에서 처음시간을 뺌

	if(end_t->tv_usec < begin_t->tv_usec){
		end_t->tv_sec--;
		end_t->tv_usec += 1000000;
	} //나중의 us값이 작을경우 1초를 뺴서 us값이 더해줌

	end_t->tv_usec -= begin_t->tv_usec;
	printf("Runtime: %ld:%06ld(sec:usec)\n", end_t->tv_sec, end_t->tv_usec);
} //프로그램 총 소요시간 계산 후 출력하는 함수
