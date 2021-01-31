#include <stdio.h>
#include <stdlib.h>

struct ssu_pirate {
	unsigned long booty;
	unsigned int beard_length;
	char name[128];
};

int main(void)
{
	struct ssu_pirate blackbeard = {950, 48, "Edward Teach"}, pirate;
	char *fname = "ssu_data";
	FILE *fp1, *fp2;

	if((fp2 = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	} //파일을 fp2에 쓰기 모드로 오픈, 파일이 없는 경우 새로 생성

	if(fwrite(&blackbeard, sizeof(struct ssu_pirate), 1, fp2) != 1) {
		fprintf(stderr, "fwrite error\n");
		exit(1);
	} //fp2 파일에 구조체의 데이터를 구조체 크기 * 1 만큼 씀
	//에러시 오류 출력 후 프로그램 종료
	if(fclose(fp2)) {
		fprintf(stderr, "fclose error\n");
		exit(1);
	} //fp2의 파일을 닫음

	if((fp1 = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error\n");
		exit(1);
	} //파일을 읽기 모드로 오픈함, 실패시 에러 메시지 출력

	if(fread(&pirate, sizeof(struct ssu_pirate), 1, fp1) != 1) {
		fprintf(stderr, "fread error\n");
		exit(1);
	} //ssu_pirate의 크기 *1 만큼의 데이터를 fp로부터 읽어와 pirate에 저장
	//실패시 오류 출력
	if(fclose(fp1)) {
		fprintf(stderr, "fclose error\n");
		exit(1);
	} //fp1의 파일을 닫음, 실패시 오류 메시지 출력 후 프로그램 종료

	printf("name=\"%s\" booty=%lu beard_length=%u\n",
			pirate.name, pirate.booty, pirate.beard_length);
	//데이터 출력
	exit(0); //프로그램 종료
}
