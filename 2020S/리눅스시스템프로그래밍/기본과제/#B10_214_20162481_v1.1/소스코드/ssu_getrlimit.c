#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#define ssu_show(limit) ssu_show_limit(limit, #limit)

void ssu_show_limit(int rlim_type, char *rlim_name);

int main(void)
{
	printf("	resource soft limit hard limit	\n\n");
	ssu_show(RLIMIT_CPU); //프로세스의 최대 CPU사용시간 출력
	ssu_show(RLIMIT_FSIZE); //파일 최대 크기 확인
	ssu_show(RLIMIT_DATA); // 자료 구역의 최대크기 확인
	ssu_show(RLIMIT_STACK); //스택의 최대 크기 확인
	ssu_show(RLIMIT_CORE); //한 코어 파일의 최대크기 확인
#ifdef RLIMIT_RSS
	ssu_show(RLIMIT_RSS); //메모리 상주 세트의 최대 크기 확인
#endif
#ifdef RLIMIT_MEMLOCK
	ssu_show(RLIMIT_MEMLOCK); //한 프로세스가 mlock으로 잠글 수 있는 메모리의 최대 확인
#endif
#ifdef RLIMIT_NPROC
	ssu_show(RLIMIT_NPROC); //실제 사용자 ID 당 자식 프로세스의 갯수 확인
#endif
#ifdef RLIMIT_OFILE
	ssu_show(RLIMIT_OFILE); //한 프로세스가 열수 있는 최대 파일의 갯수 확인
#endif
#ifdef RLIMIT_NOFILE
	ssu_show(RLIMIT_NOFILE); //한 프로세스가 열 수 있는 최대 파일의 갯수 확인
#endif
#ifdef RLIMIT_VMEN
	ssu_show(RLIMIT_VMEN); //한 프로세스의 자유 메모리 최댓값 확인
#endif

	exit(0);
}

void ssu_show_limit(int rlim_type, char *rlim_name) {
	struct rlimit rlim;
	char cur[11], max[11];

	getrlimit(rlim_type, &rlim);
	if(rlim.rlim_cur == RLIM_INFINITY)
		strcpy(cur, "infinity");
	else
		sprintf(cur, "%10ld", rlim.rlim_cur);

	if(rlim.rlim_max == RLIM_INFINITY)
		strcpy(max, "infinity");
	else
		sprintf(max, "%10ld", rlim.rlim_max);
	//각 자원의 종류, 약한 한계, 강한 한계를 출력함
	printf("%15s : %10s %10s\n", rlim_name, cur, max);
}
