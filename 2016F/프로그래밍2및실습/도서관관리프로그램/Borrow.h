#ifndef BORROW_H
#define BORROw_H



#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


/*
 * Borrow struct.
 * StudentNum is 8 digit, BookNumber is 7 digit, other is type time_t.
 */
typedef struct Borrow
{
	int m_iStudentNum ;
	int m_iBookNum ;
	time_t m_tBorrowDate ;
	time_t m_tReturnDate ;

	struct Borrow * m_pPrev ;
	struct Borrow * m_pNext ;
}  Borrow ;



#endif
