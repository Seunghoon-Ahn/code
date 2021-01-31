#include <stdio.h>
#include <stdlib.h>

struct ssu_id {
	char name[64];
	int id;
};

int main(void)
{
	struct ssu_id test1, test2;
	char *fname = "ssu_exam.dat";
	FILE *fp;

	if((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	} //파일을 쓰기모드로 오픈함, 파일이 없으면 생성함, 오픈 실패 시 에러 출력

	printf("Input ID>> ");
	scanf("%d", &test1.id);//id를 입력받음
	printf("Input name>> ");
	scanf("%s", test1.name); //이름을 입력받음

	if(fwrite(&test1, sizeof(struct ssu_id), 1, fp) != 1) {
		fprintf(stderr, "fwrite error\n");
		exit(1);
	} //파일에 구조체에 담긴 이름과 ID를 씀
	//fwrite 함수를 이용해 구조체의 크기 1개만큼 파일에 씀
	fclose(fp); //파일 저장

	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	} //파일을 읽기 모드로 오픈함, 파일이 있어야 함, 오픈 실패 시 에러 출력

	if(fread(&test2, sizeof(struct ssu_id), 1, fp) != 1) {
		fprintf(stderr, "fread error\n");
		exit(1);
	} //test2 구조체에 파일에서 읽어온 정보를 저장
	//파일에서 구조체를 읽어서 tsst2구조체에 저장
	printf("\nID    name\n");
	printf("=============\n");
	printf("%d      %s\n", test2.id, test2.name); //저장된 데이터 출력
	fclose(fp); //파일을 닫음
	exit(0); //프로그램 종료
}

