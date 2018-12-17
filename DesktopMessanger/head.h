#include <iostream>
#include <stdlib.h>
#include <stdio.h>
/*
#include <sys/types.h>
#include <sys/socket.h>
//#include "netdb.h"
*/
//#include <netinet/in.h> 

#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <fstream>
#include <winver.h>
#include <stdio.h>
#include "commctrl.h"
#pragma comment (lib,"WS2_32.lib")	

using namespace std;

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 



#include "CreateGradientBrush.cpp"


HBITMAP s_hBitmap = NULL;
LPCWSTR s_szFile = L"11.bmp";
#define CLOSE 1313
#define ACTIVEBOW 1314
HWND HwndParent;
#define SAVEBUTTON 1315