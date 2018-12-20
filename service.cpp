#include "windows.h"
#include "stdio.h"


#define		MAX_NUM_OF_PROCESS		4
/** Window Service **/
VOID ServiceMainProc(char *svc_name);
VOID CreateService(char* pPath, char* pName);
VOID DeleteService(char* pName);
VOID WriteLog(char* pFile, char* pMsg);
BOOL StopService(char* pName);
BOOL StartService(char* pName);
VOID ExecuteSubProcess();
VOID ProcMonitorThread(VOID *);
BOOL StartProcess(int ProcessIndex);
VOID EndProcess(int ProcessIndex);
VOID AttachProcessNames();

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);
int get_service_exepath(wchar_t *svcname);

/** Window Service **/
const int nBufferSize = 500;
CHAR pServiceName[nBufferSize+1];
CHAR pExeFile[nBufferSize+1];
CHAR lpCmdLineData[nBufferSize+1];
CHAR pLogFile[nBufferSize+1];
BOOL ProcessStarted = TRUE;

CRITICAL_SECTION		myCS;

SERVICE_TABLE_ENTRY		lpServiceStartTable[] = 
{
	{pServiceName, ServiceMain},
	{NULL, NULL}
};

/*LPTSTR ProcessNames[] = { "C:\\n.exe",
						 "C:\\a.exe",
						 "C:\\b.exe",
						 "C:\\c.exe" };*/
LPTSTR ProcessNames[MAX_NUM_OF_PROCESS];

SERVICE_STATUS_HANDLE   hServiceStatusHandle; 
SERVICE_STATUS          ServiceStatus; 
PROCESS_INFORMATION	pProcInfo[MAX_NUM_OF_PROCESS];

int main(int argc, char* argv[])
{
//test:get_service_exepath(L"Dhcp");
	if(argc >= 2)
	strcpy(lpCmdLineData, argv[1]);
ServiceMainProc("b_service");
return 0;
}

VOID ServiceMainProc(char *svc_name)
{
::InitializeCriticalSection(&myCS);
// initialize variables for .exe and .log file names
char pModuleFile[nBufferSize+1];
DWORD dwSize = GetModuleFileName(NULL, pModuleFile, nBufferSize);
pModuleFile[dwSize] = 0;
	if(dwSize>4 && pModuleFile[dwSize-4] == '.')
	{
	sprintf(pExeFile,"%s",pModuleFile);
	printf("%s\n",pExeFile);
	pModuleFile[dwSize-4] = 0;
	sprintf(pLogFile,"%s.log",pModuleFile);
	}
strcpy(pServiceName,svc_name);

	if(_stricmp("-i",lpCmdLineData) == 0 || _stricmp("-I",lpCmdLineData) == 0)
	CreateService(pExeFile, pServiceName);
	else if(_stricmp("-k",lpCmdLineData) == 0 || _stricmp("-K",lpCmdLineData) == 0)
	StopService(pServiceName);
	else if(_stricmp("-u",lpCmdLineData) == 0 || _stricmp("-U",lpCmdLineData) == 0)
	DeleteService(pServiceName);
	else if(_stricmp("-s",lpCmdLineData) == 0 || _stricmp("-S",lpCmdLineData) == 0)
	StartService(pServiceName);
	else
	ExecuteSubProcess();
}

VOID CreateService(char* pPath, char* pName)
{  
SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 
	if (schSCManager==0) 
	{
	long nError = GetLastError();
	char pTemp[121];
	sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
	WriteLog(pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = CreateService
		( 
			schSCManager,
			pName,//name
			pName,//service name to display 
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			pPath,//service's binary
			NULL,//no load ordering group
			NULL,//no tag identifier
			NULL,//no dependencies
			NULL,//LocalSystem account 
			NULL);
		if (schService==0) 
		{
		long nError =  GetLastError();
		char pTemp[121];
		sprintf(pTemp, "Failed to create service %s, error code = %d\n", pName, nError);
		WriteLog(pLogFile, pTemp);
		}
		else
		{
		char pTemp[121];
		sprintf(pTemp, "Service %s installed\n", pName);
		WriteLog(pLogFile, pTemp);
		CloseServiceHandle(schService); 
		}
	CloseServiceHandle(schSCManager);
	}	
}

VOID DeleteService(char* pName)
{
SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
	long nError = GetLastError();
	char pTemp[121];
	sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
	WriteLog(pLogFile, pTemp);
	}
	else
	{
	SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenService failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
			char pTemp[121];
			sprintf(pTemp, "Failed to delete service %s\n", pName);
			WriteLog(pLogFile, pTemp);
			}
			else 
			{
			char pTemp[121];
			sprintf(pTemp, "Service %s removed\n",pName);
			WriteLog(pLogFile, pTemp);
			}
		CloseServiceHandle(schService); 
		}
	CloseServiceHandle(schSCManager);	
	}
DeleteFile(pLogFile);
}

VOID WriteLog(char* pFile, char* pMsg)
{
// write error or other information into log file
::EnterCriticalSection(&myCS);
	try
	{
	SYSTEMTIME oT;
	::GetLocalTime(&oT);
	FILE* pLog = fopen(pFile,"a");
	fprintf(pLog,"%02d/%02d/%04d, %02d:%02d:%02d\n    %s",oT.wMonth,oT.wDay,oT.wYear,oT.wHour,oT.wMinute,oT.wSecond,pMsg); 
	fclose(pLog);
	}
	catch(...)
	{
	}
::LeaveCriticalSection(&myCS);
}

BOOL StopService(char* pName) 
{ 
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf(pTemp, "OpenService failed, error code = %d\n", nError);
			WriteLog(pLogFile, pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				char pTemp[121];
				sprintf(pTemp, "ControlService failed, error code = %d\n", nError);
				WriteLog(pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

BOOL StartService(char* pName) 
{ 
	// run service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf(pTemp, "OpenService failed, error code = %d\n", nError);
			WriteLog(pLogFile, pTemp);
		}
		else
		{
			// call StartService to run the service
			if(StartService(schService, 0, (const char**)NULL))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				char pTemp[121];
				sprintf(pTemp, "StartService failed, error code = %d\n", nError);
				WriteLog(pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}


VOID ExecuteSubProcess()
{
	//if(_beginthread(ProcMonitorThread, 0, NULL) == -1)
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "StartService failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}

	if(!StartServiceCtrlDispatcher(lpServiceStartTable))
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "StartServiceCtrlDispatcher failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
::DeleteCriticalSection(&myCS);
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
 
    hServiceStatusHandle = RegisterServiceCtrlHandler(pServiceName, ServiceHandler); 
    if (hServiceStatusHandle==0) 
    {
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "RegisterServiceCtrlHandler failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
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
		WriteLog(pLogFile, pTemp);
    } 

	AttachProcessNames();
	for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
	{
		pProcInfo[iLoop].hProcess = 0;
		StartProcess(iLoop);
	}
}

VOID AttachProcessNames()
{
	LPTSTR lpszpath;
	lpszpath = new char[nBufferSize];
	memset(lpszpath,0x00,sizeof(lpszpath));
	DWORD dwSize = GetModuleFileName(NULL, lpszpath, nBufferSize);
	lpszpath[dwSize] = 0;
	while(lpszpath[dwSize] != '\\' && dwSize != 0)
	{
		lpszpath[dwSize] = 0; dwSize--;
	}
	for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
	{
		ProcessNames[iLoop] = (char*) malloc(nBufferSize);
		memset(ProcessNames[iLoop], 0x00, nBufferSize);
		strcpy(ProcessNames[iLoop],lpszpath); 
	}
	strcat(ProcessNames[0], "1.exe");
	strcat(ProcessNames[1], "2.exe");
	strcat(ProcessNames[2], "3.exe");
	strcat(ProcessNames[3], "4.exe");
}

VOID WINAPI ServiceHandler(DWORD fdwControl)
{
	switch(fdwControl) 
	{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			ProcessStarted = FALSE;
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
			ServiceStatus.dwCheckPoint    = 0; 
			ServiceStatus.dwWaitHint      = 0;
			// terminate all processes started by this service before shutdown
			{
				for(int i = MAX_NUM_OF_PROCESS - 1 ; i >= 0; i--)
				{
					EndProcess(i);
					delete ProcessNames[i];
				}			
			}
			break; 
		case SERVICE_CONTROL_PAUSE:
			ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
			break;
		case SERVICE_CONTROL_CONTINUE:
			ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default:
			if(fdwControl>=128&&fdwControl<256)
			{
				int nIndex = fdwControl&0x7F;
				// bounce a single process
				if(nIndex >= 0 && nIndex < MAX_NUM_OF_PROCESS)
				{
					EndProcess(nIndex);
					StartProcess(nIndex);
				}
				// bounce all processes
				else if(nIndex==127)
				{
					for(int i = MAX_NUM_OF_PROCESS-1; i >= 0; i--)
					{
						EndProcess(i);
					}
					for(i = 0; i < MAX_NUM_OF_PROCESS; i++)
					{
						StartProcess(i);
					}
				}
			}
			else
			{
				char pTemp[121];
				sprintf(pTemp,  "Unrecognized opcode %d\n", fdwControl);
				WriteLog(pLogFile, pTemp);
			}
	};
    if (!SetServiceStatus(hServiceStatusHandle,  &ServiceStatus)) 
	{ 
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
    } 
}
BOOL StartProcess(int ProcessIndex)
{
	STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,"",NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
	startUpInfo.wShowWindow = SW_SHOW;
	startUpInfo.lpDesktop = NULL;
	if(CreateProcess(NULL, ProcessNames[ProcessIndex],NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,\
					 NULL,NULL,&startUpInfo,&pProcInfo[ProcessIndex]))
	{
		Sleep(1000);
		return TRUE;
	}
	else
	{
		long nError = GetLastError();
		char pTemp[256];
		sprintf(pTemp,"Failed to start program '%s', error code = %d\n", ProcessNames[ProcessIndex], nError); 
		WriteLog(pLogFile, pTemp);
		return FALSE;
	}
}


VOID EndProcess(int ProcessIndex)
{
	if(ProcessIndex >=0 && ProcessIndex <= MAX_NUM_OF_PROCESS)
	{
		if(pProcInfo[ProcessIndex].hProcess)
		{
			// post a WM_QUIT message first
			PostThreadMessage(pProcInfo[ProcessIndex].dwThreadId, WM_QUIT, 0, 0);
			Sleep(1000);
			// terminate the process by force
			TerminateProcess(pProcInfo[ProcessIndex].hProcess, 0);
		}
	}
}
VOID ProcMonitorThread(VOID *)
{
	while(ProcessStarted == TRUE)
	{
		DWORD dwCode;
		for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
		{
			if(::GetExitCodeProcess(pProcInfo[iLoop].hProcess, &dwCode) && pProcInfo[iLoop].hProcess != NULL)
			{
				if(dwCode != STILL_ACTIVE)
				{
					if(StartProcess(iLoop))
					{
						char pTemp[121];
						sprintf(pTemp, "Restarted process %d\n", iLoop);
						WriteLog(pLogFile, pTemp);
					}
				}
			}
		}
	}
}


int get_service_exepath(wchar_t *svcname)
{
LPQUERY_SERVICE_CONFIG lpsc;
SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(hSCManager)
	{
	SC_HANDLE hService = OpenServiceW(hSCManager,svcname, SERVICE_QUERY_CONFIG); 
		if(hService)
		{
		//CloseServiceHandle(hSCManager);
		DWORD dwBytesNeeded = 0, dwBufSize;
			if(!QueryServiceConfig(hService, NULL, 0, &dwBytesNeeded))
			{
			DWORD dwError = GetLastError();
				if (ERROR_INSUFFICIENT_BUFFER == dwError)
				{
				dwBufSize = dwBytesNeeded;
				lpsc = (LPQUERY_SERVICE_CONFIG)HeapAlloc(GetProcessHeap(), 0, dwBufSize);
					if (QueryServiceConfig(hService, lpsc, dwBufSize, &dwBytesNeeded))
					{
					MessageBox(0,lpsc->lpBinaryPathName,"SVC Exe Path",0);
					}
				HeapFree(GetProcessHeap(),0,lpsc);
				}
			}
		CloseServiceHandle(hService);
		}
	CloseServiceHandle(hSCManager);
	}
return(0);
}