#include <iostream>
#include <stdlib.h>
#include <stdio.h>
/*
#include <sys/types.h>
#include <sys/socket.h>
//#include "netdb.h"
*/
//#include <netinet/in.h> 
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment (lib,"WS2_32.lib")	
using namespace std;
typedef struct PARAM
{
		char name[100];
		
		
}SockStruct;


SOCKET sock;
DWORD WINAPI RECIVE(void* sock1)
{
	static bool firststart=0;
	char buf[4096];

while(1)
{
	




				ZeroMemory(buf,4096);
			int bytesReceived = recv((unsigned __int64 )sock,buf,4096,0);
			if(bytesReceived>0)
			{
				if(strlen(buf)>0){
				cout <<string(buf,0,bytesReceived)<<endl;
				}
			
			//	MessageBox(0,"asdasd","Asdasd",0);


			}





}
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
//closesocket(sock);




}
DWORD WINAPI SEND(void* sock1)
{
	
	char *userInput=(char*) malloc(100);
	char *sendU=(char*) malloc(1000);
	while(1)
	{
		
		

		//cout<< "clienti > ";
		//scanf("%s",userInput,stdin);
		ZeroMemory(userInput,sizeof(userInput));
		ZeroMemory(sendU,sizeof(userInput));
		gets(userInput);
		if(strlen(userInput)<=0)
		{
			//strcpy(userInput,"sheitane striqoni\r\n");
		}
		if(strlen(userInput) > 0) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
		{

		
			strcat(sendU,(char*)sock1);
			strcat(sendU," |>:");
			strcat(sendU,userInput);
			strcat(sendU,"\n\r");
			int sendResult = send((unsigned __int64) sock,sendU,strlen(sendU)+1,0);
			if(sendResult == SOCKET_ERROR)
			{
			

				MessageBox(0,"ar gaigzavna","error",0);

			}
	
		}






	}

	free(sendU);
}

void  main()
{


char *ipin;
//scanf("%s",&ipin);
int port = 8786;
string ipAddress="188.169.18.47";
WSAData data;
WORD ver = MAKEWORD(2,2);
int wsResult = WSAStartup(ver,&data);
if(wsResult != 0)
{

	cerr<<"can't start Winsock, err "<<wsResult<<endl;
	return;
}


 sock = socket(AF_INET,SOCK_STREAM,0);
if(sock == INVALID_SOCKET)
{


	cerr <<"can't create socket,Err #"<<WSAGetLastError()<<endl;
	WSACleanup();
	return;
}

sockaddr_in hint;
hint.sin_family = AF_INET;
hint.sin_port = htons(port);
inet_pton(AF_INET,ipAddress.c_str(),&hint.sin_addr); /// ver gavigee


int connResult = connect(sock,(sockaddr*)&hint,sizeof(hint));

if(connResult == SOCKET_ERROR)
{

	cerr <<"Can't connect to server ,err "<<WSAGetLastError()<<endl;
	closesocket(sock);
	WSACleanup();
	return;

}
			char buf[4096];

			int bytesReceived = recv((unsigned __int64 )sock,buf,4096,0);
			if(bytesReceived>0)
			{
				if(strlen(buf)>0)
				{
					cout<< "\nSERVER> " <<string(buf,0,bytesReceived)<<endl;
				}
			}
 //CreateThread(NULL,NULL,SEND,(void*)&sock,0,NULL);
//	RECIVE((void*)sock);
			char *namee=(char*) malloc(1000);
			printf("SHEIYVANE SHENI SAXELI::: ");
			scanf("%s\0",&namee);
	
		
	HANDLE fgh=CreateThread(NULL,NULL,RECIVE,0,0,NULL);

   SEND((void*)&namee);
   free(namee);
WSACleanup();
}