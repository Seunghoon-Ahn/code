#ifndef LIBRARY_SERVICE_H
#define LIBRARY_SERVICE_H



#include "Client.h"
#include "Book.h"
#include "Borrow.h"



void File_Load ( FILE * fFile , int iFileCheck ) ;
void File_Save ( FILE * fFile , int iFileCheck ) ;
void ServiceMenu_Print () ;
void ServiceAdmin_Print () ;
void ServiceUser_Print () ;
void Copy_Nto0 ( char * cpOrigin , char * cpCopy , int iOrigin_Index , int iCopy_Index , int iLength ) ;
void Register_Member () ;
Client * Sort_StudentNum_Find_Member ( Client * pNode ) ;
void Login_Member () ;
void Register_Book () ;
Book * Sort_ISBN_Find_Book ( Book * pNode ) ;
void Eliminate_Book () ;
void Eliminate_Borrow ( Borrow * pNode ) ;
void BookNumber_ReSetting () ;
void Borrow_Book () ;
time_t Set_Return_Date ( time_t tTime ) ;
void Return_Book () ;
Client * Search_Client () ;
Book * Search_Book ( int iMenu, bool bReturn ) ;
void Logout_Member () ;
void Program_End () ;
void My_Borrow_List () ;
void Modify_Member () ;
void Quit_Member () ;
void Print_User ( Client * pNode ) ;
void Print_Book_Information ( Book * pNode ) ;
void Print_Borrow_Information ( Borrow * pBorrowNode , Book * pBookNode ) ;
void All_free () ;


Client * pClientHead ;
Client * pClientTail ;
Book * pBookHead ;
Book * pBookTail ;
Borrow * pBorrowHead ;
Borrow * pBorrowTail ;

//static Client * pUser = NULL ;				// Login. NULL is noOne, ClientHead is admin. Other people, that people login.



#endif