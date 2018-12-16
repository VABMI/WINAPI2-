#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dos.h>
#include <Windows.h>
int main()
{

	int i=0;
	while(1)
	{
		Sleep(700);
		i++;
		printf("%i\n",i);
	}
	return 0;
}