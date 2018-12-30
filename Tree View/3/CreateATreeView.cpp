HWND CreateATreeView(HWND hwndParent)
{ 
    RECT rcClient;  // dimensions of client area 
    HWND hwndTV;    // handle to tree-view control 
    InitCommonControls(); 
  
	///// | 0x0008|0x0010

	hwndTV = CreateWindow( WC_TREEVIEW,TEXT("Tree View"),0x5010|TVIF_IMAGE| TVS_DISABLEDRAGDROP|TVS_TRACKSELECT|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_NONEVENHEIGHT|WS_VISIBLE |TVS_TRACKSELECT|TVS_INFOTIP| TVS_TRACKSELECT|WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_EDITLABELS ,1,0, 200, 700, hwndParent, (HMENU)123, NULL, NULL);


	  
						HBITMAP	bvb= (HBITMAP)LoadImage(NULL,"D:\\WINAPI2-\\Tree View\\1\\1200x900\\70.bmp", IMAGE_BITMAP,200,100, LR_LOADFROMFILE);
								
							

							SendMessage(hwndTV,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)bvb);

    {  //InitTreeViewImageLists(hwndTV,hwndParent)
    //    DestroyWindow(hwndTV); 
       // return FALSE; 
    } 



//	SendDlgItemMessage(hwndParent,123,TVM_SETIMAGELIST,0,(LPARAM)hImageList);
    return hwndTV;
} 