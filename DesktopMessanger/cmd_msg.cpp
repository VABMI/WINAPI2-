
HFONT select_font(HWND hwnd)
{
HDC hdc;                  // display device context of owner window
CHOOSEFONT cf;            // common dialog box structure
static LOGFONT lf;        // logical font structure
static DWORD rgbCurrent;  // current text color
HFONT hfont, hfontPrev;
DWORD rgbPrev;

// Initialize CHOOSEFONT
ZeroMemory(&cf, sizeof(cf));
cf.lStructSize = sizeof (cf);
cf.hwndOwner = hwnd;
cf.lpLogFont = &lf;
cf.rgbColors = rgbCurrent;
cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

	if (ChooseFont(&cf)==TRUE)
	{
	hfont = CreateFontIndirect(cf.lpLogFont);
	//hfontPrev = SelectObject(hdc, hfont);
	rgbCurrent= cf.rgbColors;
	rgbPrev = SetTextColor(hdc, rgbCurrent);
	}
return hfont;
}





long __stdcall on_cmd(HWND hwnd,unsigned int message
					,unsigned int wparam,long lparam)

{
	
int ctrl_id = (unsigned short)wparam;
	if(ctrl_id==200)
	{
	hfont_global=select_font(hwnd);
	//SendMessage(hwnd,WM_SETFONT,(UINT)hfont,0);
	}

	else if(ctrl_id==10)
	{
		static bool ShowHide;
		RECT r;
		GetClientRect(GetDesktopWindow(),&r);
		int X,Y,W,H;

	X=r.right-350;Y=0;W=350;H=r.bottom-40;
		if(ShowHide==0)
	{
			HCURSOR hCursor=LoadCursorFromFile("F:\\WINAPI2-\\DesktopMessanger\\Debug\\5.ico");
			SetCursor(hCursor);
			SetClassLong(g_hwndButton, -12, (DWORD)hCursor);
		ShowHide=1;
		SetWindowPos(hwnd,0,r.right-10,0,W,H,0);
	}
	else
	{


			HCURSOR hCursor=LoadCursorFromFile("F:\\WINAPI2-\\DesktopMessanger\\Debug\\4.ico");
	SetCursor(hCursor);
	SetClassLong(g_hwndButton, -12, (DWORD)hCursor);


		SetWindowPos(hwnd,0,X,Y,W,H,0);
		ShowHide=0;
	}
		
	}
return 0;
}