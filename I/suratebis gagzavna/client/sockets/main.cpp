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
#include"getSaveFilename.cpp"
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
    Addr.sin_addr.s_addr = inet_addr("188.169.18.47");
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
		const char *pathf=save();
		 MessageBox(0,pathf,pathf,0);

        FILE *File;
        File = fopen(pathf, "wb");


		int hghg;
		float jhbjhb;
        fwrite((const char*)Buffer, 1, Size, File);
        fclose(File);
    }

    getchar();
    closesocket(Socket);
    WSACleanup();
    return 0;
}

