// I.cpp : Defines the entry point for the console application.
//

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

void  ServiceInit(DWORD dwArgc,LPTSTR *apArgv);
void ServiceInstall(void);
void ServiceDelete(void);
void ServiceStart(void);
void ServiceStop(void);


int main(int argc, CHAR* argv[])
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
			cout<<"StartStServiceCtrlDispatcher Failed"<<endl;
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
	


 ServiceInit(DWORD dwArgc,LPTSTR *apArgv)
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