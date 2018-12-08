inline DWORD WINAPI find_file_in_dir(void *vall)
{

	wchar_t *path,*SadzebniFaili;

	search val1;

	memcpy((search*)&val1,(search*)vall,sizeof(struct PARAM));
	//	memcpy((struct PARAM *)&val,(struct PARAM *)bufer1,sizeof(struct PARAM));
	//	val1.constval();
	path=val1.path;
	SadzebniFaili=val1.SadzebniFaili;




HANDLE hf;
WIN32_FIND_DATAW ffdata;

wchar_t *srchpath=(wchar_t*)malloc(30000000);
wchar_t *fname=(wchar_t*)malloc(30000000);

wcscpy(srchpath,path);
wcscat(srchpath,L"\\");
wcscat(srchpath,L"\\*.*");
wcscpy(fname,path);
wcscat(fname,L"\\");

	hf=FindFirstFileW(srchpath,&ffdata);
	if(hf == INVALID_HANDLE_VALUE)
	return FALSE;
	////////////////////////////// if daemtxva faili modzebnilia //////////////////
	//	MessageBoxW(0,ffdata.cFileName,ffdata.cFileName,0);
	if(wcslen(ffdata.cFileName)==wcslen(SadzebniFaili))
			 {
				if(wcsncmp(ffdata.cFileName,SadzebniFaili,wcslen(SadzebniFaili))==0)
				{
					MessageBoxW(0,fname,fname,0);
				}

			 }
///////////////////////////////////////////////////////////////////////////////////////
	while(FindNextFileW(hf,&ffdata))
	{
		
		if(wcslen(ffdata.cFileName)==wcslen(SadzebniFaili))
			 {
				if(wcsncmp(ffdata.cFileName,SadzebniFaili,wcslen(SadzebniFaili))==0)
				{
					MessageBoxW(0,path,path,0);
				}

			 }
	//	wcscat(fname,ffdata.cFileName);
		//wcscat(fname,L"\r\n");
	//	MessageBoxW(0,ffdata.cFileName,ffdata.cFileName,0);
		if((ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) /// if direqtoriiaaa
			{
			
				if(ffdata.cFileName[0]!='.'){
					ZeroMemory(srchpath,sizeof(srchpath));
					wcscpy(srchpath,path);
					wcscat(srchpath,L"\\");
					wcscat(srchpath,ffdata.cFileName);
				search vall;
				vall.constval();
				vall.path=srchpath;
				vall.SadzebniFaili=SadzebniFaili;
					find_file_in_dir(&vall);

				}
			}
		


	}	

	free(srchpath);
	free(fname);
FindClose(hf);
return 0; 
}