bool martivi(int x){
	for(int i=2;i<=x/2;i++)
		if(x%i==0)return false;
		return true;
}


long __stdcall cmd_msg(HWND hwnd,unsigned int message
					,unsigned int wparam,long lparam)

{

int ctrl_id = (unsigned short)wparam;
	if(ctrl_id==200)
	{

	}

	else if(ctrl_id==10)
	{
		if(HIWORD(wparam)==BN_CLICKED){
	
	HWND h=0;
	HWND h1=0;
	char x[100];
	int q;
	char a[100];


	
	h=GetDlgItem(hwnd,20);
	h1=GetDlgItem(hwnd,30);
	GetWindowTextA(h1,x,100);

	q = atoi(x);
	////sprintf(x, "%s%d", " ", q);


	for(int i=0;i<=q;i++)
		if(martivi(i)){
		sprintf(a, "%s%d", " ", i);
		SendMessage(h,EM_REPLACESEL,0,(LPARAM)a);
		}


	//SendMessage(h,EM_REPLACESEL,0,(LPARAM)a);
	//SetWindowTextA(h,a);
		}
	}


return 0;
}