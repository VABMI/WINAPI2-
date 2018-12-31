#include "head.h"
#include "notify_msg.cpp"

HFONT hfont_global;
HWND h;
HBITMAP bvb;
HCURSOR hCursor;
HWND hwnd=0;
			
	HWND tree;
	HINSTANCE hInst,g_hInst; // main function handler
#define WIN32_LEAN_AND_MEAN // this will assume smaller exe

HTREEITEM Selected;

TV_INSERTSTRUCT tvinsert;  // struct to config out tree control

   TV_ITEM tvi; 
    TV_INSERTSTRUCT tvins; 


HTREEITEM Parent;           // Tree item handle
HTREEITEM Before;           // .......
HTREEITEM Root;             // .......

HTREEITEM hitTarget;
static HTREEITEM hPrev=(HTREEITEM)TVI_FIRST;

HIMAGELIST hImageList;      // Image list array hadle
HIMAGELIST hImageList2;

HBITMAP hBitMap;            // bitmap handler
bool flagSelected=false;

HWND hTree;
TVHITTESTINFO tvht; 
POINTS Pos;
bool Dragging;

HWND hEdit;






	//=====================================================//
HWND CreateATreeView(HWND hwndParent);
#include "CreateATreeView.cpp"
#include "AddItemToTree.cpp"

#include"create.cpp"



//======================== 22222222222222=====

/*
BOOL InitTreeViewImageLists(HWND hwndTV,HWND hw) 
{ 
    HIMAGELIST himl;  // handle to image list 
    HBITMAP hbmp;     // handle to bitmap 

    // Create the image list. 
    if (hImageList=ImageList_Create(16,16,ILC_COLOR16,2,10)) return 0; 

    // Add the open file, closed file, and document bitmaps. 
    hbmp = (HBITMAP)LoadImage(NULL,"C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\MARBLES.BMP", IMAGE_BITMAP,300,300, LR_LOADFROMFILE);
	bvb= (HBITMAP)LoadImage(NULL,"C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\MARBLES.BMP", IMAGE_BITMAP,300,300, LR_LOADFROMFILE);
	if(!hbmp)
	{

	//	MessageBox(hw,"No Items in TrtryuturyueeView","Error",MB_OK|MB_ICONINFORMATION);
	}
 int   g_nOpen = ImageList_Add(hImageList, bvb, (HBITMAP)NULL); 

    DeleteObject(hbmp); 


    // Fail if not all of the images were added. 
  //if (ImageList_GetImageCount(hImageList) )
//		MessageBox(hw,"No Items in TrtryuturyueeView","Error",MB_OK);

    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(hwndTV, hImageList, TVSIL_NORMAL); 

    return TRUE; 
}



*/
long __stdcall window_main_function_chvenia(HWND hwnd,unsigned int message, unsigned int wparam,long lparam)
{	
	HBITMAP bvb;
	 char path[100];
	HWND hwndtree=GetDlgItem(hwnd,123);
	HWND hstatic=GetDlgItem(hwnd,31);
	RECT r;
	
	switch(message)
	{
			case WM_INITDIALOG: 
		{

	

		}
		break;
		case WM_CREATE:
		create(hwnd, message,wparam,lparam);	
		//	 CreateWindow("msctls_trackbar32", "f", WS_VISIBLE | WS_CHILD, 500, 100, 200, 50, hwnd, (HMENU)251, NULL, NULL);


		
		/*
		
			    resourcesTreeView.hwnd = GetDlgItem(hwnd, ID_RESOURCES_TREE_VIEW);
    resourcesTreeView.insert.hParent = NULL;
    resourcesTreeView.insert.hInsertAfter = TVI_ROOT;
    resourcesTreeView.insert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
resourcesTreeView.insert.item.pszText = "Parent";
    resourcesTreeView.insert.item.iImage = 0;
    resourcesTreeView.insert.item.iSelectedImage = 1;
    resourcesTreeView.parent = (HTREEITEM)SendDlgItemMessage(hwnd, ID_RESOURCES_TREE_VIEW, TVM_INSERTITEM, 0, (LPARAM)&resourcesTreeView.insert);
    resourcesTreeView.root = resourcesTreeView.parent;
    resourcesTreeView.before = resourcesTreeView.parent;
    UpdateWindow(hwnd);

	*/


		break;
		
		case WM_COMMAND:
	switch(LOWORD(wparam))
	{

				

	}
//	MessageBox(hwnd,"No Items in TrtryuturyueeView","Error",MB_OK|MB_ICONINFORMATION);
		break;
		
		case WM_LBUTTONDBLCLK:
	
		break;

		case WM_PAINT:

		
		break;

		case WM_KEYDOWN:
				MessageBox(hwnd,"main fanjara","main fanjara",0);
		break;
		case WM_NOTIFY:

			#include "WM_NOTY_TREE.cpp"

			break;
		
	
			//if(message== WM_NOTIFY||message== WM_VSCROLL||message== WM_HSCROLL){	MessageBox(hwnd,"main fanjara","main fanjara",0);//notify_msg(hwnd, message, wparam, lparam);			}




}
return DefWindowProc(hwnd,message,wparam,lparam);
}

void main()
{
	
int X,Y,W,H;
ULONG style=0;
WNDCLASS wc;
ZeroMemory(&wc,sizeof(WNDCLASS));
wc.style=CS_DBLCLKS|SW_MAXIMIZE;
wc.lpfnWndProc=(WNDPROC)&window_main_function_chvenia;
wc.lpszClassName="12";
wc.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(200,200,200));
wc.hIcon=(HICON)LoadImage(0,"c:\\1.ico",IMAGE_ICON,16,16,LR_LOADFROMFILE);




	if(RegisterClass(&wc)==0)
	{
	MessageBox(hwnd,"RegisterClass error",0,0);
	return;
	}
//mtavari fanjara:
style=WS_VISIBLE|WS_OVERLAPPED|WS_CLIPCHILDREN;
X=10;Y=30;W=700;H=500;
hwnd=CreateWindow(wc.lpszClassName,"Main",style|WS_OVERLAPPEDWINDOW,X,Y,W,H,0,0,0,0);

 HWND buton;//=CreateWindow("button","Main",WS_VISIBLE|WS_CHILD|BS_BITMAP,300,Y,80,80,hwnd,(HMENU)0,0,0);

 bvb= (HBITMAP)LoadImage(NULL,"C:\\Users\\vaxoa\\OneDrive\\Desktop\\icon\\MARBLES.BMP", IMAGE_BITMAP,300,300, LR_LOADFROMFILE);

		//	 SendMessage(bvb, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

//SendMessage(buton, (UINT)BM_SETIMAGE,   (WPARAM)IMAGE_BITMAP, (LPARAM)bvb);






HCURSOR Cur = LoadCursorFromFile("C:\\Users\\vaxoa\\OneDrive\\Documents\\GitHub\\WINAPI\\icon\\Debug\\too994.ani");
//SendMessage(buton, WM_SETCURSOR, 0, (LPARAM) Cur);
//SetClassLong (buton, GCL_HCURSOR, (LONG) Cur);

	CreateWindow("Static","asdasda",WS_VISIBLE|WS_BORDER|WS_CHILD|SS_BITMAP,202,0,300,300,hwnd,(HMENU)31,0,0);




MSG msg;
int s=1;
	while(s!=0)
	{
	s=GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
}



