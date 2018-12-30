
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


