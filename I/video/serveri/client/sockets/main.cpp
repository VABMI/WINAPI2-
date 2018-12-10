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

SOCKET Socket, Sub;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(sockaddr_in);
char Buffer[256];
char *Str;
sockaddr_in IncomingAddress;
int AddressLen = sizeof(IncomingAddress);

int main()
{
    WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

    if(LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
    {
        WSACleanup();
        return 0;
    }

     Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    ZeroMemory(&Addr, sizeof(Addr));
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(8786);  
    bind(Socket, (sockaddr*)&Addr, sizeof(Addr));

    if(listen(Socket, 1) == SOCKET_ERROR)
    {
        printf("listening error\n");
    }
    else
    {
        printf("listening ok\n");
    }

    if(Sub = accept(Socket, (sockaddr*)&IncomingAddress, &AddressLen))
    {
        char *ClientIP = inet_ntoa(IncomingAddress.sin_addr);
        int ClientPort = ntohs(IncomingAddress.sin_port);
        printf("Client conncted!\n");
        printf("IP: %s:%d\n", ClientIP, ClientPort);

        printf("Sending file .. \n");


        FILE *File;
        char *Buffer;
        unsigned long Size;

        File = fopen("C:\\Users\\vakho1\\Desktop\\ONE MINUTE OF PURE SATISFACTION - Compilation 1.mp4", "rb");
        if(!File)
        {
            printf("Error while readaing the file\n");
            goto End;
        }

        fseek(File, 0, SEEK_END);
        Size = ftell(File);
        fseek(File, 0, SEEK_SET);

        Buffer = new char[Size];

        fread(Buffer, Size, 1, File);
        char cSize[MAX_PATH];
        sprintf(cSize, "%i", Size);

        fclose(File);

        send(Sub, cSize, MAX_PATH, 0); // File size
        send(Sub, Buffer, Size, 0); // File Binary
        free(Buffer);

End:
        closesocket(Sub);
        closesocket(Socket);
        WSACleanup();
    }

    getchar();
    return 0;
}



















/*
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

*/