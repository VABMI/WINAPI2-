// Main function to be executed as entire service code.
/*
SERVICE_STATUS_HANDLE g_ServiceStatusHandle; 
HANDLE g_StopEvent;
DWORD g_CurrentState = 0;
bool g_SystemShutdown = false;

void ReportStatus(DWORD state)
{
    g_CurrentState = state;
    SERVICE_STATUS serviceStatus = 
	{
        SERVICE_WIN32_OWN_PROCESS,
        g_CurrentState,
        state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
        NO_ERROR,
        0,
        0,
        0,
    };
    SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}
DWORD WINAPI HandlerEx(DWORD control, DWORD eventType, void *eventData, void *context);

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
    // Must be called at start.
    g_ServiceStatusHandle = RegisterServiceCtrlHandlerEx("SERVICE NAME", &HandlerEx, NULL);
    
    // Startup code.
    ReportStatus(SERVICE_START_PENDING);
    g_StopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  
    ReportStatus(SERVICE_RUNNING);

    while (WaitForSingleObject(g_StopEvent, 3000) != WAIT_OBJECT_0)
    {
        // This sample service does "BEEP!" every 3 seconds.
        Beep(1000, 100);
    }

    ReportStatus(SERVICE_STOP_PENDING);

    CloseHandle(g_StopEvent);
    ReportStatus(SERVICE_STOPPED);
}






void ReportProgressStatus(DWORD state, DWORD checkPoint, DWORD waitHint)
{
    g_CurrentState = state;
    SERVICE_STATUS serviceStatus = {
        SERVICE_WIN32_OWN_PROCESS,
        g_CurrentState,
        state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
        NO_ERROR,
        0,
        checkPoint,
        waitHint,
    };
    SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}


void ReportErrorStatus(DWORD errorCode)
{
    g_CurrentState = SERVICE_STOPPED;
    SERVICE_STATUS serviceStatus = {
        SERVICE_WIN32_OWN_PROCESS,
        g_CurrentState,
        0,
        ERROR_SERVICE_SPECIFIC_ERROR,
        errorCode,
        0,
        0,
    };
    SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

DWORD WINAPI HandlerEx(DWORD control, DWORD eventType, void *eventData, void *context)
{
    switch (control)
    {
    // Entrie system is shutting down.
    case SERVICE_CONTROL_SHUTDOWN:
        g_SystemShutdown = true;
        // continue...
    // Service is being stopped.
    case SERVICE_CONTROL_STOP:
        ReportStatus(SERVICE_STOP_PENDING);
        SetEvent(g_StopEvent);
        break;
    // Ignoring all other events, but we must always report service status.
    default:
        ReportStatus(g_CurrentState);
        break;
    }
    return NO_ERROR;
}



int _cdecl main(void)
{
    HANDLE hSCManager;
    HANDLE hService;
    SERVICE_STATUS ss;

    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    
    printf("Load Driver\n");

    if(hSCManager)
    {
        printf("Create Service\n");

        hService = CreateService(hSCManager, "Example", 
                                 "Example Driver", 
                                  SERVICE_START | DELETE | SERVICE_STOP, 
                                  SERVICE_KERNEL_DRIVER,
                                  SERVICE_DEMAND_START, 
                                  SERVICE_ERROR_IGNORE, 
                                  "C:\\example.sys", 
                                  NULL, NULL, NULL, NULL, NULL);

        if(!hService)
        {
            hService = OpenService(hSCManager, "Example", 
                       SERVICE_START | DELETE | SERVICE_STOP);
        }

        if(hService)
        {
            printf("Start Service\n");

            StartService(hService, 0, NULL);
            printf("Press Enter to close service\r\n");
            getchar();
            ControlService(hService, SERVICE_CONTROL_STOP, &ss);

            DeleteService(hService);

            CloseServiceHandle(hService);
            
        }

        CloseServiceHandle(hSCManager);
    }
    
    return 0;
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
*/