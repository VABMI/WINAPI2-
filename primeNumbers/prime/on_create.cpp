

long __stdcall on_create(HWND hwnd,unsigned int message,unsigned int wparam,long lparam)
{


hw=0;
int X,Y,W,H;
DWORD style=WS_VISIBLE|WS_CHILD|WS_BORDER;

X=10;Y=30;W=100;H=100;
hw=CreateWindow("button","button",style,X,Y,W,H,hwnd,(HMENU)10,0,0);
SendMessage(hw,WM_SETFONT,0,0);

X=150;Y=230;W=500;H=100;
hw=CreateWindow("edit",0,WS_VSCROLL|WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL,X,Y,W,H,hwnd,(HMENU)20,0,0);
SendMessage(hw,WM_SETFONT,0,0);
SendMessage(hw,EM_LIMITTEXT,100000000000,0);

X=150;Y=30;W=500;H=100;
hw=CreateWindow("edit",0,style,X,Y,W,H,hwnd,(HMENU)30,0,0);
SendMessage(hw,WM_SETFONT,0,0);


return 0;
}