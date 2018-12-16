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

        File = fopen("C:\\Users\\vakho1\\Desktop\\77.mp4", "rb");
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

