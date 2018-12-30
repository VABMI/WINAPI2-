// I.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "commctrl.h"
#pragma comment (lib,"WS2_32.lib")	
using namespace std;
#define SERVICE_NAME L"AAA_20" ///service name
SERVICE_STATUS ServiceStatus={0};
SERVICE_STATUS_HANDLE hServiceStatusHandle=NULL;
HANDLE hServiceEvent=NULL;
void WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpArgv);
void WINAPI ServiceControlHandler(DWORD dwControl);
void ServiceReportStatus(
	DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwWaitHint);

void ServiceInit(DWORD dwArgc,LPTSTR *apArgv);
void ServiceInstall(void);
void ServiceDelete(void);
void ServiceStart(void);
void ServiceStop(void);
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam);
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message, unsigned int wparam,long lparam);
int mainA1();
int main(int argc, CHAR* argv[])
{
	cout<<"In main fun Start"<<endl;
	BOOL bStServiceCtrlDispatcher=FALSE;
	//ServiceStart();
	
	if(lstrcmpiA(argv[1],"install")==0)
	{

		ServiceInstall();
		cout<<"Installation Success"<<endl;
		ServiceStart();
	}
	else if(lstrcmpiA(argv[1],"Start")==0)
	{

		ServiceStart();
			/// mainA1();
		cout<<"ServiceStart Success"<<endl;

	}
	else if(lstrcmpiA(argv[1],"stop")==0)
	{

		ServiceStop();
		cout<<"ServiceStart Stop"<<endl;


	}
	else if(lstrcmpiA(argv[1],"Delete")==0)
	{
		ServiceDelete();
		cout<<"ServiceStart Delete"<<endl;


	}
	else 
	{
		/////Step I
		
		SERVICE_TABLE_ENTRY DispatchTable[]=
		{
			{SERVICE_NAME,(LPSERVICE_MAIN_FUNCTION)ServiceMain},
			{NULL,NULL}
		};
		///Step II
		bStServiceCtrlDispatcher=StartServiceCtrlDispatcher(DispatchTable);

		if(FALSE==bStServiceCtrlDispatcher)
		{
			cout<<"StartStServiceCtrlDispatcher Failed"<<GetLastError()<<endl;
		}
		else
		{
			cout<<"StartStServiceCtrlDispatcher Success"<<endl;

		}
		
			///	ServiceStart();
		// mainA1();
		// window_main_function_chvenia(0,0, 0,0);
	}
	

	
	cout<<"In main fun End"<<endl;
	system("pause");

	return 0;
}




void WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpArgv)
{	//system("C:\\Users\\vakhoo\\Desktop\\1.mp4");

	cout<<"ServiceMain Start"<<endl;
	BOOL bServiceStatus=FALSE;
	hServiceStatusHandle=RegisterServiceCtrlHandler
		(
		SERVICE_NAME,
		ServiceControlHandler);


	if(NULL==hServiceStatusHandle)
	{
		cout<<"RegisterServiceCtrlHandler Faild"<<endl;
	}
	else
	{
			cout<<"RegisterServiceCtrlHandler Success"<<endl;

	}
	ServiceStatus.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
	ServiceStatus.dwServiceSpecificExitCode=0;
	
	ServiceReportStatus(SERVICE_START_PENDING,NO_ERROR,3000);

	bServiceStatus=SetServiceStatus(hServiceStatusHandle,&ServiceStatus);
	if(bServiceStatus==FALSE)
	{
		cout<<"Service Status initial Setup FAILED =" <<GetLastError()<<endl;
	}
	else
	{

			cout<<"Service Status initial Setup SUCCESS ="<<endl;
	}
	ServiceInit(dwArgc,lpArgv);
	///	system("C:\\Users\\vakhoo\\Desktop\\1.mp4");
	cout<<"Service End"<<endl;
}




void WINAPI ServiceControlHandler(DWORD dwControl)
{
///		system("C:\\Users\\vakhoo\\Desktop\\1.mp4");

	cout<<"ServiceControlHandler"<<endl;
	switch(dwControl)
	{
	case SERVICE_CONTROL_SHUTDOWN :
	case SERVICE_CONTROL_CONTINUE  :
	case SERVICE_CONTROL_STOP:
		//MessageBox(0,0,0,0);
	//	system("C:\\Users\\vakhoo\\Desktop\\1.mp4");
		ServiceReportStatus(SERVICE_STOPPED,NO_ERROR,0);
		cout<<"Service stopped"<<endl;
		break;
	default:

		break;
		cout<<"ServiceControlHandler"<<endl;

	}
}

void ServiceReportStatus(
	DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwWaitHint)
{

	cout<<"ServiceReportStatus start"<<endl;

	static DWORD dwCheckPoint=1;
	BOOL bSetServiceStatus=FALSE;
	ServiceStatus.dwCurrentState=dwCurrentState;
	ServiceStatus.dwWin32ExitCode=dwWin32ExitCode;
	ServiceStatus.dwWaitHint=dwWaitHint;
	if(dwCurrentState==SERVICE_START_PENDING)
	{
		ServiceStatus.dwControlsAccepted=0;
	}
	else
	{
		ServiceStatus.dwControlsAccepted=SERVICE_ACCEPT_STOP;
	}
	///STEP 3
	if((dwCurrentState==SERVICE_RUNNING)||(dwCurrentState==SERVICE_STOPPED))
	{
		ServiceStatus.dwCheckPoint=0;
	}
	else
	{

		ServiceStatus.dwCheckPoint=dwCheckPoint++;
	}
	/// STEP 4
	bSetServiceStatus=SetServiceStatus(hServiceStatusHandle,&ServiceStatus);
	if(bSetServiceStatus==FALSE)
	{
		cout<<"service status faild="<<GetLastError()<<endl;
	}
	else
	{
			cout<<"service status success "<<endl;
	}
}
	


void ServiceInit(DWORD dwArgc,LPTSTR *apArgv)
{
	cout<<"Service Start"<<endl;
	hServiceEvent=CreateEvent(
		NULL,//secure attribute
		TRUE,//MANUAL Reset Event
		FALSE, // Non signaled
		NULL); //
	if(NULL==hServiceEvent)
	{
		ServiceReportStatus(SERVICE_STOPPED,NO_ERROR,0);
	}
	else
	{
		ServiceReportStatus(SERVICE_RUNNING,NO_ERROR,0);
	}
//	MessageBox(0,0,0,0);
	//	system("C:\\Users\\vakhoo\\Desktop\\1.mp4");
	/*
	while(1)
	{
		WaitForSingleObject(hServiceEvent,INFINITE);
		///	system("C:\\Users\\vakhoo\\Desktop\\1.mp4");
		ServiceReportStatus(SERVICE_STOPPED,NO_ERROR,0);
	}

	*/
	  HANDLE hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
   
    // Wait until our worker thread exits signaling that the service needs to stop
    WaitForSingleObject (hThread, INFINITE);
}



////////// service install
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
void ServiceDelete(void)
{

	cout<<"ServiceDelete Start"<<endl;
	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScOpenService = NULL;
	BOOL bDeleteService = FALSE;

	hScOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS);

	if(NULL==hScOpenSCManager)
	{
		cout<<"hScOpenSCManager Failed ="<<GetLastError()<<endl;
	}
	else
	{
		cout<<"hScOpenSCManager Success"<<endl;
	}

	hScOpenService=OpenService(
		hScOpenSCManager,
		SERVICE_NAME,
		SERVICE_ALL_ACCESS);
	if(NULL==hScOpenService)
	{
			cout<<"hScOpenService Failed ="<<GetLastError()<<endl;
	}
	else
	{
			cout<<"hScOpenService Success"<<endl;
	}

	bDeleteService=DeleteService(hScOpenService);
	if(FALSE==bDeleteService)
	{

		cout<<"DeleteService Failed ="<<GetLastError()<<endl;

	}
	else
	{
		cout<<"DeleteService Success"<<endl;
	}

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
		//MessageBox(0,0,0,0);
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

void ServiceStop(void)
{//	system("C:\\Users\\vakhoo\\Desktop\\1.mp4");
	cout<<"Inside Service Stop"<<endl;
	SERVICE_STATUS_PROCESS SvcStatusProcess;
	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScOpenService = NULL;
	BOOL bQueryServiceStatus = TRUE;
	BOOL bControlService = TRUE;
	DWORD dwBytesNeeded;
	///I
	hScOpenSCManager=OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS);
	if(NULL==hScOpenSCManager)
	{
		cout<<"hScOpenSCManager Faild..."<<GetLastError()<<endl;
	}
	else
	{

		cout<<"hScOpenSCManager Success"<<endl;
	}

	//II
	hScOpenService=OpenService(
		hScOpenSCManager,
		SERVICE_NAME,
		SERVICE_ALL_ACCESS);
	if(NULL==hScOpenService)
	{
			cout<<"hScOpenService Failed ="<<GetLastError()<<endl;
			CloseServiceHandle(hScOpenSCManager);
	}
	else
	{
			cout<<"hScOpenService Success"<<endl;
	}


	//III
		bQueryServiceStatus=QueryServiceStatusEx(
		hScOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded);
		if(FALSE ==bQueryServiceStatus)
		{
			cout<<"QueryServiceStatusEx Faild ="<<GetLastError()<<endl;
			CloseServiceHandle(hScOpenService);
			CloseServiceHandle(hScOpenSCManager);
		}
		else
		{
			cout<<"QueryService Success"<<endl;
				
		}
		////// IV////////////////

		bControlService=ControlService(
			hScOpenService,
			SERVICE_CONTROL_STOP,
			(LPSERVICE_STATUS)&SvcStatusProcess
			
			);
		if(TRUE == bControlService)
		{
			cout<<"Control Service Success"<<endl;
		}
		else
		{
			cout<<"Control Service Faild= "<<GetLastError()<<endl;
			CloseServiceHandle(hScOpenService);
			CloseServiceHandle(hScOpenSCManager);
		
		}

		//////V//////
		while(SvcStatusProcess.dwCurrentState!=SERVICE_STOPPED)
		{/// VI
			//	system("C:\\Users\\vakhoo\\Desktop\\1.mp4");
		///	MessageBox(0,0,0,0);
			bQueryServiceStatus=QueryServiceStatusEx(
				hScOpenService,
				SC_STATUS_PROCESS_INFO,
				(LPBYTE)&SvcStatusProcess,
				sizeof(SERVICE_STATUS_PROCESS),
				&dwBytesNeeded);

			if(TRUE == bQueryServiceStatus)
			{
				cout<<"bQueryServiceStatus Faild= "<<GetLastError()<<endl;
				CloseServiceHandle(hScOpenService);
				CloseServiceHandle(hScOpenSCManager);
			}
			else
			{
				cout<<"bQueryServiceStatus Success"<<endl;

					
			}
			//// VII
			if(SvcStatusProcess.dwCurrentState == SERVICE_STOPPED)
			{
				cout<<"Srvice Stopped Successfully"<<endl;
				break;
			}
			else
			{
					cout<<"Service Stop Faild"<<endl;
						CloseServiceHandle(hScOpenService);
				CloseServiceHandle(hScOpenSCManager);
			}


		} /// while 

		// VIII
				CloseServiceHandle(hScOpenService);
				CloseServiceHandle(hScOpenSCManager);
				cout<<"Service Stop"<<endl;
}


//----------------------------------------------------------------
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message, unsigned int wparam,long lparam)
{

	
	if(message==WM_USER+200)
	{
		if(lparam==WM_RBUTTONDOWN)
		{
		MessageBox(0,0,0,0);
		}
	}
	switch(message)
	{

		
		case WM_CREATE:
			{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			  // handle to icon
				 HBITMAP hIcon;
			  // text for tool tip
				 wchar_t lpszTip[] = L"Mouse is on the Icon !!";
 
			//	 HINSTANCE hInst =
				//	 AfxFindResourceHandle(MAKEINTRESOURCE(IDI_ICON1),RT_GROUP_ICON);

				 hIcon = (HBITMAP)LoadImage( NULL,
										   L"D:\\WINAPI2-\\DesktopMessanger\\Glove Normal.ico",
										   IMAGE_ICON,
										   16,
										   16,
										   LR_LOADFROMFILE);





			///	 (HBITMAP)LoadImage(NULL,"C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\MARBLES.BMP", IMAGE_BITMAP,300,300, LR_LOADFROMFILE);
				 if(hIcon)
				 {
    
					  // set NOTIFYCONDATA structure
 
						 NOTIFYICONDATA tnid;
 
						 tnid.cbSize = sizeof(NOTIFYICONDATA);
						 tnid.hWnd = hwnd;
						 tnid.uID = 0;
						 tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
						 tnid.uCallbackMessage = WM_USER+200; // my user message
						 tnid.hIcon =(HICON) hIcon;
						
						 if (lpszTip)
							lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip));
						 else
							tnid.szTip[0] = '\0';
 
					  // call to Shell_NotifyIcon with NIM_ADD parameter
 
						 Shell_NotifyIcon(NIM_ADD, &tnid);
 
					  // free icon 
 
						 ///if (hIcon) 
					//	 DestroyIcon(hIcon); 
				 }
			

			break;
			}
			
		case WM_CLOSE:
			exit(1);
			break;


	}
return DefWindowProc(hwnd,message,wparam,lparam);
}





 int mainA1()
{
	HWND hwnd=0;
	int X,Y,W,H;
	ULONG style=0;

	WNDCLASS wcex		= { 0 };
	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc		= window_main_function_chvenia;
	wcex.hInstance		= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"12";
	if(RegisterClass(&wcex)==0)
	{
	MessageBox(hwnd,L"RegisterClass error",0,0);
	return 1;
	}


//mtavari fanjara:
style=WS_VISIBLE |WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW;


hwnd=CreateWindow(wcex.lpszClassName,L"Main",style|WS_CLIPCHILDREN|WS_VISIBLE,0,0,100,100,0,0,0,0);

MSG msg;
int s=1;
	while(s!=0)
	{
	s=GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
	return 1;
}
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam)
{
    //  Periodically check if the service has been requested to stop
    while (1)
    {        
        /* 
         * Perform main service function here
         */
			MessageBox(0,0,0,0);
        //  Simulate some work by sleeping
        Sleep(3000);
    }
 
    return ERROR_SUCCESS;
} 