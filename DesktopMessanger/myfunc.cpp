
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

//---------------------------------------------
DWORD WINAPI RECIVE(void* sock1)
{
	
	static bool firststart=0;
	char buf[4096];
	HWND hwnd1=GetDlgItem((HWND)sock1,21);
while(1)
{
	




				ZeroMemory(buf,4096);
			int bytesReceived = recv((unsigned __int64 )sock,buf,4096,0);
			if(bytesReceived>0)
			{
				if(strlen(buf)>0&&buf[0]!='@'){
			//	cout <<string(buf,0,bytesReceived)<<endl;
				
					//ShowWindow((HWND)sock1,0);
					SendMessage(hwnd1,EM_REPLACESEL,strlen(buf),(LPARAM)buf);

				}
				//////////////////// userebis gamotanaaa ////////////////////////
				else if(buf[0]=='@')
				{			buf[0]=' ';
					MessageBox(HwndParent,buf,buf,0);
				}
			//////////////////////////////////////////////////////////////////////
			}
			else{


				break;

			}




}
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
//closesocket(sock);



return 0;
}

//---------------------------------------------
DWORD WINAPI ACTIVENOW(HWND sock1,char *name)
{
	char USERSBUF[9024];

	
			int sendResult = send((unsigned __int64) sock,"@",2,0);
			if(sendResult)
			{
				ZeroMemory(USERSBUF,9024);
				int bytesReceived1=0 ;//= recv((unsigned __int64 )sock,USERSBUF,9024,0);
				if(bytesReceived1>0)
				{
					if(USERSBUF[0]=='@')
					{		
							if(bytesReceived1>0)
							{
							//	MessageBox(0,USERSBUF,USERSBUF,0);

							}
						

					}
			
				//MessageBox(0,"asdasd","Asdasd",0);


				}
		

			}

	return 0;
}
//---------------------------------------------
void SocketisSheqmna(HWND hwnd)
{
		
char *ipin;
//scanf("%s",&ipin);
int port = 8080;
string ipAddress="127.0.0.1";
WSAData data;
WORD ver = MAKEWORD(2,2);
int wsResult = WSAStartup(ver,&data);
if(wsResult != 0)
{
	MessageBox(hwnd,"can't start Winsock, err ","can't start Winsock, err ",0);
//	cerr<<"can't start Winsock, err "<<wsResult<<endl;
exit(1);
	return;
}


 sock = socket(AF_INET,SOCK_STREAM,0);
if(sock == INVALID_SOCKET)
{

	MessageBox(hwnd,"can't create socket,Err # ","can't create socket,Err #",0);	
	exit(1);
	//cerr <<"can't create socket,Err #"<<WSAGetLastError()<<endl;
	WSACleanup();
	return;
}

sockaddr_in hint;
hint.sin_family = AF_INET;
hint.sin_port = htons(port);
inet_pton(AF_INET,ipAddress.c_str(),&hint.sin_addr); /// ver gavigee


int connResult = connect(sock,(sockaddr*)&hint,sizeof(hint));

if(connResult == SOCKET_ERROR)
{

	MessageBox(hwnd,"Can't connect to server ,err ","Can't connect to server ,err ",0);
	//cerr <<"Can't connect to server ,err "<<WSAGetLastError()<<endl;
	closesocket(sock);
	WSACleanup();

	exit(1);
	return;

}

//////////////////////// shesvlis dros dzveli smsebis gamotanaaa ////////////////////////////////////////
			char buff[10];
			//char *buf=(char*)malloc(4000096);
			ZeroMemory(buff,sizeof(buff));
			int bytesReceived = recv((unsigned __int64 )sock,buff,10,0);
			int sizee=atoi(buff);
			char *buf=(char*)malloc(sizee);
			ZeroMemory(buf,sizeof(buf));
			bytesReceived = recv((unsigned __int64 )sock,buf,sizee,0);
			if(bytesReceived>0)
			{
				if(strlen(buf)>0)
				{

					
					buf[sizee]='\0';
					
					SendMessage(GetDlgItem(hwnd,21),WM_SETTEXT,strlen(buf),(LPARAM)buf);
				
					//free(buf);
					
				}
			}

////////////////////////END  shesvlis dros dzveli smsebis gamotanaaa ////////////////////////////////////////

	HANDLE fgh=CreateThread(NULL,NULL,RECIVE,(void*)hwnd,0,NULL);


}
//---------------------------------------------
DWORD WINAPI SEND(HWND sock1,char *name)
{
		HWND hwnd=GetParent(sock1);
	char *userInput=(char*) malloc(100);
	char *sendU=(char*) malloc(1000);

	
	

		//cout<< "clienti > ";
		//scanf("%s",userInput,stdin);
		ZeroMemory(userInput,sizeof(userInput));
		ZeroMemory(sendU,sizeof(userInput));
		GetWindowText(sock1,userInput,99);
		


		if(userInput[0]==13)
		{
			userInput[0]=' ';
					//MessageBox(0,"ar gaigzavna","error",0);

		}
		gets(userInput);
		if(strlen(userInput)<=0)
		{
			//strcpy(userInput,"sheitane striqoni\r\n");
		}
		if(strlen(userInput) > 0) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
		{

		
			strcat(sendU,(char*)name);
			strcat(sendU," |>:");
			strcat(sendU,userInput);
			strcat(sendU,"\r\n");
			int sendResult = send((unsigned __int64) sock,sendU,strlen(sendU)+1,0);
			if(sendResult == SOCKET_ERROR)
			{
			

				MessageBox(0,"Serveri gaitisha","error",0);
				SocketisSheqmna(hwnd);
				return 0;

			}
			else{

			
				SendMessage(GetDlgItem(hwnd,21),EM_REPLACESEL,strlen(sendU),(LPARAM)sendU);

			}
	
		}






	free(userInput);
	free(sendU);
	return 1;
}
//---------------------------------------------


HWND WINAPI CreateTrackbar(HWND hwnd, UINT iMin,UINT iMax,UINT iSelMin, UINT iSelMax,int left,int top,int numm,ULONG style,int width,int height)
{

HWND	hwndTrack=CreateWindowEx(0,TRACKBAR_CLASS,"trackBar",WS_CHILD|WS_BORDER|WS_VISIBLE|TBS_AUTOTICKS|TBS_ENABLESELRANGE|style,118,650,width,height,hwnd,(HMENU)numm,0,0);
	
	SendMessage(hwndTrack,TBM_SETPOS,100,(LPARAM)100);


	//SendMessage(hwndTrack,TBM_SETRANGE,(WPARAM)1,(LPARAM)MAKELONG(iMin,iMax));
//	SendMessage(hwndTrack,TBM_SETPAGESIZE,100,(LPARAM)100);
	SendMessage(hwndTrack,TBM_SETSEL,(WPARAM)160,(LPARAM)MAKELONG(40,100));

	SetFocus(hwndTrack);


	HCURSOR hCursor=LoadCursorFromFile("Glove Normal.cur");
	SetCursor(hCursor);
	SetClassLong(hwndTrack, -12, (DWORD)hCursor);





	return 0;
}