
//---------------------------------------------
UINT create_menu(HWND hwnd)
{
HMENU hmenu=CreateMenu();
	if(!hmenu)
	return GetLastError();

HMENU hmenu_popup_file=CreatePopupMenu();
AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hmenu_popup_file,"&File");
AppendMenu(hmenu_popup_file,MF_STRING,100,"&ABCD");
AppendMenu(hmenu_popup_file,MF_STRING,200,"&RTY");

HMENU hmenu_popup_options=CreatePopupMenu();
AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hmenu_popup_options, "&Options");
AppendMenu(hmenu_popup_options,MF_STRING,300,"&3");
AppendMenu(hmenu_popup_options,MF_STRING,400,"&4");
SetMenu(hwnd,hmenu);
}
//---------------------------------------------
HFONT create_font(HWND hwnd)
{
HFONT hfont;
hfont=CreateFont(23,14,1,1,FW_BOLD,1,1,1,ANSI_CHARSET, 
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
      DEFAULT_PITCH | FF_DONTCARE,"Tahoma");
SendMessage(hwnd,WM_SETFONT,(UINT)hfont,0);
return hfont;
}
//---------------------------------------------
long __stdcall on_create(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{
create_menu(hwnd);
HFONT hfont=create_font(hwnd);


HWND hw=0;
int X,Y,W,H;
DWORD style=WS_VISIBLE|WS_CHILD|WS_BORDER;
X=0;Y=0;W=80;H=20;
hw=CreateWindow("button","CREATE",style,X,Y,W,H,hwnd,(HMENU)10,0,0);

X=100;
hw=CreateWindow("button","DELETE",style,X,Y,W,H,hwnd,(HMENU)20,0,0);

X+=100;
hw=CreateWindow("button","START",style,X,Y,W,H,hwnd,(HMENU)30,0,0);
X+=100;
hw=CreateWindow("button","RUNING",style,X,Y,W,H,hwnd,(HMENU)40,0,0);
X+=100;
hw=CreateWindow("button","STARTING",style,X,Y,W,H,hwnd,(HMENU)50,0,0);

return 0;
}