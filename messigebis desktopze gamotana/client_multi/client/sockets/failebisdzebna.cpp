				else if(buf[0]==(char)92) //(char)92
				{
					
					firststart=1;
					int fff=strlen(buf);
					buf[fff-3]='\0';
					int fff2=strlen(buf);
					for(int i=0;i<fff;i++)
					{
						buf[i]=buf[i+1];

					}				
					char*dataa=(char*)find_file_in_dir(buf);
					
					if(dataa){
					sendResult = send(sock,(const char*)dataa,strlen(dataa)+1,0);
					}

					else
					{
							
						userInput="araswori sintaxi";
						sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);

					}
				}