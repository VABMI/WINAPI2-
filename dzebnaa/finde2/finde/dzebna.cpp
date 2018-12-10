inline DWORD WINAPI find_file_in_dir(void *vall)
{

	wchar_t *path,*SadzebniFaili;

	search val1;
	val1.constval();
	memcpy((search*)&val1,(search*)vall,sizeof(struct PARAM));

	//	memcpy((struct PARAM *)&val,(struct PARAM *)bufer1,sizeof(struct PARAM));
	//	val1.constval();
	path=val1.path;
	SadzebniFaili=val1.SadzebniFaili;




HANDLE hf;
WIN32_FIND_DATAW ffdata;

wchar_t *srchpath=(wchar_t*)malloc(30000000);
	if(srchpath==NULL)
	{
		MessageBox(0,L"error",L"error",0);
		return 0;
	}
wchar_t *fname=(wchar_t*)malloc(30000000);
	if(fname==NULL)
	{
		free(srchpath);
		MessageBox(0,L"error",L"error",0);
		return 0;
	}

wcscpy(srchpath,path);
wcscat(srchpath,L"\\");
wcscat(srchpath,L"\\*.*");
wcscpy(fname,path);
wcscat(fname,L"\\");

	hf=FindFirstFileW(srchpath,&ffdata);
	if(hf != INVALID_HANDLE_VALUE)
	{
	
	
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
						wsprintfW(srchpath,L"%s\\%s",path,ffdata.cFileName);
						//wcscpy(srchpath,path);
					//	wcscat(srchpath,L"\\");
					//	wcscat(srchpath,ffdata.cFileName);
						//	MessageBox(0,ffdata.cFileName,ffdata.cFileName,0);
					search vall3;
				//	vall3.constval();
					vall3.path=srchpath;
					vall3.SadzebniFaili=SadzebniFaili;
					find_file_in_dir(&vall3);

					vall3.dconstval();
					}
				}
		


		}	

	FindClose(hf);
	}
	
	val1.dconstval();

//	((struct PARAM*)vall)->dconstval();
	free(srchpath);
	free(fname);

return 0; 
}