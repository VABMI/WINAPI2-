
#include "windows.h"
#include "string.h"
#include "stdio.h"

BOOL find_file_in_dir(wchar_t *path)
{
HANDLE hf;
WIN32_FIND_DATAW ffdata;

wchar_t srchpath[MAX_PATH];
wchar_t fname[MAX_PATH];

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
		wcscpy(fname,ffdata.cFileName);
		MessageBoxW(0,fname,0,0);
			if(fname[wcslen(fname)-1] !=L'.')
			{
				if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
				wsprintfW(fname,L"%s\\%s",path,ffdata.cFileName);
				MessageBoxW(0,fname,0,0);
					if(!find_file_in_dir(fname))
					{
					FindClose(hf);
					return FALSE;
					}
				wcscpy(fname,srchpath);
				}
			}
		}
		else
		{
			if(GetLastError() == ERROR_NO_MORE_FILES)
			bSearch = false;
			else
			{
			FindClose(hf);
			return FALSE;
			}
		}
	}
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


find_file_in_dir(L"C:\\Intel\\ExtremeGraphics\\CUI\\Resource");
}
