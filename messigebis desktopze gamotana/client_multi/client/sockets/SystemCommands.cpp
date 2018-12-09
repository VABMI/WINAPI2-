	 if(buf[0]=='~')
				{
					int returns=0;
					buf[0]=' ';
			
					returns=system(buf);


							if(returns ==-1)
							{
								userInput="-1 \n";
								sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
								firststart=1;
							}

					
							if(returns ==0)
							{
								userInput="0 \n";
								sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
								firststart=1;
							}
							if(returns ==1)
							{
								userInput="0 \n";
								sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
								firststart=1;
							}
								firststart=1;
				}	
