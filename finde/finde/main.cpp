
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
wcscat(srchpath,L"\\*");
wcscpy(fname,path);
wcscat(fname,L"\\");
//FILE_ATTRIBUTE_ARCHIVE
// find the first file
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
			if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if(!find_file_in_dir(fname))
				{
				FindClose(hf);
				return FALSE;
				}
			wcscpy(fname,srchpath);
			}
			else
			{
			wcscpy(fname,srchpath);
			wprintf(fname);
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
find_file_in_dir(L"c:\\Users");


system("\n\npause");
}
