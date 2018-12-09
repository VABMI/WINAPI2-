					if(buf[0]=='*')
					{
						static int Cbuf;
						char clearr[1000];
					for(int i=0;i<=500;i++)
					{
						clearr[i]=' ';
					}
						TextOut(hdc,50,200,clearr,1000);
						  PAINTSTRUCT ps;
						HDC hdc1 = BeginPaint(GetDesktopWindow(), &ps);

						FillRect(hdc1, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

				//    EndPaint(GetDesktopWindow(), &ps);

				

							SetTextColor(hdc,RGB(239, 2, 2));

							HFONT	hTmp=(HFONT)SelectObject(hdc,hfont);
							//	SetBkMode(hdc,1);
					
							TextOut(hdc,50,200,buf,strlen(buf));
							SendMessage(GetDesktopWindow(),WM_SIZE,0,1);


							userInput="TEXTIS GAMOTANA \n";
							sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
								firststart=1;
							Cbuf=strlen(buf);
							
							/*
							DeleteObject(SelectObject(hdc,hTmp));
							EndPaint(GetDesktopWindow(), &ps);

								SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
								*/
						
					}
					else if(buf[0]=='#')
					{

						SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
						TextOut(hdc,50,200,"                                                                                                  ",strlen("                                                                                                  "));
						userInput="TEXTI WAISHALA\n";
						sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
							firststart=1;
						SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
					}
