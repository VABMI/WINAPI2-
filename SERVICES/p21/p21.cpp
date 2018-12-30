


#include <windows.h>
#include <stdio.h>

HFONT hfont_global;
#include "ServisFunc.cpp"
#include "mouse_msg.cpp"

#include "on_create.cpp"
 
#include<iostream>
using namespace std;
BOOL ProcessStarted = TRUE;
//----------------------------------------------------------------
SC_HANDLE h_SCM = ::OpenSCManager (NULL,SERVICES_ACTIVE_DATABASE,SC_MANAGER_ALL_ACCESS);
SC_HANDLE OpnSrs;
char *serviceName="BBB";
char *DSPLName="BBB000";
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
////////////////////////////////////////
SERVICE_TABLE_ENTRY		lpServiceStartTable[] = 
{
	{serviceName, ServiceMain},
	{NULL, NULL}
};

SERVICE_STATUS			ServiceStatus; 
SERVICE_STATUS_HANDLE   hServiceStatusHandle;
LPHANDLER_FUNCTION		func;
////////////////////////////////////////
//----------------------------------------------------------------

#include"delete.cpp"	
#include "StopService.cpp"
#include "start.cpp"
//----------------------------------------------------------------
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{
	switch(message)
	{
		case WM_CREATE:
		on_create(hwnd,message,wparam,lparam);
		break;
		
		case WM_COMMAND:
		if(wparam==12)
		{
			OpnSrs=OpenService(h_SCM,serviceName, SERVICE_ALL_ACCESS);
		}

		////// stop ////////
		if(wparam==14)
		{ 
	///
			SERVICE_STATUS status;
			if(ControlService(OpnSrs,SERVICE_CONTROL_STOP,&status))
				{
					CloseServiceHandle(OpnSrs); 
					CloseServiceHandle(h_SCM); 
					return TRUE;
				}

			

		}
		//////////// start //////////
		if(wparam==13)
		{

			
		

		}
		////////////////////// create ////////////////////

		if(wparam==10)
		{
		
		
		SC_HANDLE schService = CreateService
		( 
			h_SCM,
			serviceName,//name
			DSPLName,//service name to display 
			SERVICE_ALL_ACCESS|  GENERIC_READ | GENERIC_EXECUTE,
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			"F:\\WINAPI2-\\ForServise\\Debug\\ForServise.exe",//service's binary
			NULL,//no load ordering group
			NULL,//no tag identifier
			NULL,//no dependencies
			NULL,//LocalSystem account 
			NULL);
		
		
			if (schService==0) 
			{
			long nError =  GetLastError();
			MessageBox(0,"asdasdas","adsada",0);
		
		
			}
		}


		if(11==wparam)
		{


			ServiceDelete();

		}

		break;
		
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_MOUSEMOVE:
		case WM_RBUTTONDBLCLK:
		case WM_LBUTTONDBLCLK:

		break;
		case WM_NCHITTEST:
			//MessageBox(0,"WM_NCHITTEST","WM_NCHITTEST",0);
			break;
		case WM_PAINT:
	
		break;

		case WM_KEYDOWN:
		
		break;
	}
return DefWindowProc(hwnd,message,wparam,lparam);
}
//----------------------------------------------------------------

int __stdcall WinMain(HINSTANCE,HINSTANCE,char *,int)
 //int main()
{
HWND hwnd=0;
int X,Y,W,H;
ULONG style=0;

WNDCLASS wc;
ZeroMemory(&wc,sizeof(WNDCLASS));

wc.style=CS_DBLCLKS;
wc.lpfnWndProc=(WNDPROC)&window_main_function_chvenia;
wc.lpszClassName="12";
wc.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(200,200,200));
wc.hIcon=(HICON)LoadImage(0,"c:\\1.ico",IMAGE_ICON,16,16,LR_LOADFROMFILE);

	if(RegisterClass(&wc)==0)
	{
	MessageBox(hwnd,"RegisterClass error",0,0);
	return 1;
	}


//mtavari fanjara:
style=WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN;
X=10;Y=30;W=700;H=500;
hwnd=CreateWindow("12","Main",style,X,Y,W,H,GetDesktopWindow(),0,0,0);

	
MSG msg;
int s=1;
	while(s!=0)
	{
	s=GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
}


VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	DWORD   status = 0; 
    DWORD   specificError = 0xfffffff; 
 
    ServiceStatus.dwServiceType        = SERVICE_WIN32; 
    ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
    ServiceStatus.dwWin32ExitCode      = 0; 
    ServiceStatus.dwServiceSpecificExitCode = 0; 
    ServiceStatus.dwCheckPoint         = 0; 
    ServiceStatus.dwWaitHint           = 0; 
 
    hServiceStatusHandle = RegisterServiceCtrlHandler(serviceName, func); 
    if (hServiceStatusHandle==0) 
    {

		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "RegisterServiceCtrlHandler failed, error code = %d\n", nError);
	//	WriteLog(pLogFile, pTemp);
        return; 
    } 
 
    // Initialization complete - report running status 
    ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
    ServiceStatus.dwCheckPoint         = 0; 
    ServiceStatus.dwWaitHint           = 0;  
    if(!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) 
    { 
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
	//	WriteLog(pLogFile, pTemp);
    } 


}




///////////////////////////////////////////////////////////////////////////////////

