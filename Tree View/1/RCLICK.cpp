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