
long __stdcall on_create(HWND hwnd,unsigned int message	, unsigned int wparam,long lparam)
{
RECT r;
GetClientRect(hwnd,&r);
//create_menu(hwnd);
//HFONT hfont=create_font(hwnd);

hwndeditout=CreateWindow("edit","",WS_VISIBLE|WS_THICKFRAME|WS_CHILD|ES_MULTILINE|ES_READONLY|WS_VSCROLL,15,30,332,250,hwnd,(HMENU)21,0,0);
	g_wndProcButtonOrigianl = (WNDPROC)SetWindowLongPtr( hwndeditout, GWLP_WNDPROC, (LONG_PTR)edit2);


g_hwndButton=CreateWindow("edit","",WS_VISIBLE|WS_CHILD|ES_MULTILINE,15,678,350,50,hwnd,(HMENU)22,0,0);
	g_wndProcButtonOrigianl = (WNDPROC)SetWindowLongPtr( g_hwndButton, GWLP_WNDPROC, (LONG_PTR)edit );

CreateWindow("edit","USER",WS_VISIBLE|WS_BORDER|WS_CHILD,15,650,100,27,hwnd,(HMENU)23,0,0);

//int RED;
CreateTrackbar(hwnd,0,300,10,50,10,10,24,TBS_HORZ,230,27);

////////////////////// setingebi /////////////////////////////////////
HCURSOR hCursor;
///////////////////////////////////////////////////////////////////////

g_hwndButton1=CreateWindow("button","><",WS_VISIBLE|WS_CHILD,0,0,12,r.bottom,hwnd,(HMENU)10,0,0);
	g_wndProcButtonOrigianlR = (WNDPROC)SetWindowLongPtr( g_hwndButton1, GWLP_WNDPROC, (LONG_PTR)button1);

  buttonX=CreateWindow("button","X",WS_VISIBLE|WS_CHILD,15,0,80,20,hwnd,(HMENU)CLOSE,0,0);
  	g_wndProcButtonOrigianlX = (WNDPROC)SetWindowLongPtr( buttonX, GWLP_WNDPROC, (LONG_PTR)buttonXX );


	//buttonX=CreateWindow("button","ACTIVE NOW",WS_VISIBLE|WS_CHILD,r.right-100,0,100,20,hwnd,(HMENU)ACTIVEBOW,0,0);
	//  	g_wndProcButtonOrigianlX = (WNDPROC)SetWindowLongPtr( buttonX, GWLP_WNDPROC, (LONG_PTR)buttonXX );


	//	CreateWindow("button","SAVE",WS_VISIBLE|WS_CHILD,r.right-100,300,100,20,hwnd,(HMENU)SAVEBUTTON,0,0);
		

return 0;
}