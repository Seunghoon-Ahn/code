#include "Library_Service.h"
#define TIME_T_SECOND_30DAY		2592000		;	// 2592000 = 3600 * 24 * 30

int iClientCount = 0 ;
int iBookCount = 0 ;
int iBorrowCount = 0 ;
int iBookNum = 0 ;
Client * pUser = NULL ;				// Login. NULL is noOne, ClientHead is admin. Other people, that people login.


/*
 * Load File and add to LinkedList
 */
void File_Load ( FILE * fFile , int iFileCheck )
{
	Client * pClientNode = NULL ;
	Client * pClientSort = NULL ;
	Book * pBookNode = NULL ;
	Book * pBookSort = NULL ;
	Borrow * pBorrowNode = NULL ;
	int i = 0 ;
	int iStartIndex = 0 ;
	int iTemp = 0 ;
	char cTemp [ 150 ] ;
	char cInfo [ 50 ] ;


	if ( 1 == iFileCheck )
	{
		while ( ( NULL != fFile ) && ( fgets ( cTemp , 149 , fFile ) ) )
		{
			pClientNode = ( Client * ) malloc ( sizeof ( Client ) ) ;							// pNode -> m_pNext = pNew
			Copy_Nto0 ( cTemp , cInfo , 0 , 0 , 8 ) ;
			pClientNode -> m_iStudentNum = atoi ( cInfo ) ;

			i = 11 ;
			iStartIndex = 11 ;
			iTemp = 0 ;
			

			while ( '\n' != cTemp [ i ] )
			{
				++ i ;


				if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 0 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pClientNode -> m_cPassword = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pClientNode -> m_cPassword , cInfo , strlen ( cInfo ) ) ;
					pClientNode -> m_cPassword [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 1 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pClientNode -> m_cName = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pClientNode -> m_cName , cInfo , strlen ( cInfo ) ) ;
					pClientNode -> m_cName [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 2 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pClientNode -> m_cAddress = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pClientNode -> m_cAddress , cInfo , strlen ( cInfo ) ) ;
					pClientNode -> m_cAddress [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( '\n' == cTemp [ i ] ) && ( 3 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex ) ;
					pClientNode -> m_cNumber = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pClientNode -> m_cNumber , cInfo , strlen ( cInfo ) ) ;
					pClientNode -> m_cNumber [ strlen ( cInfo ) ] = '\0' ;
				}
			}


			pClientSort = Sort_StudentNum_Find_Member ( pClientNode ) ;

			pClientSort -> m_pNext -> m_pPrev = pClientNode ;
			pClientNode -> m_pNext = pClientSort -> m_pNext ;
			pClientSort -> m_pNext = pClientNode ;
			pClientNode -> m_pPrev = pClientSort ;

			++ iClientCount ;
		}
	}
	else if ( 2 == iFileCheck )
	{
		while ( ( NULL != fFile ) && ( fgets ( cTemp , 149 , fFile ) ) )
		{
			pBookNode = ( Book * ) malloc ( sizeof ( Book ) ) ;										// pNode -> m_pNext = pNew
			Copy_Nto0 ( cTemp , cInfo , 0 , 0 , 7 ) ;
			pBookNode -> m_iBookNum = atoi ( cInfo ) ;


			if ( pBookNode -> m_iBookNum > iBookNum )
				iBookNum = pBookNode -> m_iBookNum ;

			i = 10 ;
			iStartIndex = 10 ;
			iTemp = 0 ;
			

			while ( '\n' != cTemp [ i ] )
			{
				++ i ;


				if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 0 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBookNode -> m_cName = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pBookNode -> m_cName , cInfo , strlen ( cInfo ) ) ;
					pBookNode -> m_cName [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 1 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBookNode -> m_cPublisher = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pBookNode -> m_cPublisher , cInfo , strlen ( cInfo ) ) ;
					pBookNode -> m_cPublisher [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 2 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBookNode -> m_cAuthor = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pBookNode -> m_cAuthor , cInfo , strlen ( cInfo ) ) ;
					pBookNode -> m_cAuthor [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 3 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBookNode -> m_cISBN = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pBookNode -> m_cISBN , cInfo , strlen ( cInfo ) ) ;
					pBookNode -> m_cISBN [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 4 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBookNode -> m_cHoldingInstitution = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cInfo ) + 1 ) ) ;
					strncpy ( pBookNode -> m_cHoldingInstitution , cInfo , strlen ( cInfo ) ) ;
					pBookNode -> m_cHoldingInstitution [ strlen ( cInfo ) ] = '\0' ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( '\n' == cTemp [ i ] ) && ( 5 == iTemp ) )
				{
					pBookNode -> m_cBorrow = cTemp [ i - 2 ] ;
				}
			}


			pBookSort = Sort_ISBN_Find_Book ( pBookNode ) ;

			pBookSort -> m_pNext -> m_pPrev = pBookNode ;
			pBookNode -> m_pNext = pBookSort -> m_pNext ;
			pBookSort -> m_pNext = pBookNode ;
			pBookNode -> m_pPrev = pBookSort ;
			
			++ iBookCount ;
		}
	}
	else
	{
		while ( ( NULL != fFile ) && ( fgets ( cTemp , 149 , fFile ) ) )
		{
			pBorrowNode = ( Borrow * ) malloc ( sizeof ( Borrow ) ) ;

			
			pBorrowNode -> m_pNext = pBorrowTail ;											// pNew -> m_pNext = pTail
			pBorrowNode -> m_pPrev = pBorrowTail -> m_pPrev ;								// pNew -> m_pPrev = pNode
			pBorrowNode -> m_pPrev -> m_pNext = pBorrowNode ;								// pNode -> m_pNext = pNew
			pBorrowTail -> m_pPrev = pBorrowNode ;											// pTail -> m_pPrev = pNew


			Copy_Nto0 ( cTemp , cInfo , 0 , 0 , 8 ) ;
			pBorrowTail -> m_pPrev -> m_iStudentNum = atoi ( cInfo ) ;

			i = 11 ;
			iStartIndex = 11 ;
			iTemp = 0 ;
			

			while ( '\n' != cTemp [ i ] )
			{
				++ i ;


				if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 0 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBorrowTail -> m_pPrev -> m_iBookNum = atoi ( cInfo ) ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
					
				}
				else if ( ( ' ' == cTemp [ i - 2 ] ) && ( '|' == cTemp [ i - 1  ] ) && ( ' ' == cTemp [ i ] ) && ( 1 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex - 2 ) ;
					pBorrowTail -> m_pPrev -> m_tBorrowDate = atol ( cInfo ) ;
					iStartIndex = i + 1 ;
					++ iTemp ;
					++ i ;
				}
				else if ( ( '\n' == cTemp [ i ] ) && ( 2 == iTemp ) )
				{
					Copy_Nto0 ( cTemp , cInfo , iStartIndex , 0 , i - iStartIndex ) ;
					pBorrowTail -> m_pPrev -> m_tReturnDate = atol ( cInfo ) ;
				}
			}

			
			++ iBorrowCount ;
		}
	}	
}


 /*
  * Save File.
  * 1 is Client, 2 is Book, 3 is Borrow.
  * 4 is write just one new borrow.
  */
void File_Save ( FILE * fFile , int iFileCheck )
{
	Client * pClientNode = pClientHead -> m_pNext ;
	Book * pBookNode = pBookHead -> m_pNext ;
	Borrow * pBorrowNode = pBorrowHead -> m_pNext ;
	int i = 0 ;


	if ( 1 == iFileCheck )
	{
		if ( iClientCount )
		{
			for ( i = 0 ; i < iClientCount ; ++i )
			{
				fprintf ( fFile , "%d | %s | %s | %s | %s\n" , pClientNode -> m_iStudentNum , pClientNode -> m_cPassword , pClientNode -> m_cName ,
																pClientNode -> m_cAddress , pClientNode -> m_cNumber ) ;
				pClientNode = pClientNode -> m_pNext ;
			}
		}
	}
	else if ( 2 == iFileCheck )
	{
		if ( iBookCount )
		{
			for ( i = 0 ; i < iBookCount ; ++i )
			{
				fprintf ( fFile , "%d | " , pBookNode -> m_iBookNum ) ;
				fprintf ( fFile , "%s | " , pBookNode -> m_cName ) ;
				fprintf ( fFile , "%s | " , pBookNode -> m_cPublisher ) ;
				fprintf ( fFile , "%s | " , pBookNode -> m_cAuthor ) ;
				fprintf ( fFile , "%s | " , pBookNode -> m_cISBN ) ;
				fprintf ( fFile , "%s | " , pBookNode -> m_cHoldingInstitution ) ;

				if ( 'Y' == pBookNode -> m_cBorrow )
					fprintf ( fFile , "Y\r\n" ) ;
				else
					fprintf ( fFile , "N\r\n" ) ;

				fflush ( fFile ) ;

				pBookNode = pBookNode -> m_pNext ;
			}
		}
	}
	else if ( 3 == iFileCheck )
	{
		if ( iBorrowCount )
		{
			for ( i = 0 ; i < iBorrowCount ; ++i )
			{
				fprintf ( fFile , "%d | " , pBorrowNode -> m_iStudentNum ) ;
				fprintf ( fFile , "%d | " , pBorrowNode -> m_iBookNum ) ;
				fprintf ( fFile , "%ld | " , pBorrowNode -> m_tBorrowDate ) ;
				fprintf ( fFile , "%ld\r\n" , pBorrowNode -> m_tReturnDate ) ;
				pBorrowNode = pBorrowNode -> m_pNext ;
			}
		}
	}
	else
	{
		pBorrowNode = pBorrowTail -> m_pPrev ;

		fprintf ( fFile , "%d | " , pBorrowNode -> m_iStudentNum ) ;
		fprintf ( fFile , "%d | " , pBorrowNode -> m_iBookNum ) ;
		fprintf ( fFile , "%ld | " , pBorrowNode -> m_tBorrowDate ) ;
		fprintf ( fFile , "%ld\r\n" , pBorrowNode -> m_tReturnDate ) ;
	}
}


/*
 * Print Basic Menu.
 */
void ServiceMenu_Print ()
{
	printf ( "Libary Service\n" ) ;
	printf ( "1. Register Member\n" ) ;
	printf ( "2. Login\n" ) ;
	printf ( "3. Exit\n\n" ) ;
}


/*
 * Print Admin Menu.
 */
void ServiceAdmin_Print ()
{
	printf ( "Admin Menu\n" ) ;
	printf ( "1. Register Book\t" ) ;
	printf ( "2. Eliminate Book\n" ) ;
	printf ( "3. Borrow Book\t\t" ) ;
	printf ( "4. Return Book\n" ) ;
	printf ( "5. Search Book\t\t" ) ;
	printf ( "6. User List\n" ) ;
	printf ( "7. Logout \t\t" ) ;
	printf ( "8. Exit\n\n" ) ;
}


/*
 * Print User Menu.
 */
void ServiceUser_Print ()
{
	printf ( "User Menu\n" ) ;
	printf ( "1. Search Book\t\t" ) ;
	printf ( "2. My Borrow List\n" ) ;
	printf ( "3. Modify Information\t" ) ;
	printf ( "4. Quit Member\n" ) ;
	printf ( "5. Logout\t\t" ) ;
	printf ( "6. Exit\n\n" ) ;
}


/*
 * because of clear, Re_Print
 */
void Re_ServiceMenu_Print ( int iMenu )
{
	system ( "clear" ) ;
	printf ( "Libary Service\n" ) ;
	printf ( "1. Register Member\n" ) ;
	printf ( "2. Login\n" ) ;
	printf ( "3. Exit\n\n" ) ;
	printf ( "Input : %d\n\n" , iMenu ) ;
}


/*
 * because of clear, Re_Print
 */
void Re_ServiceAdmin_Print ( int iMenu )
{
	system ( "clear" ) ;
	printf ( "Admin Menu\n" ) ;
	printf ( "1. Register Book\t" ) ;
	printf ( "2. Eliminate Book\n" ) ;
	printf ( "3. Borrow Book\t\t" ) ;
	printf ( "4. Return Book\n" ) ;
	printf ( "5. Search Book\t\t" ) ;
	printf ( "6. User List\n" ) ;
	printf ( "7. Logout \t\t" ) ;
	printf ( "8. Exit\n\n" ) ;
	printf ( "Input : %d\n\n" , iMenu ) ;
}


/*
 * because of clear, Re_Print
 */
void Re_ServiceUser_Print ( int iMenu )
{
	system ( "clear" ) ;
	printf ( "User Menu\n" ) ;
	printf ( "1. Search Book\t\t" ) ;
	printf ( "2. My Borrow List\n" ) ;
	printf ( "3. Modify Information\t" ) ;
	printf ( "4. Quit Member\n" ) ;
	printf ( "5. Logout\t\t" ) ;
	printf ( "6. Exit\n\n" ) ;
	printf ( "Input : %d\n\n" , iMenu ) ;
}


/*
 * strcpy, Copy Orgin [ n ] to Copy [ 0 ]
 */
void Copy_Nto0 ( char * cpOrigin , char * cpCopy , int iOrigin_Index , int iCopy_Index , int iLength )
{
	int i = 0 ;


	for ( i = 0 ; i < iLength ; ++i )
	{
		cpCopy [ iCopy_Index + i ] = cpOrigin [ iOrigin_Index + i ] ;
	}


	cpCopy [ i ] = '\0' ;
}


/*
 * Register Function.
 * Register new member, with sorted.
 */
void Register_Member ()
{
	Client * pNode = ( Client * ) malloc ( sizeof ( Client ) ) ;
	Client * pSort = NULL ;
	FILE * fClient = NULL ;
	char cTemp [ 50 ] ;


	printf ( "Student Number, Password, Name, Address, Phone Number.\n" ) ;
	printf ( "Student Number : " ) ;
	scanf ( "%d" , & pNode -> m_iStudentNum ) ;
	getchar();
	fflush ( stdin ) ;
	
	printf ( "Password : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	
	pNode -> m_cPassword = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cPassword , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cPassword [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Name : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	
	pNode -> m_cName = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cName , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cName [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Address : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	
	pNode -> m_cAddress = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cAddress , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cAddress [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Phone Number : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	
	pNode -> m_cNumber = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cNumber , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cNumber [ strlen ( cTemp ) ] = '\0' ;


	pSort = Sort_StudentNum_Find_Member ( pNode ) ;
	
	
	if ( NULL == pSort )
	{
		free ( pNode ) ;
		
		printf ( "Same Student Number. Register failed.\n" ) ;
	}
	else
	{
		pSort -> m_pNext -> m_pPrev = pNode ;
		pNode -> m_pNext = pSort -> m_pNext ;
		pSort -> m_pNext = pNode ;
		pNode -> m_pPrev = pSort ;

		++ iClientCount ;
		

		fClient = fopen ( "Client.txt" , "a" ) ;
		File_Save ( fClient , 1 ) ;
		fclose ( fClient ) ;


		printf ( "Register end.\n" ) ;
	}
}


/*
 * Parameter Node need to be sorted.
 * Compare Node's Student Number, and find sequence.
 * return value is pSort.
 * pSort -> m_pNext = pNode
 */
Client * Sort_StudentNum_Find_Member ( Client * pNode )
{
	Client * pSort = pClientHead ;
	int iSortNumber = 0 ;
	int iNodeNumber = pNode -> m_iStudentNum ;


	while ( pSort -> m_pNext != pClientTail )
	{
		pSort = pSort -> m_pNext ;
		iSortNumber = pSort -> m_iStudentNum ;

		
		if ( iNodeNumber == iSortNumber )
		{
			pSort = NULL ;

			break ;
		}
		else if ( iSortNumber > iNodeNumber )			// SortNumber is 20161112 , NodeNumber is 20161111
		{
			pSort = pSort -> m_pPrev ;

			break ;
		}
	}
	
	
	return pSort ;
}


/*
 * Login Function.
 * Admin, or User.
 */
void Login_Member ()
{
	Client * pNode = pClientHead ;
	char cUser [ 20 ] ;
	char cPassword [ 20 ] ;
	
	
	printf ( "Student Number : " ) ;
	scanf ( "%s" , cUser ) ;
	printf ( "Password : " ) ;
	scanf ( "%s" , cPassword ) ;
	getchar();


	while ( pNode -> m_pNext != pClientTail )
	{
		pNode = pNode -> m_pNext ;

		
		if ( ! strcmp ( "admin" , cUser ) )
		{
			pUser = pClientHead ;

			break ;
		}
		else if ( ( atoi ( cUser ) ) == ( pNode -> m_iStudentNum ) )			// SortNumber is 1234567 098765 , NodeNumber is 1234567 987654
		{
			if ( ! strcmp ( cPassword , pNode -> m_cPassword ) )
			{
				pUser = pNode ;

				break ;
			}
			else
			{
				pUser = NULL ;

				break ;
			}
		}
	}
}


/*
 * Register Function.
 * Register Book, with sorted.
 */
void Register_Book ()
{
	Book * pNode = ( Book * ) malloc ( sizeof ( Book ) ) ;
	Book * pSort = NULL ;
	FILE * fBook = NULL ;
	char cTemp [ 50 ] ;

	printf ( "Book Name, Publisher, Author, ISBN, Holding Institution.\n" ) ;
	printf ( "Book Name : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	
	pNode -> m_cName = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cName , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cName [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Publisher : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;

	pNode -> m_cPublisher = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cPublisher , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cPublisher [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Author : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;

	pNode -> m_cAuthor = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cAuthor , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cAuthor [ strlen ( cTemp ) ] = '\0' ;

	printf ( "ISBN : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;

	pNode -> m_cISBN = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cISBN , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cISBN [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Holding Institution : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;

	pNode -> m_cHoldingInstitution = ( char * ) malloc ( sizeof ( char ) * ( strlen ( cTemp ) + 1 ) ) ;
	strncpy ( pNode -> m_cHoldingInstitution , cTemp , strlen ( cTemp ) ) ;
	pNode -> m_cHoldingInstitution [ strlen ( cTemp ) ] = '\0' ;


	pSort = Sort_ISBN_Find_Book ( pNode ) ;
	
	
	if ( NULL == pSort )
	{
		free ( pNode ) ;
		
		printf ( "Same Student Number. Register failed.\n" ) ;
	}
	if ( NULL != pSort )
	{
		pNode -> m_cBorrow = 'Y' ;
		pNode -> m_iBookNum = iBookNum + 1 ;
		++ iBookNum ;
		pSort -> m_pNext -> m_pPrev = pNode ;
		pNode -> m_pNext = pSort -> m_pNext ;
		pSort -> m_pNext = pNode ;
		pNode -> m_pPrev = pSort ;

		++ iBookCount ;


		fBook = fopen ( "Book.txt" , "a" ) ;
		File_Save ( fBook , 2 ) ;
		fclose ( fBook ) ;


		printf ( "Register end.\n" ) ;
	}
}


/*
 * Parameter Node need to be sorted.
 * Compare Node's ISBN, and find sequence.
 * return value is pSort.
 * pSort -> m_pNext = pNode
 */
Book * Sort_ISBN_Find_Book ( Book * pNode )
{
	Book * pSort = pBookHead ;
	char cSortISBN [ 14 ] ;
	char cNodeISBN [ 14 ] ;
	char cTemp [ 8 ] ;
	int iSortISBN = 0 ;
	int iNodeISBN = 0 ;

	strcpy ( cNodeISBN , pNode -> m_cISBN ) ;


	while ( pSort -> m_pNext != pBookTail )
	{
		pSort = pSort -> m_pNext ;
		strcpy ( cSortISBN , pSort -> m_cISBN ) ;

		strncpy ( cTemp , cSortISBN , 7 ) ;
		cTemp [ 7 ] = '\0' ;
		iSortISBN = atoi ( cTemp ) ;
		strncpy ( cTemp , cNodeISBN , 7 ) ;
		cTemp [ 7 ] = '\0' ;
		iNodeISBN = atoi ( cTemp ) ;


		if ( iSortISBN > iNodeISBN )			// SortISBN is 20160805111 , NodeNumber is 20160805112
		{
			pSort = pSort -> m_pPrev ;

			break ;
		}
		else if ( iSortISBN == iNodeISBN )
		{
			Copy_Nto0 ( cSortISBN , cTemp , 7 , 0 , 7 ) ;
			iSortISBN = atoi ( cTemp ) ;
			Copy_Nto0 ( cNodeISBN , cTemp , 7 , 0 , 7 ) ;
			iNodeISBN = atoi ( cTemp ) ;

			if ( iSortISBN > iNodeISBN )
			{
				pSort = pSort -> m_pPrev ;

				break ;
			}
		}
	}

	
	return pSort ;
}


/*
 * Eliminate Book.
 * Search the book first, and get StudentNumber and BookNumber.
 */
void Eliminate_Book ()
{
	int iMenu = 0 ;
	Book * pNode = NULL ;
	Book * pEliPrev = NULL ;
	Book * pEliNext = NULL ;
	FILE * fBook = NULL ;


	printf ( "1. Book Name\t" ) ;
	printf ( "2. ISBN\n" ) ;

	scanf ( "%d" , & iMenu ) ;
	getchar();
	fflush ( stdin ) ;


	if ( 2 == iMenu )
		iMenu = 3 ;


	pNode = Search_Book ( iMenu , true ) ;
	
	
	if ( NULL != pNode )
	{
		Print_Book_Information ( pNode ) ;
		pNode = Search_Book ( 5 , true ) ;
	}


	if ( ( NULL != pNode ) && ( 'Y' == pNode -> m_cBorrow ) )
	{
		pEliPrev = pNode -> m_pPrev ;
		pEliNext = pNode -> m_pNext ;
		pEliPrev -> m_pNext = pEliNext ;
		pEliNext -> m_pPrev = pEliPrev ;
		-- iBookCount ;


		if ( pNode -> m_iBookNum == iBookNum )
			BookNumber_ReSetting () ;


		free ( pNode ) ;


		fBook = fopen ( "Book.txt" , "w+" ) ;
		File_Save ( fBook , 2 ) ;
		fclose ( fBook ) ;
	}
	else if ( ( NULL != pNode ) && ( 'N' == pNode -> m_cBorrow ) )
	{
		printf ( "You can't eliminate it.\n" ) ;
	}
	else
		printf ( "That book doesn't exist.\n" ) ;
}


/*
 * Eliminate the Borrowed Book.
 */
void Eliminate_Borrow ( Borrow * pNode )
{
	Borrow * pEliPrev = pNode -> m_pPrev ;
	Borrow * pEliNext = pNode -> m_pNext ;
	FILE * fBorrow = NULL ;


	pEliPrev -> m_pNext = pEliNext ;
	pEliNext -> m_pPrev = pEliPrev ;
	-- iBorrowCount ;


	free ( pNode ) ;


	fBorrow = fopen ( "Borrow.txt" , "w+" ) ;
	File_Save ( fBorrow , 3 ) ;
	fclose ( fBorrow ) ;
}


/*
 * iBookNum is eliminated, so value has to be changed.
 */
void BookNumber_ReSetting ()
{
	Book * pNode = pBookHead ;


	iBookNum = 0 ;


	while ( pNode -> m_pNext != pBookTail )
	{
		pNode = pNode -> m_pNext ;

	
		if ( pNode -> m_iBookNum > iBookNum )
			iBookNum = pNode -> m_iBookNum ;
	}
}


/*
 * Borrow Book.
 * Search the book first, and get StudentNumber and BookNumber.
 */
void Borrow_Book ()
{
	int iMenu = 0 ;
	int iTempBookNum = 0 ;
	int iStudentNum = 0 ;
	time_t tTime = 0 ;
	Client * pClientNode = pClientHead ;
	Book * pBookNode = pBookHead ;
	Borrow * pBorrowNode = pBorrowHead ;
	FILE * fBorrow = NULL ;


	printf ( "1. Book Name\t" ) ;
	printf ( "2. ISBN\n" ) ;

	printf ( "Input Menu : " ) ;

	scanf ( "%d" , & iMenu ) ;
	getchar();

	if ( 2 == iMenu )
		iMenu = 3 ;
	
	fflush ( stdin ) ;


	pBookNode = Search_Book ( iMenu , true ) ;
	
	
	if ( NULL != pBookNode )
	{
		Print_Book_Information ( pBookNode ) ;

		pClientNode = pClientHead ;
		pBookNode = pBookHead ;

		printf ( "Student Number : " ) ;
		scanf ( "%d" , & iStudentNum ) ;
		printf ( "Book Number : " ) ;
		scanf ( "%d" , & iTempBookNum ) ;

		getchar();


		while ( pClientNode -> m_pNext != pClientTail )
		{
			pClientNode = pClientNode -> m_pNext ;

	
			if ( pClientNode -> m_iStudentNum == iStudentNum )
				break ;
		}
		while ( pBookNode -> m_pNext != pBookTail )
		{
			pBookNode = pBookNode -> m_pNext ;

	
			if ( pBookNode -> m_iBookNum == iTempBookNum )
				break ;
		}


		if ( pClientNode -> m_iStudentNum != iStudentNum )
		{
			printf ( "Client doesn't exist.\n" ) ;
		}
		else if ( pBookNode -> m_iBookNum != iTempBookNum )
		{
			printf ( "Book doesn't exist.\n" ) ;
		}
		else if ( 'N' == pBookNode -> m_cBorrow )
		{
			printf ( "Can't borrow that book.\n" ) ;
		}
		else
		{
			pBookNode -> m_cBorrow = 'N' ;
			
			pBorrowNode = ( Borrow * ) malloc ( sizeof ( Borrow * ) ) ;

			pBorrowNode -> m_iStudentNum = pClientNode -> m_iStudentNum ;
			pBorrowNode	-> m_iBookNum = pBookNode -> m_iBookNum ;
			time ( & tTime ) ;
			pBorrowNode -> m_tBorrowDate = tTime ;
			pBorrowNode -> m_tReturnDate = Set_Return_Date ( tTime ) ;

			pBorrowTail -> m_pPrev -> m_pNext = pBorrowNode ;
			pBorrowNode -> m_pPrev = pBorrowTail -> m_pPrev ;
			pBorrowTail -> m_pPrev = pBorrowNode ;
			pBorrowNode -> m_pNext = pBorrowTail ;

			++ iBorrowCount ;

			printf ( "Book has been borrowed.\n" ) ;


			fBorrow = fopen ( "Borrow.txt" , "a" ) ;
			File_Save ( fBorrow , 0 ) ;
			fclose ( fBorrow ) ;
		}
	}
}


/*
 * Set returning date.
 * If returning date is Sunday, set it Monday. + 1 day.
 */
time_t Set_Return_Date ( time_t tTime )
{
	char cTemp [ 40 ] ;


	tTime += TIME_T_SECOND_30DAY ;
	strcpy ( cTemp , ctime ( & tTime ) ) ;
	
	
	if ( ( 'S' == cTemp [ 23 ] ) && ( 'U' == cTemp [ 24 ] ) && ( 'N' == cTemp [ 25 ] ) )
		tTime += 86400 ;


	return tTime ;
}


/*
 * Return the borrowed book.
 */
void Return_Book ()
{
	int iStudentNum = 0 ;
	int ** irgBookNum = NULL ;
	int iTemp = 0 ;
	int i = 0 ;
	char cTemp ;
	Client * pClientNode = pClientHead ;
	Book * pBookNode = pBookHead ;
	Borrow * pBorrowNode = pBorrowHead ;
	int iStudentBorrow = 0 ;


	printf ( "Student Number : " ) ;
	scanf ( "%d" , & iStudentNum ) ;
	getchar();


	while ( pClientNode -> m_pNext != pClientTail )
	{
		pClientNode = pClientNode -> m_pNext ;

	
		if ( iStudentNum == pClientNode -> m_iStudentNum )
			break ;
	}
	while ( ( pClientTail != pClientNode -> m_pNext ) && ( pBorrowNode -> m_pNext != pBorrowTail ) )
	{
		pBorrowNode = pBorrowNode -> m_pNext ;


		if ( iStudentNum == pBorrowNode -> m_iStudentNum )
		{
			++ iStudentBorrow ;
		}
	}
	if ( iStudentBorrow )
	{
		pBorrowNode = pBorrowHead ;
		irgBookNum = ( int * ) malloc ( iStudentBorrow * sizeof ( int ) ) ;


		while ( i != iStudentBorrow )
		{
			if ( pBorrowTail == pBorrowNode -> m_pNext )
			{
				pBorrowNode = pBorrowHead ;
			}


			pBorrowNode = pBorrowNode -> m_pNext ;
			pBookNode = pBookHead ;


			if ( iStudentNum == pBorrowNode -> m_iStudentNum )
			{
				while ( pBookTail != pBookHead -> m_pNext )
				{
					pBookNode = pBookNode -> m_pNext ;


					if ( pBorrowNode -> m_iBookNum == pBookNode -> m_iBookNum )
						break ;
				}


				Print_Borrow_Information ( pBorrowNode , pBookNode ) ;
				irgBookNum [ i ] = pBorrowNode -> m_iBookNum ;
				++i ;
			}
		}


		printf ( "Returning Book Number : " ) ;
		scanf ( "%d" , & iTemp ) ;
		getchar();
		fflush ( stdin ) ;

		i = 0 ;


		while ( iTemp != irgBookNum [ i ] )
		{
			++ i ;
		}
		if ( i == iStudentBorrow )
		{
			printf ( "Book Number is wrong.\n" ) ;
		}
		else
		{
			printf ( "Return the book? : " ) ;
			scanf ( "%c" , & cTemp ) ;
			getchar();


			if ( 'Y' == cTemp )
			{
				pBookNode = pBookHead ;


				while ( pBookTail != pBookNode -> m_pNext )
				{
					pBookNode = pBookNode -> m_pNext ;


					if ( irgBookNum [ i ] == pBookNode -> m_iBookNum )
						break ;
				}	


				pBookNode -> m_cBorrow = 'Y' ;
				Eliminate_Borrow ( pBorrowNode ) ;
			}
		}


		free ( irgBookNum ) ;
	}
}


/*
 * Search Client.
 * Name, Student Number, Every Student.
 */
Client * Search_Client ()
{
	int iMenu = 0 ;
	char cName [ 20 ] ;
	int iTempStudentNum ;
	Client * pNode = pClientHead ;


	while ( 4 != iMenu )
	{
		pNode = pClientHead ;


		printf ( "1. Client Name Search\t" ) ;
		printf ( "2. Student Number Search\n" ) ;
		printf ( "3. All Search\t" ) ;
		printf ( "4. Previous Menu\n\n" ) ;
		printf ( "Input Menu : " ) ;


		scanf ( "%d" , & iMenu ) ;
		getchar();


		if ( 1 == iMenu )
		{
			printf ( "Client Name : " ) ;
			scanf ( "%s" , cName ) ;
			getchar();


			while ( pClientTail != pNode -> m_pNext)
			{
				pNode = pNode -> m_pNext ;


				if ( ! strcmp ( cName , pNode -> m_cName ) )
					break ;
			}


			if ( pClientTail != pNode -> m_pNext )
				Print_User ( pNode ) ;
			else
				printf ( "There's no User Name %s\n" , cName ) ;
		}
		else if ( 2 == iMenu )
		{
			printf ( "Student Number : " ) ;
			scanf ( "%d" , & iTempStudentNum ) ;
			getchar();


			while ( pClientTail != pNode -> m_pNext)
			{
				pNode = pNode -> m_pNext ;


				if ( iTempStudentNum == pNode -> m_iStudentNum )
					break ;
			}


			Print_User ( pNode ) ;
		}
		else if ( 3 == iMenu )
		{
			while ( pClientTail != pNode -> m_pNext )
			{
				pNode = pNode -> m_pNext ;

				Print_User ( pNode ) ;
			}
		}
		else if ( 4 != iMenu )
		{
			printf ( "Wrong menu. Try again.\n" ) ;
		}
	}
}


/*
 * Search Specific Book.
 * Name, Publisher, ISBN, Author, All Search.
 * Additional, Book number.
 * if bReturn is true, Search and return the book.
 * else, keep searching.
 */
Book * Search_Book ( int iMenu , bool bReturn )
{
	char cName [ 25 ] ;
	char cISBN [ 14 ] ;
	char cPublisher [ 25 ] ;
	char cAuthor [ 15 ] ;
	int iBookNum = 0 ;
	Book * pNode = pBookHead ;


	while ( 6 != iMenu )
	{
		pNode = pBookHead ;

		if ( ! bReturn )
		{
			printf ( "1. Book Name\t" ) ;
			printf ( "2. Publisher\n" ) ;
			printf ( "3. ISBN\t" ) ;
			printf ( "4. Author\n" ) ;
			printf ( "5. All Search\t" ) ;
			printf ( "6. Previous Menu\n\n" ) ;
			printf ( "Input Menu : " ) ;


			scanf ( "%d" , & iMenu ) ;
			getchar();
			fflush ( stdin ) ;
		}


		if ( 1 == iMenu )	// Name
		{
			printf ( "Book Name : " ) ;

			gets ( cName ) ;
			fflush ( stdin ) ;


			while ( pNode -> m_pNext != pBookTail )
			{
				pNode = pNode -> m_pNext ;

		
				if ( ! strcmp ( cName , pNode -> m_cName ) )			// SortISBN is 20160805111 , NodeNumber is 20160805112
				{
					break ;
				}
			}
		}
		
		else if ( 2 == iMenu ) // Publisher
		{
			printf ( "Publisher : " ) ;

			gets ( cPublisher ) ;
			fflush ( stdin ) ;


			while ( pNode -> m_pNext != pBookTail )
			{
				pNode = pNode -> m_pNext ;


				if ( ! strcmp ( cPublisher , pNode -> m_cPublisher ) )
				{
					break ;

				}
			}
		}
		else if ( 3 == iMenu ) // ISBN
		{
			printf ( "ISBN : " ) ;
			scanf ( "%s" , cISBN ) ;
			getchar();
			fflush ( stdin ) ;


			while ( pNode -> m_pNext != pBookTail )
			{
				pNode = pNode -> m_pNext ;


				if ( ! strcmp ( cISBN , pNode -> m_cISBN ) )
				{
					break ;
				}
			}
		}
		else if ( 4 == iMenu ) // Author
		{
			printf ( "Author : " ) ;

			gets ( cAuthor ) ;
			fflush ( stdin ) ;


			while ( pNode -> m_pNext != pBookTail )
			{
				pNode = pNode -> m_pNext ;


				if ( ! strcmp ( cAuthor , pNode -> m_cAuthor ) )
				{
					break ;
				}
			}
		}
		else if ( 5 == iMenu )	// All Search
		{
			while ( pNode -> m_pNext != pBookTail )
			{
				pNode = pNode -> m_pNext ;
				Print_Book_Information ( pNode ) ;
			}
		}
		else if ( 7 == iMenu )	// BookNumber
		{
			printf ( "BookNumber : " ) ;

			scanf ( "%d" , & iBookNum ) ;
			
			getchar();

			fflush ( stdin ) ;


			while ( pNode -> m_pNext != pBookTail )
			{
				pNode = pNode -> m_pNext ;


				if ( iBookNum == pNode -> m_iBookNum )
				{
					break ;
				}
			}
		}
		else if ( 6 == iMenu )
		{
			break ;
		}
		else
		{
			printf ( "Wrong menu. Try again.\n" ) ;
		}


		if ( pNode -> m_pNext == pBookTail )
			pNode = NULL ;
		else if ( ! bReturn )
			Print_Book_Information ( pNode ) ;
		else
			return pNode ;
	}
}


/*
 * Logout.
 */
void Logout_Member ()
{
	pUser = NULL ;
}


/*
 * End Program.
 */
void Program_End ()
{
	exit ( 1 ) ;
}


/*
 * Print User's Borrow List.\n
 */
void My_Borrow_List ()
{
	int iMyBorrow = 0 ;
	Book * pBookNode = pBookHead ;
	Borrow * pBorrowNode = pBorrowHead ;


	while ( pBorrowNode -> m_pNext != pBorrowTail )
	{
		pBorrowNode = pBorrowNode -> m_pNext ;


		if ( pUser -> m_iStudentNum == pBorrowNode -> m_iStudentNum )
		{
			++ iMyBorrow ;
		}
	}
	if ( iMyBorrow )
	{
		pBorrowNode = pBorrowHead ;

		
		while ( iMyBorrow )
		{
			pBorrowNode = pBorrowNode -> m_pNext ;


			if ( pUser -> m_iStudentNum == pBorrowNode -> m_iStudentNum )
			{
				while ( pBookTail != pBookNode -> m_pNext )
				{
					pBookNode = pBookNode -> m_pNext ;


					if ( pBorrowNode -> m_iBookNum == pBookNode -> m_iBookNum )
						break ;
				}
				Print_Borrow_Information ( pBorrowNode , pBookNode ) ;
				
				-- iMyBorrow ;
			}
		}
	}
}


/*
 * Modify User's Information.
 * User can modify only Password, Address, and Phone Number.
 */
void Modify_Member ()
{
	char cTemp [ 50 ] ;
	FILE * fClient = NULL ;


	printf ( "Modify user's information except Student Number, and User Name.\n" ) ;
	printf ( "Password : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	strncpy ( pUser -> m_cPassword , cTemp , strlen ( cTemp ) ) ;
	pUser -> m_cPassword [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Address : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	strncpy ( pUser -> m_cAddress , cTemp , strlen ( cTemp ) ) ;
	pUser -> m_cAddress [ strlen ( cTemp ) ] = '\0' ;

	printf ( "Phone Number : " ) ;
	gets ( cTemp ) ;
	fflush ( stdin ) ;
	strncpy ( pUser -> m_cNumber , cTemp , strlen ( cTemp ) ) ;
	pUser -> m_cNumber [ strlen ( cTemp ) ] = '\0' ;


	fClient = fopen ( "Client.txt" , "w+" ) ;
	File_Save ( fClient , 1 ) ;
	fclose ( fClient ) ;


	printf ( "Modify End.\n" ) ;
}


/*
 * Quit Member.
 * If user borrow the book, user can't quit.
 */
void Quit_Member ()
{
	Client * pEliPrev = pUser -> m_pPrev ;
	Client * pEliNext = pUser -> m_pNext ;
	Borrow * pBorrowNode = pBorrowHead ;
	FILE * fClient = NULL ;


	while ( pBorrowTail != pBorrowNode -> m_pNext )
	{
		pBorrowNode = pBorrowNode -> m_pNext ;


		if ( pUser -> m_iStudentNum == pBorrowNode -> m_iStudentNum )
			break ;
	}

	if ( pBorrowTail == pBorrowNode -> m_pNext )
	{
		pEliPrev -> m_pNext = pEliNext ;
		pEliNext -> m_pPrev = pEliPrev ;
		-- iClientCount ;

		free ( pUser -> m_cAddress ) ;
		free ( pUser -> m_cName ) ;
		free ( pUser -> m_cNumber ) ;
		free ( pUser -> m_cPassword ) ;

		free ( pUser ) ;


		fClient = fopen ( "Client.txt" , "w+" ) ;
		File_Save ( fClient , 1 ) ;
		fclose ( fClient ) ;


		pUser = NULL ;
	}
	else
	{
		printf ( "User already borrowed the book. User can't quit.\n" ) ;
	}
}


/*
 * Print One User's Information.
 */
void Print_User ( Client * pNode )
{
	if ( NULL != pNode )
	{
		printf ( "\nStudent Number : %d\n" , pNode -> m_iStudentNum ) ;
		printf ( "User Name : %s\n" , pNode -> m_cName ) ;
		printf ( "Address : %s\n" , pNode -> m_cAddress ) ;
		printf ( "Phone Number : %s\n" , pNode -> m_cNumber ) ;
	}
}


/*
 * Print Book Information.
 */
void Print_Book_Information ( Book * pNode )
{
	if ( NULL != pNode )
	{
		printf ( "Book Number : %d\n" , pNode -> m_iBookNum ) ;
		printf ( "Book Name : %s\n" , pNode -> m_cName ) ;
		printf ( "Publisher : %s\n" , pNode -> m_cPublisher ) ;
		printf ( "Author : %s\n" , pNode -> m_cAuthor ) ;
		printf ( "ISBN : %s\n" , pNode -> m_cISBN ) ;
		printf ( "Holding Institution : %s\n" , pNode -> m_cHoldingInstitution ) ;
		printf ( "Eliminate or Borrow Possbile : %c\n" , pNode -> m_cBorrow ) ;	
	}
	else
	{
		printf ( "That book doesn't exist.\n" ) ;
	}
}


/*
 * Print Borrow Book's Information.
 */
void Print_Borrow_Information ( Borrow * pBorrowNode , Book * pBookNode )
{
	if ( ( NULL != pBorrowNode ) && ( NULL != pBookNode ) )
	{
		printf ( "Book Number : %d\n" , pBookNode -> m_iBookNum ) ;
		printf ( "Book Name : %s\n" , pBookNode -> m_cName ) ;
		printf ( "Borrow Date : %ld\n" , pBorrowNode -> m_tBorrowDate ) ;
		printf ( "Return Date : %ld\n\n" , pBorrowNode -> m_tReturnDate ) ;
	}
}


/*
 * free all malloc.
 */
void All_free ()
{
	Client * pClientNode = pClientHead ;
	Book * pBookNode = pBookHead ;
	Borrow * pBorrowNode = pBorrowHead ;


	while ( pClientTail != ( pClientNode -> m_pNext ) )
	{
		pClientNode = pClientNode -> m_pNext ;

		free ( pClientNode -> m_cAddress ) ;
		free ( pClientNode -> m_cName ) ;
		free ( pClientNode -> m_cNumber ) ;
		free ( pClientNode -> m_cPassword ) ;

		free ( pClientNode -> m_pPrev ) ;
	}
	while ( pBookTail != ( pBookNode -> m_pNext ) )
	{
		pBookNode = pBookNode -> m_pNext ;

		free ( pBookNode -> m_cAuthor ) ;
		free ( pBookNode -> m_cHoldingInstitution ) ;
		free ( pBookNode -> m_cName ) ;
		free ( pBookNode -> m_cPublisher ) ;

		free ( pBookNode -> m_pPrev ) ;
	}
	while ( pBorrowTail != ( pBorrowNode -> m_pNext ) )
	{
		pBorrowNode = pBorrowNode -> m_pNext ;

		free ( pBorrowNode -> m_pPrev ) ;
	}

	free ( pClientNode -> m_pNext ) ;
	free ( pClientNode ) ;
	free ( pBookNode -> m_pNext ) ;
	free ( pBookNode ) ;
	free ( pBorrowNode -> m_pNext ) ;
//	free ( pBorrowNode ) ;
}


/*
 * main Function.
 */
int main ()
{
	int iInput = 0 ;
	int iNum = 0 ;
	int iMenu = 0 ;
	bool bKeep = true ;
	FILE * fClient = fopen ( "Client.txt" , "r+" ) ;
	FILE * fBook = fopen ( "Book.txt" , "r+" ) ;
	FILE * fBorrow = fopen ( "Borrow.txt" , "r+" ) ;


	pClientHead = ( Client * ) malloc ( sizeof ( Client ) ) ;
	pClientTail = ( Client * ) malloc ( sizeof ( Client ) ) ;
	pBookHead = ( Book * ) malloc ( sizeof ( Book ) ) ;
	pBookTail = ( Book * ) malloc ( sizeof ( Book ) ) ;
	pBorrowHead = ( Borrow * ) malloc ( sizeof ( Borrow ) ) ;
	pBorrowTail = ( Borrow * ) malloc ( sizeof ( Borrow ) ) ;
	
	
	if ( NULL == fClient )
	{
		fClient = fopen ( "Client.txt" , "w+" ) ;
	}
	if ( NULL == fBook )
	{
		fBook = fopen ( "Book.txt" , "w+" ) ;
	}
	if ( NULL == fBorrow )
	{
		fBorrow = fopen ( "Borrow.txt" , "w+" ) ;
	}


	pClientHead -> m_pPrev = NULL ;
	pClientHead -> m_pNext = pClientTail ;
	pClientTail -> m_pPrev = pClientHead ;
	pClientTail -> m_pNext = NULL ;

	pBookHead -> m_pPrev = NULL ;
	pBookHead -> m_pNext = pBookTail ;
	pBookTail -> m_pPrev = pBookHead ;
	pBookTail -> m_pNext = NULL ;

	pBorrowHead -> m_pPrev = NULL ;
	pBorrowHead -> m_pNext = pBorrowTail ;
	pBorrowTail -> m_pPrev = pBorrowHead ;
	pBorrowTail -> m_pNext = NULL ;


	File_Load ( fClient , 1  ) ;
	fclose ( fClient ) ;
	File_Load ( fBook , 2 ) ;
	fclose ( fBook ) ;
	File_Load ( fBorrow , 3 ) ;
	fclose ( fBorrow ) ;



	while ( bKeep )
	{
		if ( 0 == iMenu )
		{
			ServiceMenu_Print () ;

			printf ( "Input Menu : " ) ;
			scanf ( "%d" , & iInput ) ;

			getchar();
			fflush ( stdin ) ;


			switch ( iInput )
			{
				case 1 :
					Re_ServiceMenu_Print ( iInput ) ;
					Register_Member () ;
					ServiceMenu_Print () ;

					break ;

				case 2 :
					Re_ServiceMenu_Print ( iInput ) ;
					Login_Member () ;

					if ( NULL == pUser )
						;
					else if ( pClientHead == pUser )
					{
						iMenu = 1 ;
					}
					else
					{
						iMenu = 2 ;
					}

					break ;

				case 3 :
					Re_ServiceMenu_Print ( iInput ) ;
					bKeep = false ;

					break ;

				default :
					system ( "clear" ) ;
					ServiceMenu_Print () ;

					break ;
			}
		}
		else if ( 1 == iMenu )
		{
			ServiceAdmin_Print () ;

			printf ( "Input Menu : " ) ;

			scanf ( "%d" , & iInput ) ;
			getchar();

			fflush ( stdin ) ;


			switch ( iInput )
			{
				case 1 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Register_Book () ;

					break ;
				case 2 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Eliminate_Book () ;
					
					break ;
				case 3 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Borrow_Book () ;
					
					break ;
				case 4 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Return_Book () ;
					
					break ;
				case 5 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Print_Book_Information ( Search_Book ( 0 , false ) ) ;
					
					break ;
				case 6 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Search_Client ( ) ;
					
					break ;
				case 7 :
					Re_ServiceAdmin_Print ( iInput ) ;
					Logout_Member () ;
					iMenu = 0 ;
					
					break ;
				case 8 :
					Re_ServiceAdmin_Print ( iInput ) ;
					bKeep = false ;
					
					break ;

				default :
					system ( "clear" ) ;
					ServiceAdmin_Print () ;

					break ;
			}
		}
		else
		{
			ServiceUser_Print () ;
			
			
			printf ( "Input Menu : " ) ;

			scanf ( "%d" , & iInput ) ;
			getchar();

			fflush ( stdin ) ;


			switch ( iInput )
			{
				case 1 :
					Re_ServiceUser_Print ( iInput ) ;
					Print_Book_Information ( Search_Book ( 0 , false ) ) ;

					break ;
				case 2 :
					Re_ServiceUser_Print ( iInput ) ;
					My_Borrow_List () ;

					break ;
				case 3 :
					Re_ServiceUser_Print ( iInput ) ;
					Modify_Member () ;
					
					break ;
				case 4 :
					Re_ServiceUser_Print ( iInput ) ;
					Quit_Member () ;
					iMenu = 0 ;

					break ;
				case 5 :
					Re_ServiceUser_Print ( iInput ) ;
					Logout_Member () ;
					iMenu = 0 ;
					
					break ;
				case 6 :
					Re_ServiceUser_Print ( iInput ) ;
					bKeep = false ;
					
					break ;

				default :
					system ( "clear" ) ;
					ServiceUser_Print () ;

					break ;
			}

		}
	}


	fClient = fopen ( "Client.txt" , "w+" ) ;
	fBook = fopen ( "Book.txt" , "w+" ) ;
	fBorrow = fopen ( "Borrow.txt" , "w+" ) ;


	File_Save ( fClient , 1 ) ;
	File_Save ( fBook , 2 ) ;
	File_Save ( fBorrow , 3 ) ;


	fclose ( fClient ) ;
	fclose ( fBook ) ;
	fclose ( fBorrow ) ;

	All_free () ;
}
