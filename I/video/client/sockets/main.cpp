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

SOCKET Socket;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(Addr);

int main()
{
    WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

    if(LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
    {
        WSACleanup();
        return 0;
    }

     Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    ZeroMemory(&Addr, sizeof(Addr));    // clear the struct
    Addr.sin_family = AF_INET;    // set the address family
    Addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    Addr.sin_port = htons(8786);    // set the port

    if(connect(Socket, (sockaddr*)&Addr, sizeof(Addr)) < 0)
    {
        printf("Connection failed !\n");
        getchar();
        return 0;
    }

    printf("Connection successful !\n");

    printf("Receiving file .. \n");

    int Size;
    char *Filesize = new char[1024];

    if(recv(Socket, Filesize, 1024, 0)) // File size
    {
        Size = atoi((const char*)Filesize);
        printf("File size: %d\n", Size);
    }

    char *Buffer = new char[Size];

    if(recv(Socket, Buffer, Size, 0)) // File Binary
    {
        FILE *File;
        File = fopen("01.jpg", "wb");
        fwrite((const char*)Buffer, 1, Size, File);
        fclose(File);
    }

    getchar();
    closesocket(Socket);
    WSACleanup();
    return 0;
}


























/*
void  main()
{
char *ipin;
int port = 8786;
string ipAddress="188.169.18.47";
cout<<endl<<"________________ 188.169.18.47 __\n";
cout<<endl<<"sheiyvane PORT_N->:";
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


char buf[4096];
string userInput="asasas";
do
{
	

		
			ZeroMemory(buf,4096);
			int bytesReceived = recv(sock,buf,4096,0);
			if(bytesReceived>0)
			{

				cout<< "SERVER> " <<string(buf,0,bytesReceived)<<endl;

				
	FILE *OUTPUT_FILE;
	OUTPUT_FILE=fopen("C:\\Users\\vakho1\\Desktop\\Capture1.PNG","ab");

	if(OUTPUT_FILE){
			
			fprintf(OUTPUT_FILE,"%",buf);
	}
	fclose(OUTPUT_FILE);







			}



		
	

}while(userInput.size()>0);
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
closesocket(sock);

WSACleanup();
}
*/