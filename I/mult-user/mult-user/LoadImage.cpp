				else if(buf[0]=='I'&&buf[1]=='M'&&buf[2]=='G'&&buf[3]=='C')
				{		static int CountFile=0;
						ZeroMemory(Filesize,sizeof(Filesize));

						if(recv(sock, Filesize, 1024, 0)) // File size
						{
							Size = atoi((const char*)Filesize);
							printf("File size: %d\n", Size);

							

						}

				  char *Buffer = new char[Size];
				  ZeroMemory(Filesize,sizeof(Filesize));
				  sprintf(Filesize,"%i_FILE.bmp",CountFile);

					if(recv(sock, Buffer, Size, 0)) // File Binary
					{
											
						FILE *File;
						File = fopen(Filesize, "wb");
						fwrite((const char*)Buffer, 1, Size, File);
						fclose(File);
					}
									/////////////////// failshi chawera //////////////
					//send(sock,buf,bytesIn,0);
					ZeroMemory(buf,strlen(buf));
					Sleep(10);
					sprintf(buf,"%s","faili atvirtulia serverze\n");
					bytesIn=strlen(buf);
					CountFile++;
					goto L;
					////////////////////////////////////////////////////
				}