
#include "stdafx.h"
HFONT hfont_global;
HWND globh;
		
bool b1=0;
//----------------------------------------------------------------

DWORD WINAPI Thread_no_1( void** bufer1 ) 
{
	
			   int x=(int)bufer1[0];
			     static char buf2[999999999];
				
				
			  
					  for(int i=(int)bufer1[0];i<=(int)bufer1[1];i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
								else if(i==j+1)
								{
									char buffer[2000];

									sprintf(buffer,"%i",i);
								//	itoa(i,buffer,90);
									strcat(buf2,(char*)buffer);
									//strcat(buf2,"\n\r");
									strcat(buf2,"|_| ");
							
									SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);
								}
							}
						}

				
					


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
						
					

	return 1; 
} 
DWORD WINAPI Thread_no_2( void** bufer1 ) 
{
	
			   int x=atoi((char*)bufer1);


			  static char buf2[100000];



					  for(int i=(int)bufer1[1];i<=(int)bufer1[2];i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
									else if(i==j+1)
								{
									char buffer[2000];
									sprintf(buffer,"%i",i);
									//	itoa(i,buffer,10);
									strcat(buf2,(char*)buffer);
									strcat(buf2,"|_| ");
								}
						}
					  }



					  L:

					  if(b1==1){

					  SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);
					  }

					  else{ goto L;}
					//	MessageBox(0,buf2,buf2,0);

					
	return 1; 
} 
DWORD WINAPI Thread_no_3( void** bufer1 ) 
{
	
			   int x=(int)bufer1[0];
			     static char buf2[999999999];
				
				
			  
					  for(int i=(int)bufer1[2];i<=(int)bufer1[3];i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
								else if(i==j+1)
								{
									char buffer[2000];

									sprintf(buffer,"%i",i);
								//	itoa(i,buffer,90);
									strcat(buf2,(char*)buffer);
									//strcat(buf2,"\n\r");
									strcat(buf2,"|_| ");
							
									SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);
								}
							}
						}

				
					


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
						
					

	return 1; 
} 
DWORD WINAPI Thread_no_4( void** bufer1 ) 
{
	
			   int x=(int)bufer1[0];
			     static char buf2[999999999];
				
				
			  
					  for(int i=(int)bufer1[3];i<=(int)bufer1[4];i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
								else if(i==j+1)
								{
									char buffer[2000];

									sprintf(buffer,"%i",i);
								//	itoa(i,buffer,90);
									strcat(buf2,(char*)buffer);
									//strcat(buf2,"\n\r");
									strcat(buf2,"|_| ");
							
									SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);
								}
							}
						}

				
					


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
						
					

	return 1; 
} 
DWORD WINAPI Thread_no_5( void** bufer1 ) 
{
	
			   int x=(int)bufer1[0];
			     static char buf2[999999999];
				
				
			  
					  for(int i=(int)bufer1[4];i<=(int)bufer1[5];i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
								else if(i==j+1)
								{
									char buffer[2000];

									sprintf(buffer,"%i",i);
								//	itoa(i,buffer,90);
									strcat(buf2,(char*)buffer);
									//strcat(buf2,"\n\r");
									strcat(buf2,"|_| ");
							
									SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);
								}
							}
						}

				
					


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
						
					

	return 1; 
} 
DWORD WINAPI Thread_no_6( void** bufer1 ) 
{
	
			   int x=(int)bufer1[0];
			     static char buf2[999999999];
				
				
			  
					  for(int i=(int)bufer1[5];i<=(int)bufer1[6];i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
								else if(i==j+1)
								{
									char buffer[2000];

									sprintf(buffer,"%i",i);
								//	itoa(i,buffer,90);
									strcat(buf2,(char*)buffer);
									//strcat(buf2,"\n\r");
									strcat(buf2,"|_| ");
							
									SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);
								}
							}
						}

				
					


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
						
					

	return 1; 
} 
//----------------------------------------------------------------
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message
					, unsigned int wparam,long lparam)
{				
	
	
	
	





	switch(message)
	{
		case WM_CREATE:
			{ 
				
				globh=hwnd;
				RECT r;
				CreateWindow("edit","Main",WS_CHILD|WS_BORDER|WS_VISIBLE,0,0,150,30,hwnd,(HMENU)1,0,0);

				CreateWindow("Button","gashveba",WS_CHILD|WS_BORDER|WS_VISIBLE,155,0,80,30,hwnd,(HMENU)2,0,0);
				GetClientRect(hwnd,&r);
				globh=CreateWindow("edit","",WS_CHILD|WS_BORDER|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|ES_MULTILINE,0,50,r.right,r.bottom-55,hwnd,(HMENU)3,0,0);
				SendMessage(globh,EM_SETLIMITTEXT,1000000,0);



			}
		break;
		
		case WM_COMMAND:
			{

				if(wparam==2)
				{	
					int dd=2;
					
					SendMessage(globh,WM_SETTEXT,0,(LPARAM)"");
					
					
					static int arr[100];
					char bufer[100];
					SendMessage(GetDlgItem(hwnd,1),WM_GETTEXT,100,(LPARAM)bufer);
					//MessageBox(0,bufer,bufer,0);
					int value=atoi(bufer);
					
					arr[0]=2;
					arr[1]=(value/dd);
					arr[2]=(arr[1]+(value/dd));
					arr[3]=(arr[2]+(value/dd));
					arr[4]=(arr[3]+(value/dd));
					arr[5]=(arr[4]+(value/dd));
				//	arr[1]=value;
				//	arr[2]=(int)hwnd;
				//	int val1=(value/2);
				

						HANDLE Thread1=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_1,&arr,0,0);
						/*
						Thread1=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_2,&arr,0,0);

						Thread1=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_3,&arr,0,0);

						Thread1=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_4,&arr,0,0);
				
						Thread1=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_5,&arr,0,0);

						*/



					
					//	WaitForSingleObject(Thread1,INFINITE);
					//	SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);

					//	HANDLE Thread2=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_2,&arr,0,0);
				

				//	system("pause");
			//	MessageBox(0,"gacdaaaa",bufer,0);

			
				}

			
			}
		break;
		
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_MOUSEMOVE:
		case WM_RBUTTONDBLCLK:
		case WM_LBUTTONDBLCLK:

		break;

		case WM_PAINT:

		break;

		case WM_KEYDOWN:

		break;
	}
return DefWindowProc(hwnd,message,wparam,lparam);
}
//----------------------------------------------------------------

int __stdcall WinMain(HINSTANCE,HINSTANCE,char *,int)
 //int main()
{
HWND hwnd=0;
int X,Y,W,H;
ULONG style=0;

WNDCLASS wc;
ZeroMemory(&wc,sizeof(WNDCLASS));

wc.style=CS_DBLCLKS;
wc.lpfnWndProc=(WNDPROC)&window_main_function_chvenia;
wc.lpszClassName="12";
wc.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(200,200,200));
wc.hIcon=(HICON)LoadImage(0,"c:\\1.ico",IMAGE_ICON,16,16,LR_LOADFROMFILE);

	if(RegisterClass(&wc)==0)
	{
	MessageBox(hwnd,"RegisterClass error",0,0);
	return 1;
	}


//mtavari fanjara:
style=WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN;
X=10;Y=30;W=700;H=500;
hwnd=CreateWindow(wc.lpszClassName,"Main",style,X,Y,W,H,0,0,0,0);

	
MSG msg;
int s=1;
	while(s!=0)
	{
	s=GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
}