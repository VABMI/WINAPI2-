		struct PARAM
					{
						__int64 pauza;
						__int64 start;
						__int64 end;
						char buffer[100];
						char *buffer2;
						HWND Hedit;
						void init()
						{
							buffer2=new char[9999999];
							memset(buffer2,0,sizeof(buffer2));
						}

						void clear()
						{
						//	 delete [] buffer2;

						}
					};