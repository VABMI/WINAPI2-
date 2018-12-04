

DWORD WINAPI SEND(void* sock,string userInput)
{
			
	if(userInput.size() > 0) ///    c_str utitebs  userInput ze misamartze rac weria anu send agzavnis orobitshi da cherez operatiulida akitxebs ororbitshi
	{
		int sendResult = send((unsigned __int64) sock,userInput.c_str(),userInput.size()+1,0);
		if(sendResult != SOCKET_ERROR)
		{
			

			MessageBox(0,L"ar gaigzavna",L"error",0);

		}
	
	}






	

	return 0;
}



void * CreateSoket(unsigned __int64  *soket1)
{

		
	//	FreeConsole();
char *ipin;
//scanf("%s",&ipin);
int port = 8080;
string ipAddress="188.169.18.47";
WSAData data;
WORD ver = MAKEWORD(2,2);
int wsResult = WSAStartup(ver,&data);
if(wsResult != 0)
{

	cerr<<"can't start Winsock, err "<<wsResult<<endl;
	return 0;
}


SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
if(sock == INVALID_SOCKET)
{


	cerr <<"can't create socket,Err #"<<WSAGetLastError()<<endl;
	WSACleanup();
	return 0;
}

sockaddr_in hint;
hint.sin_family = AF_INET;
hint.sin_port = htons(port);
inet_pton(AF_INET,ipAddress.c_str(),&hint.sin_addr); /// ver gavigee

L:
int connResult = connect(sock,(sockaddr*)&hint,sizeof(hint));

if(connResult == SOCKET_ERROR)
{

	goto L;
	/*
	cerr <<"Can't connect to server ,err111 "<<WSAGetLastError()<<endl;
	closesocket(sock);
	WSACleanup();
	return 0;
	*/
}
*soket1=sock;
return (void*)sock;

}


