
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

//wcscpy(srchpath,fname);
bool bSearch = true;

	
	FindNextFileW(hf,&ffdata);
		wcscat(fname,ffdata.cFileName);
	
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
					MessageBoxW(0,fname,fname,0);
	
			}

		char fname1[100];
		FindNextFileW(hf,&ffdata);
	//	wcscat(fname,ffdata.cFileName);
	sprintf(fname1,"%s",ffdata.cFileName);
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
					MessageBox(0,fname1,fname1,0);
	
			}
	//	hf=FindFirstFileW(L"C:\\Users\\..",&ffdata);
		FindNextFileW(hf,&ffdata);
		wcscat(fname,ffdata.cFileName);
	
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
					MessageBoxW(0,fname,fname,0);
	
			}
		FindNextFileW(hf,&ffdata);
		wcscat(fname,ffdata.cFileName);
	
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
					MessageBoxW(0,fname,fname,0);
	
			}

//	while(bSearch)
	{


		/*

		if(FindNextFileW(hf,&ffdata))
		{
		wcscat(fname,ffdata.cFileName);
		MessageBoxW(0,fname,fname,0);
			if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				
	
			}
			
		}
		*/
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
