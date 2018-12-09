   

char* save(){
OPENFILENAME ofn;

    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); 
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter ="Text Files (*.jpg)\0*.jpg\0(*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt ="bmp";

    GetSaveFileName(&ofn);


				char g[200];	
				int co=0;
				char szFile[200];
				char path[1000];
				sprintf(szFile,"%s",ofn.lpstrFile);

			 	 for(int i=0;i<=strlen(szFile);i++)
				 {

				//	if(((int)(szFile[i]))==47)
					if(((int)szFile[i])==92)
					{
					path[co]=szFile[i];
					
					co++;
					path[co]=szFile[i];

					}
					else
					{
						path[co]=szFile[i];

					}



			  
				co++;


				 }













    return (char*)path;

}