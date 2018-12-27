#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#pragma comment (lib,"WS2_32.lib")
using namespace std;
void main()
{

//	FreeConsole();
	WSADATA wsData;
	WORD ver = MAKEWORD(2,2);
	int WsOK = WSAStartup(ver,&wsData);
	if(WsOK !=0)
	{
	//	cerr <<"Can't Initialize Wins"<<endl;
		return;
	}


	SOCKET listening = socket(AF_INET,SOCK_STREAM,0);
	if(listening == INVALID_SOCKET)
	{

		cerr << "Can't create a socket! "<<endl;
		return;

	}






	sockaddr_in hint;
	hint.sin_family=AF_INET;
	hint.sin_port=htons(8786);
	hint.sin_addr.S_un.S_addr=INADDR_ANY; /// ver gavige



	bind(listening,(sockaddr*)&hint,sizeof(hint));
	listen(listening,SOMAXCONN);


	int count=0;

	fd_set master;
	FD_ZERO(&master);
	FD_SET(listening,&master);
	char countbuf[100];
		char buf[4096];
		char cbuff[10];
		int bytesIn;
		int i;
	int socketCount;
	while(true)
	{
		
		fd_set copy=master;
		 socketCount=select(0,&copy,nullptr,nullptr,nullptr);
		
		for( i=0;i<socketCount;i++)
		{
			SOCKET sock=copy.fd_array[i];
			if(sock==listening)
			{
					
				////accept a new connection
				SOCKET client=accept(listening,nullptr,nullptr);
				//Add the new connection tothelisof connected clients

				FD_SET(client,&master);

				ZeroMemory(cbuff,sizeof(cbuff));
				sprintf(cbuff,"%i",count);
			//	strcat(countbuf,cbuff);
				//strcat(countbuf,"\r\n");
				send(client,cbuff,strlen(cbuff)+1,0);
				count++;
				///Sleep(100);
				send(client,cbuff,strlen(cbuff)+1,0);

			}

			else
			{
			
				
				ZeroMemory(buf,4096);
				bytesIn = recv(sock,buf,4096,0);
				cout<<buf<<endl;
#include"ID.cpp"

#include"LoadImage.cpp"

				else if(bytesIn>0)
				{

					for(i=0;i<master.fd_count;i++)
					{
						SOCKET outSock = master.fd_array[i];
						if(outSock != listening && outSock !=sock)
						{
							send(outSock,buf,bytesIn,0);


						}

					}

				}
				else if(bytesIn<=0)
				{
					closesocket(sock);
					FD_CLR(sock,&master);
				//	MessageBox(0,"error",0,0);

				}



			
			}

		}
		//ZeroMemory(&copy,sizeof(copy));

	}

	WSACleanup();
}




	



