
HWND hwndeditout=NULL; 
HWND    g_hwndButton            = NULL;  
HWND       g_hwndButton1	=	NULL;
WNDPROC g_wndProcButtonOrigianl = NULL;   
BOOL    g_bSeeingMouse          = FALSE;





LRESULT CALLBACK edit (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
		PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	char name[100];
	   WNDPROC wpOld = (WNDPROC)GetWindowLongPtr(g_hwndButton, GWLP_USERDATA);
	   HWND hwnd1=GetParent(hwnd);
	   HWND USER=GetDlgItem(hwnd1,23);
	 switch( message )
    {

	
		case WM_PAINT:
			 
		SetLayeredWindowAttributes(hwnd,  0,  
		(255 * 70) / 100, LWA_COLORKEY);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);
		 SetBkMode ((HDC)wParam, TRANSPARENT);
			/*
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawPicture(hdc, &rect);
		EndPaint(hwnd, &ps);
		 SetBkColor(hdc,RGB(255,32,79));
	
		SetBkMode (HDc, TRANSPARENT);
		TextOut (HDc, 0, 0, L"Text", 4);
		ReleaseDC (hWnd, HDc);
		*/
      break;

	      case WM_KEYDOWN:

			  	if(wParam==13)
				{
					
					GetWindowText(USER,name,99);
				
					if(SEND(hwnd,(char*)name))
					{
												
						SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)0);

					}
					//// gagzavna
					//	MessageBox(0,"button","asada",0);

				}
		
			   
			  break;

    }





    return CallWindowProc( g_wndProcButtonOrigianl, hwnd, message, wParam, lParam );
}


LRESULT CALLBACK edit2 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char name[100];
	   WNDPROC wpOld = (WNDPROC)GetWindowLongPtr(g_hwndButton, GWLP_USERDATA);
	   HWND hwnd1=GetParent(hwnd);
	   HWND USER=GetDlgItem(hwnd1,23);
	 switch( message )
    {
	 case WM_PAINT:
		 {
			 /*
			SetLayeredWindowAttributes(hwnd,  0,  
		(255 * 20) / 100, LWA_COLORKEY);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);
		// SetBkMode ((HDC)wParam, TRANSPARENT);
		*/
		///////////////////////////////////////////////////////
				 }
			
      break;

	  case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		//	lpMMI->ptMinTrackSize.x = 1336-350;
		//	lpMMI->ptMinTrackSize.y = 28;
			lpMMI->ptMaxTrackSize.y=428;
			//lpMMI->ptMaxPosition.y=50;
			
		}
	      case WM_KEYDOWN:

			   
			  break;

    }


    return CallWindowProc( g_wndProcButtonOrigianl, hwnd, message, wParam, lParam );
}
