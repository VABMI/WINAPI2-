
void create(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{


	HWND tvHandle=CreateATreeView(hwnd);

	HIMAGELIST imageList = ::ImageList_Create(20,20,ILC_COLORDDB | ILC_MASK,2,5000);

	HIMAGELIST imageList2= ::ImageList_Create(20,20,ILC_COLORDDB | ILC_MASK,2,100);




HICON icon;

icon	= (HICON)LoadImage(NULL,"2.ico", IMAGE_ICON,30,30, LR_LOADFROMFILE);
		
if(icon){


ImageList_AddIcon(imageList, icon);

}

icon	= (HICON)LoadImage(NULL,"Glove Normal.ico", IMAGE_ICON,30,30, LR_LOADFROMFILE);
if(icon){


ImageList_AddIcon(imageList, icon);
//ImageList_AddIcon(imageList2, icon);

}

icon	= (HICON)LoadImage(NULL,"3.ico", IMAGE_ICON,30,30, LR_LOADFROMFILE);
if(icon){


ImageList_AddIcon(imageList, icon);
//ImageList_AddIcon(imageList2, icon);

}
icon	= (HICON)LoadImage(NULL,"4.ico", IMAGE_ICON,30,30, LR_LOADFROMFILE);
if(icon){


ImageList_AddIcon(imageList, icon);
//ImageList_AddIcon(imageList2, icon);

}
	if(ImageList_GetImageCount(imageList) == 4)
	{
		SendMessage(tvHandle, TVM_SETIMAGELIST,(WPARAM)TVSIL_NORMAL, (LPARAM)imageList);
	}




// load icons and add them to ImageList

	//=====================================================//
	
	

	/*
	
	TVITEM tvitm;	
	tvitm.mask=TVIF_TEXT;
	tvitm.pszText="vaxo";
	tvitm.cchTextMax=strlen(tvitm.pszText);

	tvinsert.item=tvitm;
	tvinsert.hInsertAfter=TVI_ROOT;
	SendMessage(hwnd,TVM_INSERTITEM,(WPARAM)0,(LPARAM)&tvitm);

	
	tvitm.pszText="saqartvelo";
	tvitm.cchTextMax=lstrlen("saqartvelo");
	tvinsert.item=tvitm;
	SendMessage(hwnd,TVM_INSERTITEM,(WPARAM)0,(LPARAM)&tvinsert);




	tvitm.pszText="item3";
	tvitm.cchTextMax=lstrlen(tvitm.pszText);
	
	tvitm.hItem=TreeView_GetParent(hwnd,tvitm.hItem);



	*/


	//	CreateWindowEx(0, WC_TREEVIEW,TEXT("Tree View"), WS_VISIBLE | WS_CHILD,0, 0, 200, 500, hwnd, (HMENU)123, GetModuleHandle(NULL), NULL);
	//	if(InitTreeViewImageLists()

	/*
	
	tvi.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	tvi.pszText="saqartvelo";
	tvi.cchTextMax=lstrlen("saqartvelo");
	tvi.iImage=1;
	tvi.iSelectedImage=1;
	tvi.lParam=(LPARAM)1;
	tvinsert.item=tvi;
	tvinsert.hInsertAfter=hPrev;
	
		TreeView_CreateDragImage(hwnd,hitTarget);	

		hImageList=ImageList_Create(16,16,ILC_COLOR16,2,10);
		
		hBitMap=(HBITMAP)LoadBitmap(NULL, MAKEINTRESOURCE("C:\\Users\\vaxoa\\OneDrive\\Documents\\GitHub\\WINAPI\\icon\\BMP.png"));
		
		///// C:\Users\vaxoa\OneDrive\Desktop\icon\Itzikgur-My-Seven-Downloads-1.ico
		
		
		
		
		
		ImageList_Add(hImageList,hBitMap,NULL);	

		DeleteObject(hBitMap);	

		
		*/


	//	SendDlgItemMessage(hwnd,123,TVM_SETIMAGELIST,0,(LPARAM)&tvinsert);

		

//////////////////////////////// parents and children /////////////////////////////////
	HWND hwnd_tv=GetDlgItem(hwnd,123);
	/*
			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE;//|TVIF_CHILDREN;//|TVIF_SELECTEDIMAGE|
	        tvinsert.item.pszText="Parent";
			tvinsert.item.cchTextMax=128;
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=1; 
			Parent=(HTREEITEM)SendMessage(hwnd_tv,TVM_INSERTITEM,0,(LPARAM)&tvinsert);	//SendDlgItemMessage(hwnd,123,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			
			
				tvinsert.hParent=Parent;         // handle of the above data
				tvinsert.hInsertAfter=TVI_LAST;  // below parent
				tvinsert.item.pszText="Child 1";
				tvinsert.item.iImage=0;
				tvinsert.item.iSelectedImage=0; 

					 Parent=(HTREEITEM)SendDlgItemMessage((HWND)Parent,123,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
					*/
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\witeli.BMP",1,0,1);  
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\76.bmp",2,2,3);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\92.bmp",2,0,1);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\67.bmp",2,1,2);
					  

				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\\\97.bmp",1,2,0);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\23.bmp",1,0,3);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\66.bmp",1,3,1);
		//				SendMessage(tvHandle, TVM_SETIMAGELIST,(WPARAM)0, (LPARAM)imageList2);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				 
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\ukraina.bmp",1,0,1);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\68.bmp",1,2,1);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\87.bmp",1,0,2);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\70.bmp",1,2,3);
					  SendMessage(hwnd_tv,TVM_SETTEXTCOLOR,0,(LPARAM)RGB(250,47,47));

				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\8.bmp",1,1,2);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\83.bmp",1,1,2);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\69.bmp",1,1,2);
				 
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\64.bmp",1,1,2);
				  AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\25.bmp",1,1,2);
				 AddItemToTree(hwnd_tv,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\43.bmp",1,1,2);

					//	 AddItemToTree(hwnd_tv,"saqartvelo21",2);
					//	  AddItemToTree(hwnd_tv,"saqartvelo21",2);
					//      AddItemToTree(hwnd_tv,"saqartvelo22",3); 
						
					 /*
////======================================================//////////////////////////////////////////////////////
			 tvinsert.hParent=NULL;			// top most level no need handle
			 tvinsert.hInsertAfter=TVI_LAST; // work as root level
	         tvinsert.item.pszText="Parent2";
             Parent=(HTREEITEM)SendDlgItemMessage(hwnd,123,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
/////==================================================//////////////////////////////////////////////
	 tvinsert.hParent=NULL;			// top most level no need handle
			 tvinsert.hInsertAfter=TVI_LAST; // work as root level
	         tvinsert.item.pszText="Parent3";
             Parent=(HTREEITEM)SendDlgItemMessage(hwnd,123,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			 */

			 

}
