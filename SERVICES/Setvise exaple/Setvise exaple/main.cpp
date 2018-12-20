#include "windows.h"
#include "stdio.h"

bool Initialize()
{
int m_lDriverCount=0;
SC_HANDLE h_SCM = ::OpenSCManager (NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	if (h_SCM != NULL)
	{
	ENUM_SERVICE_STATUS struct_ServiceStatus;
	ENUM_SERVICE_STATUS *lpServiceStatus;
	BOOL b_RetVal = FALSE;
	DWORD dw_BytesNeeded;
	DWORD dw_ServiceCount;
	DWORD dw_ResumeHandle = 0;
	DWORD dw_ServiceType;
	DWORD dw_ServiceState;
	
	dw_ServiceType = SERVICE_DRIVER; //We are interested only in drivers
	
	dw_ServiceState = SERVICE_STATE_ALL; // interested to know about drivers in all states
	
	//Call EnumServicesStatus using the handle returned by OpenSCManager
	b_RetVal = ::EnumServicesStatus(h_SCM,
			dw_ServiceType,
			dw_ServiceState,
			&struct_ServiceStatus,
			sizeof(struct_ServiceStatus),
			&dw_BytesNeeded,
			&dw_ServiceCount,
			&dw_ResumeHandle
			);
	
	DWORD dw_Error = GetLastError();
	// Verify if EnumServicesStatus needs more memory space
		if ((b_RetVal == FALSE) || dw_Error == ERROR_MORE_DATA) 
		{
		DWORD dw_Bytes = dw_BytesNeeded + sizeof(ENUM_SERVICE_STATUS);
		lpServiceStatus = new ENUM_SERVICE_STATUS [dw_Bytes];
		EnumServicesStatus(	h_SCM,
			dw_ServiceType,
			dw_ServiceState,
			lpServiceStatus,
			dw_Bytes,
			&dw_BytesNeeded,
			&dw_ServiceCount,
			&dw_ResumeHandle);
		}
		
	m_lDriverCount = dw_ServiceCount; // number of drivers
	// Get additional information regarding driver by opening the driver service
	SC_HANDLE h_ServiceHandle = NULL;
		for(unsigned int i = 0; i < dw_ServiceCount ; i++)
		{
		h_ServiceHandle = NULL;
		h_ServiceHandle = OpenService(h_SCM, lpServiceStatus[i].lpServiceName, SERVICE_ALL_ACCESS);
			if(NULL != h_ServiceHandle)
			{
			LPQUERY_SERVICE_CONFIG lpqscBuf; 
			DWORD dwBytesNeeded; 
			BOOL bSuccess=TRUE;
			// Allocate a buffer for the configuration information.
			lpqscBuf = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 4096); 
				if (lpqscBuf == NULL) 
				{
				return FALSE;
				}

				// Get the configuration information. 
				if (!QueryServiceConfig(h_ServiceHandle,lpqscBuf,4096,&dwBytesNeeded)) 
				{
				bSuccess = FALSE; 
				}
				
				// Fill Startup Type
				if(SERVICE_AUTO_START & lpqscBuf->dwStartType)
				{
				printf("%s\n","Auto Start");
				}
				else if(SERVICE_BOOT_START & lpqscBuf->dwStartType)
				{
				printf("%s\n","Boot Start");
				}
				else if(SERVICE_DEMAND_START & lpqscBuf->dwStartType)
				{
				printf("%s\n","Demand Start");
				}
				else if(SERVICE_DISABLED & lpqscBuf->dwStartType)
				{
				printf("%s\n","Disabled");
				}
				else if(SERVICE_SYSTEM_START & lpqscBuf->dwStartType)
				{
				printf("%s\n","System Start");
				}

			// set the binary path
			LPCTSTR psz_SystemRoot; 
			psz_SystemRoot = (LPTSTR) malloc(1024*sizeof(TCHAR));
			
			DWORD dw_Ret = GetEnvironmentVariable(TEXT("SYSTEMROOT"), (char*)psz_SystemRoot, 1024);
			//_tcscpy((unsigned short*)psz_SystemRoot, (const unsigned short *)psz_SystemRoot);
			
			// In binary path information received, there could be some of the strings that 
			// needs to be replaced. Strings to be replaced are as follows: \SystemRoot, \??\
			// Add SYSTEMROOT value obtained by calling GetEnvironmentVariable() to \System32 and \system32

			// Find "\SystemRoot" and replace it with System root value obtained after
			// querying environment variable
			TCHAR sz_BinaryPathName[200] = {0};
			sprintf(sz_BinaryPathName, lpqscBuf->lpBinaryPathName);
			TCHAR *lpFirstOccurance = NULL;
			lpFirstOccurance = (TCHAR*)strstr(sz_BinaryPathName, "\\SystemRoot");
				if(strlen(sz_BinaryPathName) > 0 && lpFirstOccurance != NULL)
				{
				// replace \SysteRoot with system root value obtained by
				// calling GetEnvironmentVariable() to get SYSTEMROOT
				lpFirstOccurance += strlen("\\SystemRoot");
				sprintf(sz_BinaryPathName, "%s%s", psz_SystemRoot, lpFirstOccurance);
				}
				else
				{
				lpFirstOccurance = NULL;
				lpFirstOccurance = (TCHAR*)strstr(sz_BinaryPathName, "\\??\\");
					if(strlen(sz_BinaryPathName) > 0 && lpFirstOccurance != NULL)
					{
					// Remove \??\ at the starting of binary path
					lpFirstOccurance += strlen("\\??\\");
					sprintf(sz_BinaryPathName, "%s", lpFirstOccurance);
					}
					else
					{
					lpFirstOccurance = NULL;
					lpFirstOccurance = (TCHAR*)strstr(sz_BinaryPathName, "system32");
						if(strlen(sz_BinaryPathName) > 0 && lpFirstOccurance != NULL && sz_BinaryPathName == lpFirstOccurance)
						{
						// Add SYSTEMROOT value if there is only system32 mentioned in binary path
						TCHAR sz_TempBinaryPathName[200] = {0};
						sprintf(sz_TempBinaryPathName, "%s\\%s", psz_SystemRoot, sz_BinaryPathName); 
						sprintf(sz_BinaryPathName, "%s", sz_TempBinaryPathName); 

						}
						else
						{
						lpFirstOccurance = NULL;
						lpFirstOccurance = (TCHAR*)strstr(sz_BinaryPathName, "System32");
							if(strlen(sz_BinaryPathName) > 0 && lpFirstOccurance != NULL && sz_BinaryPathName == lpFirstOccurance)
							{
							// Add SYSTEMROOT value if there is only System32 mentioned in binary path
							TCHAR sz_TempBinaryPathName[200] = {0};
							sprintf(sz_TempBinaryPathName, "%s\\%s", psz_SystemRoot, sz_BinaryPathName); 
							sprintf(sz_BinaryPathName, "%s", sz_TempBinaryPathName); 
							}
						}
					}
				}
			printf("%s\n",sz_BinaryPathName); 
			
			free((void*)psz_SystemRoot);
			LocalFree(lpqscBuf); 
			CloseServiceHandle(h_ServiceHandle);
			}

			printf("%s\n",lpServiceStatus[i].lpServiceName);
			printf("%s\n",lpServiceStatus[i].lpDisplayName);
			
			// Fill Driver Type
			if(SERVICE_FILE_SYSTEM_DRIVER & lpServiceStatus[i].ServiceStatus.dwServiceType)
			{
			printf("%s\n","File System Driver");
			}
			else if(SERVICE_KERNEL_DRIVER & lpServiceStatus[i].ServiceStatus.dwServiceType)
			{
			printf("%s\n","Kernel Driver");
			}
			
			// Update service status
			if(SERVICE_CONTINUE_PENDING == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Continue pending");
			}
			else if(SERVICE_PAUSE_PENDING == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Pause pending");
			}
			else if(SERVICE_PAUSED == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Paused");
			}
			else if(SERVICE_RUNNING == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Running");
			}
			else if(SERVICE_START_PENDING == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Start pending");
			}
			else if(SERVICE_STOP_PENDING == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Stop pending");
			}
			else if(SERVICE_STOPPED == lpServiceStatus[i].ServiceStatus.dwCurrentState)
			{
				printf("%s\n","Stopped");
			}

		}
	}
CloseServiceHandle(h_SCM);
return true;
}


void main()
{
Initialize();

system("pause");
}