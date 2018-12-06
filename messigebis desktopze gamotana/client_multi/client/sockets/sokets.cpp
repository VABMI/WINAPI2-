void*soketss(SOCKET *sock)
{

	
char *ipin;
//scanf("%s",&ipin);
int port = 8786;
string ipAddress="188.169.18.47";
cout<<"sheiyvane IP->: ";
	//cin>>ipAddress;
cout<<endl<<"sheiyvane PORT_N->:";
	//cin>>port;
cout<<endl<<"________________\n";
WSAData data;
WORD ver = MAKEWORD(2,2);
int wsResult = WSAStartup(ver,&data);
if(wsResult != 0)
{

	cerr<<"can't start Winsock, err "<<wsResult<<endl;
	return 0;
}


 *sock = socket(AF_INET,SOCK_STREAM,0);
if(*sock == INVALID_SOCKET)
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
int connResult = connect(*sock,(sockaddr*)&hint,sizeof(hint));

if(connResult == SOCKET_ERROR)
{
	goto L;
	/*
	cerr <<"Can't connect to server ,err "<<WSAGetLastError()<<endl;
	closesocket(sock);
	WSACleanup();
	return;
	*/

}


return (void*)sock;
}