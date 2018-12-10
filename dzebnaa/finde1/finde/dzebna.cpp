DWORD WINAPI find_file_in_dir(void* vall)
{
	search val2;
	memcpy((search*)&val2,(search*)vall,sizeof(search));
//	val2.constval();
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
					MessageBoxW(0,val2.path,val2.path,0);
				}

			 }
	//	wcscat(fname,ffdata.cFileName);
		//wcscat(fname,L"\r\n");
	//	MessageBoxW(0,ffdata.cFileName,ffdata.cFileName,0);
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) /// if direqtoriiaaa
			{
			
				if(ffdata.cFileName[0]!='.')
				{	
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

	
//	val2.dconstval();
//	free(srchpath);
//	free(fname);
	FindClose(hf);
return 0; 
}