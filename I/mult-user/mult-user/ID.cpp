				if(buf[0]=='I'&&buf[1]=='D')
				{	
					ZeroMemory(buf,sizeof(buf));
					sprintf(buf,"%i",count);
					send(sock,buf,strlen(buf)+1,0);

				}