HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, int nLevel,int ico_I,int ico_II) 

{ 
	static int i=2;
    TV_ITEM tvi; 
    TV_INSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
	static HTREEITEM hPrevLev3Item = NULL; 
	static HTREEITEM hPrevLev4Item = NULL;
	static HTREEITEM hPrevLev5Item = NULL;
	static HTREEITEM hPrevLev6Item = NULL;
	/*
hImageList=ImageList_Create(16,16,ILC_COLOR16,2,10);
	    HICON hIcon;
		 hBitMap = (HBITMAP)LoadImage(NULL, "C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\123.bmp", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
		 bvb= (HBITMAP)LoadImage(NULL,"C:\\Users\\vaxoa\\OneDrive\\Desktop\\LIST.BMP", IMAGE_BITMAP,10,10, LR_LOADFROMFILE);

		 		
		 ImageList_Add(hImageList,(HBITMAP)bvb,TVSIL_NORMAL);

		 		 SendDlgItemMessage(hwnd,123,TVM_SETIMAGELIST,0,(LPARAM)(HBITMAP)hImageList);

				     TreeView_SetImageList(hwndTV, hImageList, TVSIL_NORMAL); 

				  SendMessage(hwndTV, TVM_SETIMAGELIST, 0, (LPARAM) hImageList); 
	
   hBitMap=(HBITMAP)LoadImage(NULL, "C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\123.bmp", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
 
   
   
   ImageList_Add(hImageList,hBitMap,NULL);
   DeleteObject(hBitMap);

		 SendDlgItemMessage(hwnd,123,TVM_SETIMAGELIST,0,(LPARAM)(HBITMAP)hImageList);
 SendMessage(hwndTV, TVM_SETIMAGELIST, 0, 
         (LPARAM) hImageList); 

	
	 */





    HTREEITEM hti; 
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE| TVIF_SELECTEDIMAGE|TVIS_STATEIMAGEMASK|TVIS_OVERLAYMASK|TVIS_USERMASK ; 
 

    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
    tvi.lParam = (LPARAM) nLevel; 

	
 //   tvi.iImage =0;
  //  tvi.iSelectedImage =1;
	
	tvins.item.mask=TVIF_TEXT | TVIF_IMAGE| TVIF_SELECTEDIMAGE;
	tvins.item.lParam=(LPARAM) nLevel;
	tvins.item.pszText=lpszItem;
	tvins.item.cchTextMax=lstrlen(lpszItem);
  //  tvins.item = tvi; 
    tvins.hInsertAfter = hPrev; 
	tvins.item.iImage=ico_I;
	tvins.item.iSelectedImage=ico_II;
	
    if (nLevel == 1) 
	{
        tvins.hParent = TVI_ROOT;
		 hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
		hPrevRootItem = hPrev; 
	}
    else if (nLevel == 2) 
	{	
		tvins.hParent = hPrevRootItem;
		 hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
        hPrevLev2Item = hPrev; 
	}
     else if(nLevel==3)
	 { 
		hPrevLev3Item = hPrev; 
		 hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
        tvins.hParent = hPrevLev2Item; 
	 }
	 else if (nLevel == 4) 
	 {
		 tvins.hParent=hPrevLev3Item;
	 	 hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
		 hPrevLev4Item = hPrev;
	 }
	 else if (nLevel == 5) 
	 {
		   tvins.hParent = hPrevLev4Item; 
		   hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
		   hPrevLev5Item = hPrev;
	 }
	 else if (nLevel == 6) 
	 {
		 tvins.hParent = hPrevLev5Item; 
		 hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins);
		 hPrevLev6Item = hPrev;
	 }


  //  hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
	/*
    if (nLevel == 1) 
        hPrevRootItem = hPrev; 
    else if (nLevel == 2) 
	{
        hPrevLev2Item = hPrev;
	}
	  else if (nLevel == 3) 
        hPrevLev3Item = hPrev; 
	 else if (nLevel == 4) 
        hPrevLev4Item = hPrev;
	   else if (nLevel == 5) 
        hPrevLev5Item = hPrev;
	    else if (nLevel == 6) 
        hPrevLev6Item = hPrev;

	   */
		/*
    if (nLevel > 1)
	{ 
        hti = TreeView_GetParent(hwndTV, hPrev); 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.hItem = hti; 
        tvi.iImage =1; 
        tvi.iSelectedImage = 1; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
 */
    return hPrev; 
} 
 
 