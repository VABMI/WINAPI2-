

//---------------------------------------------
long __stdcall on_create(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{

HWND hw=0;
int X,Y,W,H;
DWORD style=WS_VISIBLE|WS_CHILD|WS_BORDER;
X=0;Y=0;W=80;H=20;
hw=CreateWindow("button","CREATE",style,X,Y,W,H,hwnd,(HMENU)10,0,0);
CreateWindow("button","ELETE",style,X,Y+150,W,H,hwnd,(HMENU)11,0,0);
X=100;
//hw=CreateWindow("edit","DELETE",style,200,Y,200,400,hwnd,(HMENU)20,0,0);

CreateWindow("button","open",style,0,30,50,30,hwnd,(HMENU)12,0,0);


CreateWindow("button","start",style,0,65,50,30,hwnd,(HMENU)13,0,0);

CreateWindow("button","stop",style,0,100,50,30,hwnd,(HMENU)14,0,0);
return 0;
}