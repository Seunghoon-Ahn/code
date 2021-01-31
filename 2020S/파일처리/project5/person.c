#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "person.h"

char fill_page[PAGE_SIZE]; //0xFF로 채운 페이지 크기의 배열

//필요한 경우 헤더 파일과 함수를 추가할 수 있음

// 과제 설명서대로 구현하는 방식은 각자 다를 수 있지만 약간의 제약을 둡니다.
// 레코드 파일이 페이지 단위로 저장 관리되기 때문에 사용자 프로그램에서 레코드 파일로부터 데이터를 읽고 쓸 때도
// 페이지 단위를 사용합니다. 따라서 아래의 두 함수가 필요합니다.
// 1. readPage(): 주어진 페이지 번호의 페이지 데이터를 프로그램 상으로 읽어와서 pagebuf에 저장한다
// 2. writePage(): 프로그램 상의 pagebuf의 데이터를 주어진 페이지 번호에 저장한다
// 레코드 파일에서 기존의 레코드를 읽거나 새로운 레코드를 쓰거나 삭제 레코드를 수정할 때나
// 모든 I/O는 위의 두 함수를 먼저 호출해야 합니다. 즉 페이지 단위로 읽거나 써야 합니다.

//
// 페이지 번호에 해당하는 페이지를 주어진 페이지 버퍼에 읽어서 저장한다. 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void readPage(FILE *fp, char *pagebuf, int pagenum)
{
	fseek(fp, PAGE_SIZE * pagenum, SEEK_SET);
	fread((void *)pagebuf, PAGE_SIZE, 1, fp);

	return;
}

//
// 페이지 버퍼의 데이터를 주어진 페이지 번호에 해당하는 위치에 저장한다. 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void writePage(FILE *fp, const char *pagebuf, int pagenum)
{
	fseek(fp, PAGE_SIZE * pagenum, SEEK_SET);
	fwrite((void *)pagebuf, PAGE_SIZE, 1, fp);

	return;
}

//
// 새로운 레코드를 저장할 때 터미널로부터 입력받은 정보를 Person 구조체에 먼저 저장하고, pack() 함수를 사용하여
// 레코드 파일에 저장할 레코드 형태를 recordbuf에 만든다. 그런 후 이 레코드를 저장할 페이지를 readPage()를 통해 프로그램 상에
// 읽어 온 후 pagebuf에 recordbuf에 저장되어 있는 레코드를 저장한다. 그 다음 writePage() 호출하여 pagebuf를 해당 페이지 번호에
// 저장한다.
// 
void pack(char *recordbuf, const Person *p)
{
	char *tmp = recordbuf;
	strcpy(tmp, p->sn);
	strcpy(tmp += strlen(p->sn), "#");
	strcpy(tmp += 1, p->name);
	strcpy(tmp += strlen(p->name), "#");
	strcpy(tmp += 1, p->age);
	strcpy(tmp += strlen(p->age), "#");
	strcpy(tmp += 1, p->addr);
	strcpy(tmp += strlen(p->addr), "#");
	strcpy(tmp += 1, p->phone);
	strcpy(tmp += strlen(p->phone), "#");
	strcpy(tmp += 1, p->email);
	strcpy(tmp += strlen(p->email), "#");
	tmp += 1;
	for(tmp; tmp < recordbuf + 99; tmp++)
		*tmp = (char)0xFF;

	return;
}

// 
// 아래의 unpack() 함수는 recordbuf에 저장되어 있는 레코드를 구조체로 변환할 때 사용한다. 이 함수가 언제 호출되는지는
// 위에서 설명한 pack()의 시나리오를 참조하면 된다.
//
void unpack(const char *recordbuf, Person *p)
{

	char *token;
	char tmpbuf[RECORD_SIZE];
	strcpy(tmpbuf, recordbuf);
	int len = 0;

	token = strtok(tmpbuf, "#");
	strcpy(p->sn, token);
	token = strtok(NULL, "#");
	strcpy(p->name, token);
	token = strtok(NULL, "#");
	strcpy(p->age, token);
	token = strtok(NULL, "#");
	strcpy(p->addr, token);	
	token = strtok(NULL, "#");
	strcpy(p->phone, token);
	token = strtok(NULL, "#");
	strcpy(p->email, token);

	return;
}

//
// 새로운 레코드를 저장하는 기능을 수행하며, 터미널로부터 입력받은 필드값을 구조체에 저장한 후 아래의 insert() 함수를 호출한다.
//
void insert(FILE *fp, const Person *p)
{
	char recordbuf[RECORD_SIZE];
	char pagebuf[PAGE_SIZE];
	char header[PAGE_SIZE];
	int pagecnt, recordcnt, d_page, d_record;
	int recordnum;
	int new_d_page, new_d_record;

	memset(recordbuf, (char)0xFF, RECORD_SIZE);

	pack(recordbuf, p);

	readPage(fp, header, 0);
	memcpy(&pagecnt, header, 4);
	memcpy(&recordcnt, header + 4, 4);
	memcpy(&d_page, header + 8, 4);
	memcpy(&d_record, header + 12, 4);

	if(d_page == -1 && d_record == -1) { //삭제되어 빈 레코드가 없을때
		if(recordcnt == 0) { //가장 처음으로 생성되는 경우
			fseek(fp, 0, SEEK_END);
			writePage(fp, fill_page, 1); //1번 페이지에 쓰고
			readPage(fp, pagebuf, 1); //1번 페이지 읽고
			strncpy(pagebuf, recordbuf, RECORD_SIZE);
			writePage(fp, pagebuf, 1);
			pagecnt++;
			recordcnt++;

			memcpy(header, &pagecnt, 4);
			memcpy(header + 4, &recordcnt, 4);
			writePage(fp, header, 0);
		}
		else { //이미 파일에 쓰인게 있을때
			recordnum = recordcnt % (PAGE_SIZE / RECORD_SIZE);
			if(recordnum == 0) { //숫자 딱 떨어질때 - 새 페이지 추가
				fseek(fp, 0, SEEK_END);
				writePage(fp, fill_page, pagecnt);
				pagecnt++;
				readPage(fp, pagebuf, pagecnt - 1);
				strncpy(pagebuf, recordbuf, RECORD_SIZE);
				writePage(fp, pagebuf, pagecnt - 1);
				recordcnt++;
				memcpy(header, &pagecnt, 4);
				memcpy(header+4, &recordcnt, 4);
				writePage(fp, header, 0);
			}
			else { //모든 페이지가 가득 찬것이 아닐때
				readPage(fp, pagebuf, pagecnt-1);
				strncpy(pagebuf + RECORD_SIZE * recordnum, recordbuf, RECORD_SIZE);
				writePage(fp, pagebuf, pagecnt - 1);
				recordcnt++;
				memcpy(header+4, &recordcnt, 4);
				writePage(fp, header, 0);
			}
		}
	}
	else{ //빈 레코드가 있을떄
		readPage(fp, pagebuf, d_page);
		memcpy(&new_d_page, pagebuf + d_record * RECORD_SIZE + 1, 4);
		memcpy(&new_d_record, pagebuf + d_record * RECORD_SIZE + 5, 4);
		
		strncpy(pagebuf + RECORD_SIZE * d_record, recordbuf, RECORD_SIZE);
		writePage(fp, pagebuf, d_page);
		memcpy(header + 8, &new_d_page, 4);
		memcpy(header + 12, &new_d_record, 4);
		writePage(fp, header, 0);
	}
	return;
}

//
// 주민번호와 일치하는 레코드를 찾아서 삭제하는 기능을 수행한다.
//
void delete(FILE *fp, const char *sn)
{
	char recordbuf[RECORD_SIZE];
	char pagebuf[PAGE_SIZE];
	char header[PAGE_SIZE];
	int i, j;
	int pagecnt, recordcnt, d_page, d_record;

	Person *p = (Person *)malloc(sizeof(Person));

	readPage(fp, header, 0);
	memcpy(&pagecnt, header, 4);
	memcpy(&recordcnt, header + 4, 4);
	memcpy(&d_page, header + 8, 4);
	memcpy(&d_record, header + 12, 4);

	for(i = 1; i <= pagecnt; i++) {
		readPage(fp, pagebuf, i);
		for(j = 0; j < (PAGE_SIZE / RECORD_SIZE); j++) {
			strncpy(recordbuf, pagebuf + RECORD_SIZE * j, RECORD_SIZE);
			if(recordbuf[0] == '*')
				continue;
			unpack(recordbuf, p);
			if(!strncmp(p->sn, sn, strlen(sn))) { //주민번호가 같을떄
				pagebuf[RECORD_SIZE * j] = '*';
				memcpy(pagebuf + RECORD_SIZE * j + 1, &d_page, 4);
				memcpy(pagebuf + RECORD_SIZE * j + 5, &d_record, 4);
				memcpy(header + 8, &i, 4);
				memcpy(header + 12, &j, 4);
				writePage(fp, pagebuf, i);
				writePage(fp, header, 0);
				free(p);
				return;
			}
		}
	}
	printf("No Matched sn!!\n");

	free(p);
	return;
}

int main(int argc, char *argv[])
{
	FILE *fp;  // 레코드 파일의 파일 포인터
	Person *p = (Person *)malloc(sizeof(Person));

	char d_sn[14];
	char header[PAGE_SIZE];
	int filesize = 0;
	int tmp;

	memset(fill_page, (char)0xFF, PAGE_SIZE); //페이지를 만드는데에 쓸 페이지배열

	if(argc < 4) {
		fprintf(stderr, "Arguments are something wrong...\n");
		exit(1);
	}

	if((fp = fopen(argv[2], "r+")) == 0) {
		fp = fopen(argv[2], "w+");
		fclose(fp);
		fp = fopen(argv[2], "r+");
	}

	if(argv[1][0] == 'i') { //insert 일떄
		fseek(fp, 0, SEEK_END);
		filesize = (int)ftell(fp);
		fseek(fp, 0, SEEK_SET);

		if(filesize < PAGE_SIZE) {
			memset(header, (char)0xFF, PAGE_SIZE);
			tmp = 1;
			memcpy(header, &tmp, 4);
			tmp = 0;
			memcpy(header + 4, &tmp, 4);
			tmp = -1;
			memcpy(header + 4 * 2, &tmp, 4);
			memcpy(header + 4 * 3, &tmp, 4); 
			writePage(fp, header, 0);
		}

		strcpy(p->sn, argv[3]);
		strcpy(p->name, argv[4]);
		strcpy(p->age, argv[5]);
		strcpy(p->addr, argv[6]);
		strcpy(p->phone, argv[7]);
		strcpy(p->email, argv[8]);
		insert(fp, p);
	}
	else if(argv[1][0] == 'd') { //delete 일때

		strcpy(d_sn, argv[3]);
		delete(fp, d_sn); //주민번호 보내서 삭제 할수 있게
	}

	free(p);
	fclose(fp);
	
	return 1;
}