
void * find_file_in_dir(char *path)
{
HANDLE hf;
WIN32_FIND_DATAA ffdata;

char srchpath[3000];
char fname[3000];
char bufer[3000];
strcpy(srchpath,path);
strcat(srchpath,"\\*.*");



strcpy(fname,path);
strcat(fname,"\\");
//	MessageBox(0,srchpath,path,0);
hf=FindFirstFile(srchpath,&ffdata);

	if(hf == INVALID_HANDLE_VALUE)
	return FALSE;

strcpy(srchpath,fname);
bool bSearch = true;
	while(bSearch)
	{
		if(FindNextFile(hf,&ffdata))
		{		
				strcat(fname,ffdata.cFileName);

				strcat(fname,"\n\r");
	

		}
		else
		{
			if(GetLastError() == ERROR_NO_MORE_FILES)
			bSearch = false;
		}
	}

//	MessageBox(0,fname,fname,0);




	
FindClose(hf);

return (void*)fname;
}