		if(sock==listening)
			{
					
				////accept a new connection
				SOCKET client=accept(listening,nullptr,nullptr);
				//Add the new connection tothelisof connected clients

				FD_SET(client,&master);

				ZeroMemory(cbuff,sizeof(cbuff));
				sprintf(cbuff,"%i",count);
			//	strcat(countbuf,cbuff);
				//strcat(countbuf,"\r\n");
				send(client,cbuff,strlen(cbuff)+1,0);
				count++;
				///Sleep(100);
				send(client,cbuff,strlen(cbuff)+1,0);

			}
