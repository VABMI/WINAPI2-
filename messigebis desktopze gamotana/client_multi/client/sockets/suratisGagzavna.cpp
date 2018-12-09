	else if(buf[0]=='I'&&buf[1]=='M'&&buf[2]=='G')
{
		send((SOCKET)sock, "SURATIS SERVERZE GAGZAVNA ::: SEIYVANE SURATIS MISAMARTI :::", strlen("SURATIS SERVERZE GAGZAVNA ::: SEIYVANE SURATIS MISAMARTI :::"), 0);
		bytesReceived = recv(sock,buf,4096,0);
		MessageBox(0,"asadasd","asdasd",0);

				
				FILE *File;
				

				File = fopen("C:\\Users\\vakho1\\Desktop\\1200x900\\28.jpg", "rb");
				if(!File)
				{
					printf("Error while readaing the file\n");
				//	goto End1;
				}
				else
				{

				fseek(File, 0, SEEK_END);
				unsigned long Size = ftell(File);
				fseek(File, 0, SEEK_SET);

				char *Buffer1 = new char[Size];

				fread(Buffer1, Size, 1, File);
				char cSize[MAX_PATH];
				sprintf(cSize, "%i", Size);

				fclose(File);
				send((SOCKET)sock,(const char*)"IMGC", strlen("IMGC"), 0);
				Sleep(100);
				send((SOCKET)sock, cSize, MAX_PATH, 0); // File size
				Sleep(100);
				send((SOCKET)sock, Buffer1, Size, 0); // File Binary
				free(Buffer1);

		//End1:

				}
		



	//	readForImage(buf,(void*)&sock);

}