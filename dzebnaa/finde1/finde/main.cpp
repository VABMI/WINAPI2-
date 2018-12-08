
#include "windows.h"
#include "string.h"
#include "stdio.h"
typedef struct {
	   wchar_t *SadzebniFaili;//=(wchar_t*)malloc(1000);
	   wchar_t * path;//=(wchar_t*)malloc(1000);
	   void constval()
	   {

		  SadzebniFaili =(wchar_t*)malloc(1000);
		  path=(wchar_t*)malloc(1000);
	   }
	   void dconstval()
	   {

		    free(SadzebniFaili);
		    free(path);
	   }

}search;
DWORD WINAPI find_file_in_dir(void* vall)
{
	search val2;
	val2.constval();
	memcpy((search*)&val2,(search*)vall,sizeof(search));



	val2.path;

//	wchar_t *path=val2.path;wchar_t *SadzebniFaili;
HANDLE hf;
WIN32_FIND_DATAW ffdata;

wchar_t *srchpath=(wchar_t*)malloc(30000000);
wchar_t *fname=(wchar_t*)malloc(30000000);

wcscpy(srchpath,val2.path);
wcscat(srchpath,L"\\");
wcscat(srchpath,L"\\*.*");
wcscpy(fname,val2.path);
wcscat(fname,L"\\");

	hf=FindFirstFileW(srchpath,&ffdata);
	if(hf == INVALID_HANDLE_VALUE)
	return FALSE;
	//	MessageBoxW(0,ffdata.cFileName,ffdata.cFileName,0);
	if(wcslen(ffdata.cFileName)==wcslen(val2.SadzebniFaili))
			 {
				if(wcsncmp(ffdata.cFileName,val2.SadzebniFaili,wcslen(val2.SadzebniFaili))==0)
				{
					MessageBoxW(0,L"Modzebna",L"modzebna",0);
				}

			 }

		wcscpy(srchpath,fname);
		bool bSearch = true;
		
	while(FindNextFileW(hf,&ffdata))
	{
		
		if(wcslen(ffdata.cFileName)==wcslen(val2.SadzebniFaili))
			 {
				if(wcsncmp(ffdata.cFileName,val2.SadzebniFaili,wcslen(val2.SadzebniFaili))==0)
				{
					


					// wchar_t *filee=(wchar_t*)malloc(wcslen(ffdata.cFileName)+wcslen(path));
					//wcscat(filee,path);
					//wcscat(filee,L"\\");
					//wcscat(filee,ffdata.cFileName);
					MessageBoxW(0,val2.path,val2.path,0);

				//	free(filee);
				}

			 }
	//	wcscat(fname,ffdata.cFileName);
		//wcscat(fname,L"\r\n");
	//	MessageBoxW(0,ffdata.cFileName,ffdata.cFileName,0);
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) /// if direqtoriiaaa
			{
			
				if(ffdata.cFileName[0]!='.'){	
					wcscpy(srchpath,val2.path);
					wcscat(srchpath,L"\\");
					wcscat(srchpath,ffdata.cFileName);
					//wcscat(srchpath,L"\\*.*");
					search val3;
					val3.constval();
					val3.path=srchpath;
					val3.SadzebniFaili=val2.SadzebniFaili;
					//find_file_in_dir((search*)&val3);
					CreateThread(0,0,find_file_in_dir,(search*)&val3,0,0);
					Sleep(10);
				//	free(&val3);

				}
			}
		


	}

		//	MessageBoxW(0,fname,fname,0);

	
	val2.dconstval();
	free(srchpath);
	free(fname);
FindClose(hf);
return 0; 
}
//--------------------------------------------------------------------------------------------

long __stdcall mainProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	switch(msg)
	{
		case WM_CREATE:
			{
			CreateWindow(L"edit",L"",WS_VISIBLE|WS_CHILD|WS_BORDER,120,0,160,20,hwnd,(HMENU)2,0,0);
			HWND combo=CreateWindow(L"combobox",L"ssss",WS_VISIBLE|WS_CHILD|WS_BORDER|CBS_DROPDOWN | CBS_HASSTRINGS | CBS_SIMPLE |WS_VSCROLL|CBS_HASSTRINGS,0,0,100,190,hwnd,(HMENU)15,0,0);
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"C:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"A:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"B:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"D:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"E:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"F:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"G:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"H:");
			SendMessage(combo,CB_ADDSTRING,0,(LPARAM)L"I:");
			CreateWindow(L"button",L"dzebna",WS_VISIBLE|WS_CHILD|WS_BORDER,280,0,70,20,hwnd,(HMENU)1,0,0);
			}
		break;
		
		case WM_COMMAND:
			if(wp==1)
			{
			//	 wchar_t *sea=(wchar_t*)malloc(1000);
				//GetWindowText(GetDlgItem(hwnd,2),sea,100);
			//	  wchar_t * combo=(wchar_t*)malloc(1000);
			//	GetWindowText(GetDlgItem(hwnd,15),combo,100);
				//find_file_in_dir((wchar_t*)combo,(wchar_t*)sea);
				search val1;

				val1.constval();
			
				GetWindowText(GetDlgItem(hwnd,2),val1.SadzebniFaili,100);
				GetWindowText(GetDlgItem(hwnd,15),val1.path,100);
			//	find_file_in_dir((search*)&val1);

				CreateThread(0,0,find_file_in_dir,(search*)&val1,0,0);
				Sleep(10);
				//CreateThread
				val1.dconstval();
						MessageBoxW(0,L"ASd",L"Asdad",0);
			}
			break;

	}

	return DefWindowProc(hwnd,msg,wp,lp);
}
void main()
{
//find_file_in_dir(L"C:",L"vc100.idb");

WNDCLASS wc={0};
wc.lpszClassName=L"search";
wc.lpfnWndProc=&mainProc;
if(RegisterClass(&wc)==0){

	return ;

}
CreateWindow(wc.lpszClassName,L"search",WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW|WS_BORDER|WS_VISIBLE|WS_BORDER,0,0,600,500,0,0,0,0);

MSG msg={0};
while(GetMessage(&msg,0,0,0)!=0)
{

	TranslateMessage(&msg);
	DispatchMessage(&msg);

}
system("\n\npause");
}
