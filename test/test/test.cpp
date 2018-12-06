
#include "stdafx.h"
HFONT hfont_global;
HWND globh,globh2,globh3;
		
bool b1=0;
//----------------------------------------------------------------
#include "struct.cpp"


inline DWORD WINAPI Thread_no_1( void* bufer1 ) 
{		

	
			struct PARAM *val=(struct PARAM *)bufer1;

			
			/*
			   int x3=((int*)bufer1)[2];

			   int x=((int*)bufer1)[0];
			   int x2=((int*)bufer1)[1];
			
			  char buf2[9999];
	
		   static   char *buf2=(char*)malloc(999999999);
		   memset((void*)buf2,0,sizeof(buf2));
		   char buffer[2000]={0};
		   */

			val->init();
			

		   for(int i=val->start;i<=val->end;i++)
						{
							for(int j=2;j<i;j++)
							{
								if(i%j==0)
									break;
								else if(i==j+1)
								{
									
									sprintf(val->buffer,"%i",i);
									strcat((char*)val->buffer2,val->buffer);
									strcat((char*)val->buffer2,"|\r\n");

								}
							}
						}

		   Sleep(val->pauza);
		   HWND hEdit=val->Hedit;
		   HWND fff=(HWND)hEdit;
						SendMessage((HWND)hEdit,EM_REPLACESEL,strlen((char*)val->buffer2),(LPARAM)val->buffer2);



						
	
					  val->clear();

	return 1; 
} 

/*
DWORD WINAPI Thread_no_2( void* bufer2 ) 
{		
					   int x3=((int*)bufer1)[2];

			   int x=((int*)bufer1)[0];
			   int x2=((int*)bufer1)[1];
			
			 // char buf2[9999];
	
		   char *buf2=(char*)malloc(999999999);
					  for(int i=x;i<=x2;i++)
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
									strcat(buf2,"|");
									strcat(buf2,buffer);
									strcat(buf2,"|\r\n");
									//strcat_s(buf2,"|_| ");
							
								
								}
							}
						}

					Sleep(x3);
						SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
				free(buf2);		
					


	return 1; 
} 

DWORD WINAPI Thread_no_3( void* bufer1 ) 
{		
			 			   int x3=((int*)bufer1)[2];

			   int x=((int*)bufer1)[0];
			   int x2=((int*)bufer1)[1];
			
			 // char buf2[9999];
	
		   char *buf2=(char*)malloc(999999999);
					  for(int i=x;i<=x2;i++)
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
									strcat(buf2,"|");
									strcat(buf2,buffer);
									strcat(buf2,"|\r\n");
									//strcat_s(buf2,"|_| ");
							
								
								}
							}
						}

					Sleep(x3);
						SendMessage(globh,EM_REPLACESEL,strlen(buf2),(LPARAM)buf2);


					  b1=1;
					//	MessageBox(0,"morcha","morcha",MB_TOPMOST);	
						
				free(buf2);		
					

	return 1; 
} 
*/


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
				globh=CreateWindow("edit","aa",WS_CHILD|WS_BORDER|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|ES_MULTILINE,0,50,100,r.bottom-55,hwnd,(HMENU)3,0,0);
				globh2=CreateWindow("edit","",WS_CHILD|WS_BORDER|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|ES_MULTILINE,120,50,100,r.bottom-55,hwnd,(HMENU)4,0,0);
				globh3=CreateWindow("edit","",WS_CHILD|WS_BORDER|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|ES_MULTILINE,240,50,100,r.bottom-55,hwnd,(HMENU)5,0,0);
				SendMessage(globh,EM_SETLIMITTEXT,100000,0);



			}
		break;
		
		case WM_COMMAND:
			{

				if(wparam==2)
				{	
					int k=0;
					int dd=2;
					SendMessage(globh,WM_SETTEXT,0,(LPARAM)"");
					// int* arr=(int*)malloc(10);
					//static int arr[100];
					char bufer[10000];
					SendMessage(GetDlgItem(hwnd,1),WM_GETTEXT,9999,(LPARAM)bufer);
					int value=atoi(bufer);
					int length=value/3;


					/*
							arr[0]=0;
							arr[1]=(value/3);
							arr[2]=0;   ///sleep 

							int* ptr=arr;
							*/
							static struct PARAM val1;//={1,k*length,(k+1)*length,"","",globh};

							val1.pauza=1;
							val1.start=k*length;
							val1.end=(k+1)*length;
							val1.Hedit=globh;
							HANDLE Thread1=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_1,(struct PARAM *)&val1,0,0);
					
							k++;


								static struct PARAM val2={1,k*length,(k+1)*length,"","",globh};
											val1.pauza=1;
							val1.start=k*length;
							val1.end=(k+1)*length;
							val1.Hedit=globh2;
								
							CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_1,(struct PARAM *)&val1,0,0);
							 k++;
								static struct PARAM val3={1,k*length,(k+1)*length,"","",globh};
										val1.pauza=1;
							val1.start=k*length;
							val1.end=(k+1)*length;
							val1.Hedit=globh3;
								
							CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_1,(struct PARAM *)&val1,0,0);

							/*Sleep(1);
							arr[0]+=(value/3);
							arr[1]+=(value/3);
							arr[2]=1000;  //sleep
					//	CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread_no_1,arr,0,0);
						
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