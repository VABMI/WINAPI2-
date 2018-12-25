#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#pragma comment (lib,"WS2_32.lib")
using namespace std;

#include "ReadWrite.cpp"
void main()
{

	//FreeConsole();
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

	//	cerr << "Can't create a socket! "<<endl;
		return;

	}






	sockaddr_in hint;
	hint.sin_family=AF_INET;
	hint.sin_port=htons(8080);
	hint.sin_addr.S_un.S_addr=INADDR_ANY; /// ver gavige



	bind(listening,(sockaddr*)&hint,sizeof(hint));
	listen(listening,SOMAXCONN);




	fd_set master;
	FD_ZERO(&master);
	FD_SET(listening,&master);
	
	while(true)
	{

		fd_set copy=master;
		int socketCount=select(0,&copy,nullptr,nullptr,nullptr);

		for(int i=0;i<socketCount;i++)
		{
			SOCKET sock=copy.fd_array[i];
			if(sock==listening)
			{

				////accept a new connection
				SOCKET client=accept(listening,nullptr,nullptr);
				//Add the new connection tothelisof connected clients

				FD_SET(client,&master);

				//char* buff12=(char*)malloc(sizee);
					send(client,(const char*)"1",1,0);
			//	Read("F:\\WINAPI2-\\I\\mult-user-messanger\\mult-user\\SMS.txt", client);
					send(client,(const char*)" ",1,0);
			
				//free(buff12);
			}

			else
			{
				char buf[4096];
				ZeroMemory(buf,4096);
				int bytesIn = recv(sock,buf,4096,0);
				if(bytesIn<=0)
				{
					closesocket(sock);
					FD_CLR(sock,&master);


				}
				else
				{
					Save(buf,"D:\\WINAPI2-\\I\\mult-user-messanger\\mult-user\\SMS.txt");
					//////////////////////////////////////////// userebis gamotana  ACTIVE NOW ////////////////////////////
					if(buf[0]=='@')
					{
						ZeroMemory(buf,4096);
						strcat(buf,"@");
						strcat(buf,"USEREBIIII");
							if(send(sock,buf,strlen(buf),0))
							{
								//MessageBox(0,"gaigzavna",0,0);

							}


					}
						////////////////////////////////////////////END userebis gamotana  ACTIVE NOW ////////////////////////////
					//////////////////////////////////// registraciaaaa //////////////////////////////////////


					/*
					if(buf[0]=='~')
					{///F:\\WINAPI2-\\I\\mult-user-messanger\\mult-user\\USERS.txt

						char buf[100];
							ZeroMemory(buf,4096);
								bytesIn = recv(sock,buf,4096,0);
								/////////////////////////////////////////////////////////////////////////////
							FILE *file;
							file=fopen("F:\\WINAPI2-\\I\\mult-user-messanger\\mult-user\\USERS.txt","rb");

	
							fseek(file,0,SEEK_END);
							int size=ftell(file);
							fseek(file,0,SEEK_SET);

							 char *cv;	
							 cv=( char*)malloc(size);
							if(cv==NULL){

							}
							else
								{
									char users[20];

								 while(!feof(file))
								 {
									 
									fgets(users,size,file);
									////////////// enteris mocileba ////////////////
									if(users[strlen(users)-2]==13)
									{

										users[strlen(users)-2]=0;
									}
									///////////////////////////////////////////////

										if(strcmp(users,buf)!=0)
										{	
											strcat(cv,users);
											strcat(cv,"\r\n");
										MessageBox(0,users,users,0);
										}
										else
										{



											goto L;
										}
								 }			
								/////////////////////// failshi chawera user userebis /////////////////////
								 MessageBox(0,cv,users,0);
								 ///////////////////////////////////////////////////////////////////////
								 L:
									fclose(file);
							}
						
							/////////////////////////////////////////////////////////////////////////////
						//strcat(userr,"\r\n");
						////////// chawera active userebis failshi  //////
					//	buf[0]=' ';



					

					
						if(bytesIn)
						{

						//	MessageBox(0,buf,cv,0);
						
						}
						

					}

						*/
					////////////////////////////////////////////////////////////////////////////////////////////////
					
					
					else
					{
						for(int i=0;i<master.fd_count;i++)
						{
							SOCKET outSock = master.fd_array[i];
							if(outSock != listening && outSock !=sock)
							{
								send(outSock,buf,bytesIn,0);


							}

						}
					}
				}
			
			}

		}

	}

	WSACleanup();
}




	



