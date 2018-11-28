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

char *read(char *path);
void  main()
{

char *ipin;

int port = 8080;
string ipAddress="188.169.18.47";
cout<<endl<<"________________ 188.169.18.47 __\n";
cout<<"sheiyvane IP->: ";

cout<<endl<<"sheiyvane PORT_N->:";
	//cin>>port;
cout<<endl<<"________________\n";
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
static bool firststart=0;
HDC hdc=GetDC(GetDesktopWindow());
char buf[4096];
string userInput="lko";




do
{

	char*filee=read("C:\\Users\\vakho1\\Desktop\\Capture.PNG");

		int sendResult = send(sock,filee,strlen(filee)+1,0);
		if(sendResult == SOCKET_ERROR)
		{
			cout<<"error";
		}
	if(sendResult )
	{break;}

	

}while(userInput.size()>0);

}


char *read(char *path)
{	
	char buf[100];
	FILE *file;
	file=fopen(path,"rb");

	
	fseek(file,0,SEEK_END);
	int size=ftell(file);
	fseek(file,0,SEEK_SET);

	 char *cv;	
	 cv=( char*)malloc(size);
	
	if(cv==NULL){

	}
	else
		{
		//	while(fgetc(c,size, 1, file));
		fread(cv,size,1,file);
		cv[size]=0;
		fclose(file);
	}
		return (char*)cv;
}