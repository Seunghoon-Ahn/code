#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>

int ssu_daemon_init(void);

int main(void)
{
	printf("daemon process initialization\n");
	
	if(ssu_daemon_init() < 0) { //디몬 프로세스를 생성하는 함수 호출
		fprintf(stderr, "ssu_daemon_init failed\n");
		exit(1);
	} //실패시 오류 출력 후 프로그램 종료
	
	while(1) {
		openlog("lpd", LOG_PID, LOG_LPR);//syslog를 위한 환경 초기화
		syslog(LOG_ERR, "ope failed lpd %m"); //에러 상태 출력
		closelog();
		sleep(5);
	} //디몬 프로세스가 5초 마다 로그를 남기게 설정함
	exit(0);
}

int ssu_daemon_init(void) {
	pid_t pid;
	int fd, maxfd;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} //fork를 통해 자식 프로세스 생성, 실패시 에러 출력 후 종료
	else if (pid != 0)
		exit(0); //부모프로세스는 종료함
	
	pid = getpid(); // 현재 프로세스의 ID를 가져옴
	printf("process %d running as daemon\n", pid); //현재 프로세스 번호 출력
	setsid(); //디몬 프로세스를 새로운 세션 리더로 설정
	signal(SIGTTIN, SIG_IGN);//백그라운드가 터미널을 읽을때 나오는 시그널 무시
	signal(SIGTTOU, SIG_IGN);//백그라운드가 터미널에 쓸때 나오는 시그널 무시
	signal(SIGTSTP, SIG_IGN);//사용자가 ctrl+Z를 눌렀을때 나오는 시그널 무시
	maxfd = getdtablesize(); //프로세스의 최대 소켓 수를 확인

	for(fd = 0; fd < maxfd; fd++)
		close(fd); //현재 열려있는 모든 파일 디스크립터를 종료함

	umask(0); //uamsk를 0으로 설정
	chdir("/"); //작업디렉토리를 루트로 설정
	fd = open("/dev/null", O_RDWR); //표준입출력, 에러를 재지정함
	dup(0); //표준 출력 재지정
	dup(0); //표준 에러 재지정
	return 0;
}

