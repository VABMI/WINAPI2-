#include<stdio.h>
#include<stdlib.h>
#include <Windows.h>


void main()
{

	struct PR{

		char name[30];
		char lastname[30];
		int age;



	};

	struct PR param1={"name1","lastname1",25};

	FILE *file;
	file=fopen("asss.txt","ab");
	
	fwrite(&param1,sizeof(param1),2,file);
		fclose(file);

	FILE *file1=fopen("asss.txt","rb");
	struct PR param2;
	fread(&param2,sizeof(param2),1,file1);
	fclose(file);
	printf("%s\n%s\n%i\n",param2.name,param2.lastname,param2.age);
	


	system("pause");
}