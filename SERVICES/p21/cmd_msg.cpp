
HFONT select_font(HWND hwnd)
{
HDC hdc;                  // display device context of owner window
CHOOSEFONT cf;            // common dialog box structure
static LOGFONT lf;        // logical font structure
static DWORD rgbCurrent;  // current text color
HFONT hfont, hfontPrev;
DWORD rgbPrev;

// Initialize CHOOSEFONT
ZeroMemory(&cf, sizeof(cf));
cf.lStructSize = sizeof (cf);
cf.hwndOwner = hwnd;
cf.lpLogFont = &lf;
cf.rgbColors = rgbCurrent;
cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

	if (ChooseFont(&cf)==TRUE)
	{
	hfont = CreateFontIndirect(cf.lpLogFont);
	//hfontPrev = SelectObject(hdc, hfont);
	rgbCurrent= cf.rgbColors;
	rgbPrev = SetTextColor(hdc, rgbCurrent);
	}
return hfont;
}


  SC_HANDLE service;

#define srvName "aaaaaa"
  
long __stdcall on_cmd(HWND hwnd,unsigned int message,unsigned int wparam,long lparam)
{

 if(wparam==10)
	{ 
		/*
	SC_HANDLE hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if(hSCManager){

	SC_HANDLE  hService = CreateService(hSCManager, "Example", 
                                 "Example Driver", 
                                  SERVICE_START | DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS	, 
                                  SERVICE_WIN32_SHARE_PROCESS,
                                  SERVICE_AUTO_START, 
                                  NULL, 
								  "F:\\WINAPI2-\\ForServise\\Debug\\ForServise.exe", 
                                  NULL,NULL, NULL, NULL, NULL);
		if(!hService)
		{MessageBox(hwnd,"error","error",0);}


		


			int errr=GetLastError();
		
	
	 }


	*/


	 SC_HANDLE handle = ::OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );


     service = ::CreateService(
        handle,
        srvName,
        "111111111111",
        GENERIC_READ | GENERIC_EXECUTE ,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
		SERVICE_ERROR_SEVERE,
        "F:\\WINAPI2-\\ForServise\\Debug\\ForServise.exe",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    );

	if(service==NULL)
	{int errr=GetLastError();
		printf("OpenSCManager() failed, error: %d.\n", GetLastError());
		MessageBox(0,"error","sadad",0);
				
	}




	LPHANDLER_FUNCTION LphandlerFunction;


	RegisterServiceCtrlHandler(srvName,LphandlerFunction);

		
}

  if(wparam==20)
	{ 





			 SC_HANDLE handle = ::OpenSCManager( NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS );
		SC_HANDLE service1=OpenServiceW
			(	handle,	
				L"aaaaaa",	
					DELETE 	
					);

		if(DeleteService(service1))
		{


		}else
		{
	
			int errr=GetLastError();
					MessageBox(0,"error","sadad",0);


		}





  }

  
  if(wparam==30)
{ 	
		
		
		LPDWORD val1;
		LPDWORD val2;
		
		
		SC_HANDLE handle = ::OpenSCManager( NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS );
		  SERVICE_STATUS g_ServiceStatus;
		     g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

		
		ENUM_SERVICE_STATUS sv;
		 sv.lpDisplayName="111111111111";
		 sv.lpServiceName=srvName;
		 sv.ServiceStatus=(SERVICE_STATUS )g_ServiceStatus;
		SC_HANDLE service1=OpenServiceW(handle,L"MyTestService_01312009",DELETE);

		EnumDependentServices(service1,SERVICE_ACTIVE,&sv,sizeof(sv),0,0);
	 }
///////////////////////////////////////////////////////////////////////////////////////////
   if(wparam==40) {
	   
	   	SC_HANDLE handle = ::OpenSCManager( NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS );
	
	 SERVICE_STATUS   g_ServiceStatus;
	 g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;


		ENUM_SERVICE_STATUS sv;
		 sv.lpDisplayName="111111111111";
		 sv.lpServiceName=srvName;
		 sv.ServiceStatus=(SERVICE_STATUS )g_ServiceStatus;
		SC_HANDLE service1=OpenServiceW(handle,L"aaaaaa",SERVICE_ALL_ACCESS);

		EnumDependentServices(service1,SERVICE_ACTIVE,&sv,sizeof(sv),0,0);
	

  }
   ///////////////////////////////////////////////////////////////////////////////////////
      if(wparam==50) {
	   
	   		 SC_HANDLE handle = ::OpenSCManager( NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS );
		 if(handle)
			 {






		SC_HANDLE service1=OpenServiceW
			(	handle,	
				L"aaaaaa",	
					SERVICE_ALL_ACCESS	 	
					);

		StartService(service1,NULL,NULL);
  }
	  }
return 0;
}