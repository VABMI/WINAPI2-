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
		serviceName,
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
