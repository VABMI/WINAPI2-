else if(buf[0]=='I'&&buf[1]=='M'&&buf[2]=='G')
{
		send((SOCKET)sock, "sheiyvanet gadmosaweri failis misavarti:\n",strlen("sheiyvanet gadmosaweri failis misavarti:\n"), 0);
		Sleep(100);
		bytesReceived = recv(sock,buf,4096,0);
		int sigrdze=strlen(buf);
	//	
		
		if(buf[sigrdze-2]==13)
		{
				buf[sigrdze-2]='\0';
				//MessageBox(0,buf,buf,0);
		}

		
		
				
		FILE *File;
		///"C:\\Users\\vakho1\\Desktop\\Capture.PNG"
		File = fopen(buf, "rb");
		if(!File)
		{	
			printf("Error while readaing the file\n");
				//	goto End1;
		}
		else
		{

				fseek(File, 0, SEEK_END); /// sigrdzis gagebistvis 
				unsigned long Size = ftell(File);
				fseek(File, 0, SEEK_SET);
				char *Buffer1 = new char[Size];
				fread(Buffer1, Size, 1, File);
				char cSize[MAX_PATH];
				sprintf(cSize, "%i", Size);
				fclose(File);
				send((SOCKET)sock,(const char*)"IMGC", strlen("IMGC"), 0);
				Sleep(100);
				/////////////////// gafartovebis gagzavna ////////////////////.
				/*
					char *fileName = new char[7];
					int i=0;
					while(buf[sigrdze-i]=='.')
					{
					//	MessageBox(0,"asdad","Asdasd",0);
						//strcat(fileName,(char*)buf[sigrdze-i]);
						
					}
						//strcat(fileName,"\0");
				send((SOCKET)sock,(const char*)fileName, strlen(fileName), 0);
				Sleep(100);
				free(fileName);
				*/
				//////////////////////////////////////////////////////
				send((SOCKET)sock, cSize, MAX_PATH, 0); // File size
				Sleep(100);
				send((SOCKET)sock, Buffer1, Size, 0); // File Bin				free(Buffer1);

		//End1:

		}
		



	//	readForImage(buf,(void*)&sock);

}