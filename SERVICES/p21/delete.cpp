
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
		serviceName,
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

