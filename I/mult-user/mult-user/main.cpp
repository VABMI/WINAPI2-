#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#pragma comment (lib,"WS2_32.lib")
using namespace std;
void main()
{
#include "CreateSocket.cpp"

	int count=1; /// userebis 
	char countbuf[100];
	char buf[4096];
	char cbuff[10];
	int bytesIn;
	int i;
	int socketCount;
	///////////////////// LoadImage.cpp failis ////////////////

	int Size;
	char *Filesize = new char[1024];
	
	//////////////////////////////////////////////////////////
	while(true)
	{
		
		fd_set copy=master;
		 socketCount=select(0,&copy,nullptr,nullptr,nullptr);
		
		for( i=0;i<socketCount;i++)
		{	
			SOCKET sock=copy.fd_array[i];
#include"NewUser.cpp" //// axali useris shemosvlis damateba 
		
	
			else
			{
			
				
				ZeroMemory(buf,4096);
				bytesIn = recv(sock,buf,4096,0);
				cout<<buf<<endl;
#include"ID.cpp"

#include"LoadImage.cpp"

				else if(bytesIn>0)
				{
					L:

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
	free(Filesize);
	WSACleanup();
}




	



