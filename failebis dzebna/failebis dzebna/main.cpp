
#include "windows.h"
#include "string.h"
#include "stdio.h"

BOOL find_file_in_dir(wchar_t *path)
{
HANDLE hf;
WIN32_FIND_DATAW ffdata;

wchar_t srchpath[300];
wchar_t fname[300];
wchar_t bufer[300];
wcscpy(srchpath,path);
wcscat(srchpath,L"\\*.*");
wcscpy(fname,path);
wcscat(fname,L"\\");
MessageBoxW(0,srchpath,path,0);
hf=FindFirstFileW(srchpath,&ffdata);

	if(hf == INVALID_HANDLE_VALUE)
	return FALSE;

wcscpy(srchpath,fname);
bool bSearch = true;
	while(bSearch)
	{
		if(FindNextFileW(hf,&ffdata))
		{
			wcscat(fname,ffdata.cFileName);

				wcscat(fname,L"\n\r");
	

		}
		else
		{
			if(GetLastError() == ERROR_NO_MORE_FILES)
			bSearch = false;
		}
	}

	MessageBoxW(0,fname,fname,0);
	wchar_t path2[100];
	wscanf(L"%ls",&path2);


	find_file_in_dir(path2);
FindClose(hf);
return 0;
}
//--------------------------------------------------------------------------------------------
void main()
{
char buff[256];
GetClassName(GetDesktopWindow(),buff,256);

WNDCLASS wc;
GetClassInfo(0,buff,&wc);

WNDCLASSEX wcex;
GetClassInfoEx(0,buff,&wcex);

find_file_in_dir(L"C:\\Intel\\Logs");
}
