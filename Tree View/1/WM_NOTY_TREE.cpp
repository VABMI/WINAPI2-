	switch(wparam)
			{


			case 123:
				{
				
					switch(((LPNMHDR)lparam)->code)
					{
					case NM_RCLICK:
						{


							NMHDR FAR * hgf = (NMHDR FAR *) lparam;
							hgf->idFrom;
							hgf->code;
							static HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
							static	HTREEITEM hTreeItem;//=(HTREEITEM)hgf->code;
						


						//=======================================================
						char gbff[300];
						DWORD dwValue;
						HTREEITEM htree;
 						//htree=(HTREEITEM)
							//SendMessage(hgf->hwndFrom,TVM_GETNEXTITEM,(WPARAM)TVGN_CHILD,(LPARAM)htree);
//						hTreeItem=htree;
						//=======================================================
						//-------------------------------------------------------

							//tvins.item.lParam=(LPARAM) 2;
							tvins.item.pszText=("asasas");
							tvins.item.cchTextMax=lstrlen("asasas");
					    //  tvins.item = tvi; 
							tvins.hInsertAfter = hPrev; 

							tvins.hParent = hTreeItem;
							 hPrev = (HTREEITEM) SendMessage(hgf->hwndFrom, TVM_INSERTITEM,0,(LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
							 hTreeItem = hPrev; 
						//-------------------------------------------------------
							/*
						
						/////////////----------------------
		                TV_ITEM tvi1;
						char Text[256]="";
						tvi1.cchTextMax=254;
						tvi1.mask = TVIF_TEXT | TVIF_HANDLE;
						tvi1.hItem=hTreeItem;
						tvi1.pszText = Text;
						SendMessage(GetDlgItem(hwnd,123),TVM_GETITEM,0,(WPARAM)&tvi1);
						MessageBox(hwnd,Text,"Text",MB_OK);
						*/
						//MessageBox(hgf->hwndFrom,"RRRR clicked button","RRR clicked button",0);
						}

						break;
					case NM_HOVER:
						
						MessageBox(hwnd,"HOVER","HOVER",0);
						break;

					case NM_SETFOCUS :

							// MessageBox(hwnd,"SETFOCUS","SETFOCUS",0);
						break;
					case TVN_ITEMEXPANDING :

					//	MessageBox(hwnd,"++ --","++ --",0);
						
						break;



						case TVN_KEYDOWN :

							MessageBox(hwnd,"TVN_KEYDOWN ","TVN_KEYDOWN ",0);
							
							break;

							
					case TVN_GETDISPINFO:
						{
							
							/*
						
						TV_DISPINFO FAR *ptvdi =(TV_DISPINFO FAR *)lparam;
						TV_DISPINFO *pTVDispInfo(TV_DISPINFO*)lparam;
						pTVDispInfo->item->pszText;
						MessageBox(0,pTVDispInfo->item->pszText,0,0);
						*/
							MessageBox(hwnd,"TVN_GETDISPINFO","TVN_GETDISPINFO",0);
						}
						
						break;
						case TVN_DELETEITEM:
					
							 MessageBox(hwnd,"TVN_DELETEITEM","TVN_DELETEITEM",0);
						
						break;
						case TVN_ITEMCHANGING:
							 MessageBox(hwnd,"TVN_ITEMCHANGING","TVN_ITEMCHANGING",0);
							break;

						case TVN_SELCHANGED:
						{

								char str[455];
								NMTREEVIEW* pnmtv =(LPNMTREEVIEW)lparam;
								TVITEM item;
								item.hItem=pnmtv->itemNew.hItem;
								item.mask=TVIF_TEXT;
								item.pszText=str;
								item.cchTextMax=455;
								SendMessage(GetDlgItem(hwnd,123),TVM_GETITEM,0,(LPARAM)&item);

								GetClientRect(hwnd,&r);

							//		MessageBox(0,str,0,0);
				  
								 int vco=0;
								for(int i=0;i<=strlen(str);i++)

								{
								
									if(str[i]==(char)92)
									{   
										path[vco]=(char)92;
										vco++;
									
									}

									path[vco]=str[i];
									vco++;
								}

						  
								bvb= (HBITMAP)LoadImage(NULL,path, IMAGE_BITMAP,r.right-200,r.bottom-1, LR_LOADFROMFILE);
								
							

								SendMessage(hstatic,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)bvb);
						}

						break;



						case WM_INITDIALOG:
{


   InitCommonControls();    
}
					}
				
				
				}
				break;

			}

					

	//		if(wparam==10)
				switch(LOWORD(wparam))
				{
					
				//5	MessageBox(hwnd,"No Items in TreeView","Error",MB_OK|MB_ICONINFORMATION);


				}
			if(((LPNMHDR)lparam)->code == NM_CLICK) 
			{

			

		//	MessageBox(hwnd,"No Items in TreeView","Error",MB_OK|MB_ICONINFORMATION);

			Selected=(HTREEITEM)SendDlgItemMessage (hwndtree,1,TVM_GETNEXTITEM,TVGN_DROPHILITE,0);
				if(Selected==NULL)
				{
				//		MessageBox(hwnd,"No Items in TreeView","Error",MB_OK|MB_ICONINFORMATION);
					break;
				}	

				//////////////////////////////////////////////////////////////////

break;


			}