// testx.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"


#include <string.h>
#include <stdio.h>      // ǥ������¿� ���� �Լ� ����
#include <stdlib.h>     // C ǥ�� ���̺귯�� ����

 int chk(char cb)        // ���� ���� ����,�� �켱 ������ ���� �ش�.
{
    int i=0;
    switch(cb)                                                             
    {
        case '*' :
        case '/' : i=1; break;
        case '-' :
        case '+' : i=2; break;
        default   : i=3; break;
    }
    return i;
}

 bool com(double *dp, char *buf, double &di)                               
{
    double dk, dv;
    int i, is, ie, j, k, ix = 0;
    dv = di= 0;
    for(k=i=is=j=0; buf[i]!='\0'; i++)
    {
        if(buf[i]<'0' || buf[i]>'9')   // ���ڰ� �ƴϸ�
        { 
            switch(buf[i])                                                       
            {  
                case '*' : dk = di;
                              di=dp[--k]*dk;
                              is=i+1; 
                              break;
                case '/' : dk=di; 
            di=dp[--k]/dk; 
         is=i+1;  
         break;
    case '-' : if(buf[i+1] ==';') 
         {  
          is = i+2; 
          di = -di; 
         }
         else 
         {  
          is = i+1;
          dk =  di; 
          di = dp[--k]-dk;
         }  
         break;
                case '+' : dk=di; di=dp[--k]+dk; is=i+1;  break;
                case ' ' : 
         buf[i]='\0'; 
                           if(is) 
         { 
          dp[k++]=di; 
          di=atof(buf+is); 
          ie=0; 
         }
        else  di=atof(buf); 
        is=i+1 +ix;
           }
       }
    }  
 if( k == 0) return true;
 else false;
}

 bool Start(char* sb, double& effect)  // �Է� ���� ������ ���������� ��ȯ
{
     int i, j, k, x, ie = -1, bi = 0;
     char cb=0, cst[100], buf[1024], sbuf[1024], cbs[50];
     for(i=j=0; sb[i]!='\0'; i++) if(sb[i]!=' ') sb[j++]=sb[i]; sb[j]='\0'; //���Ŀ� ���� �� ������ ����
     strcpy(buf, sb);       // ������ buf�� ����
     for(cb=k=j=i=x=0; buf[i]!='='; i++)  // ������ ������ '=' ���� ������ 
     { 
         cst[k]='\0';  
         switch(buf[i])
         {
            case '(' : x++;
                         if(cb)     // �񱳸� ���ؼ� ��� �ص� ��ȣ�� ������                                               
                         {
                            cst[k++]=cb; // ���ÿ� ����
                            cb=0;
                         }
                         cst[k++]=buf[i];   // ���ÿ� '(' ���� 
                         break;
             case ')' : x--; 
                           if(!cb)  { k--; break; }
                           if(sbuf[j-1]>='0' && sbuf[j-1]<='9') sbuf[j++]=' ';    // ���ڰ� �ƴϸ�      
                           if(chk(cb)<=chk(cst[k-1]))                                  
                          {
                              sbuf[j++]=cb; cb=0;
                              while(cst[--k ]!='(' && k>=0) sbuf[j++]=cst[k]; 
                              if(k) cb=cst[--k ];
                         }
        else if(k) sbuf[j++]=cst[--k];
       for(int ix = 0; ix <= ie; ix++) 
        if(cbs[ix] == k) 
        { 
         if(sbuf[j-1]>='0'&&sbuf[j-1]<='9') sbuf[j++]=' ';
         sbuf[j++]='-'; 
         sbuf[j++]=';'; 
        }
                       break;
   
   case '-' : if( i==0 ) 
        {
         while(buf[++i]>='0' && buf[i]<='9')  sbuf[j++] = buf[i]; 
         sbuf[j++]=' ';
         sbuf[j++]='-';
         sbuf[j++]=';'; 
         i--;
         break;
        }
           else if (buf[i-1] == '(' )                                          
        {
         if(buf[i+1]>='0' && buf[i+1]<='9' )                             
         {
          while(buf[++i]>='0' && buf[i]<='9')  sbuf[j++] = buf[i];    
          sbuf[j++]=' ';
          sbuf[j++]='-';
          sbuf[j++]=';'; 
          i--;
             break;
         }
         else if(buf[i+1]=='(')
         {
          sbuf[j++] = '1'; 
          sbuf[j++]='-';
          sbuf[j++]=';'; 
         }
         break;
        }
            case '+' : 
            case '*' :
            case '/' : if(j>0 && (sbuf[j-1]>='0'&&sbuf[j-1]<='9')) sbuf[j++]=' ';
        if(buf[i+1]=='-')
        {
         if(buf[i+2] == '(') 
         {
          bi = 1;
          cbs[++ie] = k;
         }
         else bi = 2;
        }
                       if(cb) 
        {
            while(chk(cb)<=chk(buf[i]))   

         {
             sbuf[j++]=cb; 
             if(k) 
             { 
              if(cst[k]!='(') 
           { 
            cb=cst[--k ]; 
            continue;
           }     
              else cb=buf[i];
             }          
             else  cb=buf[i];
          break;
         }   
         if(chk(cb)>chk(buf[i])) 
         { 
          cst[k++]=cb; 
          cb= buf[i]; 
         }  
        }
        else cb=buf[i];
        if(bi == 1) 
        {
         i++;
         bi = 0;
        }
        else if(bi == 2)
        {
         bi = 0;
         i+=2;
         while(buf[i]>='0' && buf[i]<='9')  sbuf[j++] = buf[i++];
         sbuf[j++]=' ';
         sbuf[j++]='-';
         sbuf[j++]=';'; 
         i--;
        }
        break;
   default  : if(buf[i]>='0' && buf[i]<='9')  sbuf[j++]=buf[i]; 
                       else return false; break; 
      }
     }
    if(buf[i+1]!='\0' || x) return false;                 

    if(sbuf[j-1]>='0' && sbuf[j-1]<='9') sbuf[j++]=' ';    

    if(cb>0) sbuf[j++]=cb;                                

 
 while(k>0) sbuf[j++] = cst[--k];                       

    sbuf[j--]='\0'; return com((double *) buf, sbuf, effect);
}

 int main( )
{
    double effect; 
    char buf[125]="1+2*(3+5  *6-(2+  3  *4)  +(4*2+4))-((7+5)*4)=", effectx[125];
    printf("���� : %s \r\n", buf);  // �Է� ���� ���� �ֱ� ���ؼ� ���� �ص� ���� ���
    int i=0;
    while(strlen(buf) > 0)  // �Է� �� ���ڰ� ������
  { 
     if( Start(buf, effect) == true )
    {
       sprintf(effectx, "%f", effect) ; 
       i=strlen(effectx);
      while(effectx[--i]!='.') 
      {
         if(effectx[i] == '0') effectx[i] = 0;
         else break;
      }
      if(effectx[i]=='.') effectx[i]=0;
  }
  else strcpy(effectx, "error");                // ���� �� �� �� ���̸�
         printf("��� : %s \r\n", effectx) ;
  printf("���� : ");
  gets(buf);             // ���ڿ��� �Է� �޴´�.
}
return 0;
}





