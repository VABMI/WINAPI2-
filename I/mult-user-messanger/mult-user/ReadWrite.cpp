
char *Read(char *path,SOCKET client)
{	
	
	FILE *file;
	file=fopen(path,"rb");

	
	fseek(file,0,SEEK_END);
	int size=ftell(file);
	fseek(file,0,SEEK_SET);
	char* buff12=(char*)malloc(size);

	if(buff12==NULL){

	}
	else
		{
			ZeroMemory(buff12,sizeof(buff12));
			fread (buff12,1,size,file);
			//buff12[size]=0;
			char chsize[10];
			sprintf(chsize,"%i",size);
	send(client,(const char*)chsize,strlen(chsize),0);
			Sleep(1000);
	send(client,buff12,size,0);
	
		fclose(file);
	}



		
	free(buff12);
	return 0;
}

int Save(char *file,char *path)
{
	
	FILE *OUTPUT_FILE;
	OUTPUT_FILE=fopen(path,"a+");

	if(OUTPUT_FILE){
		
			// fwrite (file , sizeof(char), strlen(file), OUTPUT_FILE);
			  fputs (file,OUTPUT_FILE);
	}
	
	
	
	fclose(OUTPUT_FILE);



	return 0;
}
char *read1(char *path)
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
		
		fread(cv,size,1,file);
		cv[size]=0;
		fclose(file);
	}
		return (char*)cv;
}