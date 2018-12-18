// I.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
#define SERVICE_NAME L"ASP Service" ///service name
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


int _tmain(int argc, CHAR* argv[])
{
	cout<<"In main fun Start"<<endl;
	BOOL bStServiceCtrlDispatcher=FALSE;


	if(lstrcmpiA(argv[1],"install")==0)
	{

		ServiceInstall();
		cout<<"Installation Success"<<endl;
	}
	else if(lstrcmpiA(argv[1],"Start")==0)
	{

		ServiceStart();
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

	}
	


	cout<<"In main fun End"<<endl;
	system("pause");

	return 0;
}




void WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpArgv)
{
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

	cout<<"Service End"<<endl;
}




void WINAPI ServiceControlHandler(DWORD dwControl)
{


	cout<<"ServiceControlHandler"<<endl;
	switch(dwControl)
	{
	case SERVICE_CONTROL_STOP:
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

	while(1)
	{
		WaitForSingleObject(hServiceEvent,INFINITE);

		ServiceReportStatus(SERVICE_STOPPED,NO_ERROR,0);
	}
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
		hOpenService,
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

void ServiceStop(void)
{
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