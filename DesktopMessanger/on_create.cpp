
long __stdcall on_create(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{
	RECT r;
GetClientRect(GetDesktopWindow(),&r);
//create_menu(hwnd);
HFONT hfont=create_font(hwnd);
hwndeditout=CreateWindow("edit","",WS_VISIBLE|WS_THICKFRAME|WS_CHILD|ES_MULTILINE|ES_READONLY|WS_VSCROLL,15,30,332,250,hwnd,(HMENU)21,0,0);
g_wndProcButtonOrigianl = (WNDPROC)SetWindowLongPtr( hwndeditout, GWLP_WNDPROC, (LONG_PTR)edit2);


g_hwndButton=CreateWindow("edit","",WS_VISIBLE|WS_CHILD|ES_MULTILINE,15,678,350,50,hwnd,(HMENU)22,0,0);

g_wndProcButtonOrigianl = (WNDPROC)SetWindowLongPtr( g_hwndButton, GWLP_WNDPROC, (LONG_PTR)edit );

CreateWindow("edit","USER",WS_VISIBLE|WS_BORDER|WS_CHILD,15,650,100,27,hwnd,(HMENU)23,0,0);

//int RED;
CreateTrackbar(hwnd,0,300,10,50,10,10,24,TBS_HORZ,230,27);

////////////////////// setingebi /////////////////////////////////////
HCURSOR hCursor=LoadCursorFromFile("F:\\WINAPI2-\\DesktopMessanger\\Debug\\4.ico");
//g_hwndButton=CreateWindow("button","SAVE",WS_VISIBLE|WS_CHILD,24,1,60,18,hwnd,(HMENU)12,0,0);

// g_hwndButton=CreateWindow("button","Clear",WS_VISIBLE|WS_CHILD,262,1,60,18,hwnd,(HMENU)13,0,0);

 //SetWindowLongPtr(g_hwndButton, GCL_HCURSOR, (LONG)hCursor);

///////////////////////////////////////////////////////////////////////

g_hwndButton=CreateWindow("button","><",WS_VISIBLE|WS_CHILD,0,0,12,r.bottom-40,hwnd,(HMENU)10,0,0);
	 hCursor=LoadCursorFromFile("4.ico");
	SetCursor(hCursor);
	SetClassLong(g_hwndButton, -12, (DWORD)hCursor);


return 0;
}