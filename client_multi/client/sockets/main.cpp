#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment (lib,"WS2_32.lib")
using namespace std;
typedef struct {
	


}SockStruct,*SockStructP;

DWORD WINAPI RECIVE(void* sock)
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
				cout<< "\nSERVER> " <<string(buf,0,bytesReceived)<<endl;
				}
			



			}





}
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
//closesocket(sock);




}
DWORD WINAPI SEND(void* sock)
{
	string userInput;
	while(1)
	{
		
		

	cout<< "clienti > ";
	getline(cin,userInput);
	if(userInput.size()<=0)
	{
		userInput="sheitane striqoni";
	}
	if(userInput.size() > 0) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
	{
		int sendResult = send((unsigned __int64) sock,userInput.c_str(),userInput.size()+1,0);
		if(sendResult != SOCKET_ERROR)
		{
			

			MessageBox(0,"ar gaigzavna","error",0);

		}
	
	}






	}


}

void  main()
{


	//	FreeConsole();
char *ipin;
//scanf("%s",&ipin);
int port = 8080;
string ipAddress="188.169.18.47";
WSAData data;
WORD ver = MAKEWORD(2,2);
int wsResult = WSAStartup(ver,&data);
if(wsResult != 0)
{

	cerr<<"can't start Winsock, err "<<wsResult<<endl;
	return;
}


SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
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
	//RECIVE((void*)sock);
 // CreateThread(NULL,NULL,SEND,&sock,0,NULL);

	CreateThread(NULL,NULL,RECIVE,&sock,0,NULL);
	
//SEND((void*)sock);

//WSACleanup();
}