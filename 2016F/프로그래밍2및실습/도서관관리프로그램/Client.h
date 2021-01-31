#ifndef CLIENT_H
#define CLIENT_H



#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
 * Client struct.
 * Every string use malloc.
 */
typedef struct Client
{
	int m_iStudentNum ;
	char * m_cPassword ;
	char * m_cName ;
	char * m_cAddress ;
	char * m_cNumber ;

	struct Client * m_pPrev ;
	struct Client * m_pNext ;
}  Client ;



#endif
