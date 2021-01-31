#ifndef BOOK_H
#define BOOK_H



#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
 * Book struct.
 * Every string use malloc.
 * BookNumber is 7 digit, ISBN is 13 digit, Borrow is character.
 */
typedef struct Book
{
	int m_iBookNum ;
	char * m_cName ;
	char * m_cPublisher ;
	char * m_cAuthor ;
	char * m_cISBN ;
	char * m_cHoldingInstitution ;
	char m_cBorrow ;

	struct Book * m_pPrev ;
	struct Book * m_pNext ;
}  Book ;



#endif
