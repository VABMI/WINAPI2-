				else if(buf[0]=='I'&&buf[1]=='M'&&buf[2]=='G'&&buf[3]=='C')
				{
						int Size;
						char *Filesize = new char[1024];

						if(recv(sock, Filesize, 1024, 0)) // File size
						{
							Size = atoi((const char*)Filesize);
							printf("File size: %d\n", Size);

							free(Filesize);

						}

				  char *Buffer = new char[Size];

					if(recv(sock, Buffer, Size, 0)) // File Binary
					{
											
						FILE *File;
						File = fopen("aa.bmp", "wb");

						fwrite((const char*)Buffer, 1, Size, File);
						fclose(File);
					}
									/////////////////// failshi chawera //////////////
				//	send(sock,buf,bytesIn,0);
					////////////////////////////////////////////////////
				}