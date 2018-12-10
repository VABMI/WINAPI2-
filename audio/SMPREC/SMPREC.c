/*--------------------------------------------------------
 * SMPREC.c - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <commdlg.h>
#include "commctrl.h"
#include "sndRec.h"
#include "sndPlay.h"
#include "list.h"
#include "resource.h"

#define ID_TIMER	1

static TCHAR szAppTitle[] = TEXT("Geming SMPREC");
static HINSTANCE hInst;
static BOOL bRecording, bPlaying, bPaused;
static HWND hDlg;

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SetBtnBitmaps(void);
void InitListView(HWND hWnd);
void AddRecording(LPTSTR strName);
void EnableDlgItems(void);
void ErrCallback(LPTSTR pszError);
void TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void StartTimer(void), StopTimer(void);
void GetSelectedPath(LPTSTR pszPath, UINT cchText, INT* pIdx);

extern void GetAppPath(LPTSTR pszPath, UINT cchText);
extern void GetNewRecording(LPTSTR strTime, LPTSTR pszPath, UINT cchText);
extern void TimeToStr(UINT uTime, LPTSTR pszTime, UINT cchText);
extern void LoadRecordings(void (*lpCallback) (LPTSTR));
extern void GetRecordPath(LPTSTR szFilename, UINT cchText);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLG), 0, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndRec;
	TCHAR szPath[MAX_PATH + 1];

	switch (uMsg)
	{
	case WM_INITDIALOG:

		hDlg = hWnd;
		hwndRec = GetDlgItem(hWnd, IDC_RECORDINGS);

		SetWindowText(hWnd, szAppTitle);
		SetBtnBitmaps();
		InitListView(hwndRec);
		LoadRecordings(AddRecording);
		EnableDlgItems();

		sndRecSetCallbackWnd(hWnd); // No need, we haven't applied MCI_NOTIFY in sndRec
		sndRecSetMsgCallback((LPMSGCALLBACK)ErrCallback);
		sndPlaySetCallbackWnd(hWnd); // required
		sndPlaySetMsgCallback((LPMSGCALLBACK)ErrCallback);

		return TRUE;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_RECORDINGS:
			switch (((LPNMHDR)lParam)->code)
			{
			case LVN_ITEMCHANGED:
				EnableDlgItems();
				break;
			}
			break;
		}

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RECORD:

			if (!bRecording) {
				if (!sndRecOpen())
					return TRUE;

				if (!sndRecRecord())
					return TRUE;

				bRecording = TRUE;
				EnableDlgItems();
				
				StartTimer();
			}
			else {
				TCHAR szText[9];

				if (!sndRecStop())
					return TRUE;

				bRecording = FALSE;
				EnableDlgItems();

				StopTimer();

				GetWindowText(GetDlgItem(hWnd, IDC_LENGTH), szText, sizeof szText / sizeof szText[0]);
				GetNewRecording(szText, szPath, sizeof szPath / sizeof szPath[0]);
				sndRecSave(szPath);

				sndRecClose();
			}

			return TRUE;

		case IDC_PLAY:

			if (!bPlaying) {	// Play
				GetSelectedPath(szPath, sizeof szPath / sizeof szPath[0], 0);

				if (!sndPlayOpen(szPath))
					return TRUE;

				if (!sndPlayStart())
					return TRUE;

				bPlaying = TRUE;
				EnableDlgItems();
				
				StartTimer();
			}
			else if (bPlaying && bPaused)	{ // Resume
				if (!sndPlayResume())
					return TRUE;

				bPaused = FALSE;
				StartTimer();

				EnableDlgItems();
			}
			else {								// Pause
				if (!sndPlayPause())
					return TRUE;

				bPaused = TRUE;
				StopTimer();

				EnableDlgItems();
			}

			return TRUE;

		case IDC_STOP:
			if (!sndPlayStop())
				return TRUE;

			bPlaying = FALSE;
			StopTimer();

			EnableDlgItems();

			sndPlayClose();

			return TRUE;

		case IDC_DELETE:
			{
				int idx;

				GetSelectedPath(szPath, sizeof szPath / sizeof szPath[0], &idx);

				if (IDYES != MessageBox(hWnd, TEXT("Are you sure you want to delete this file?"), szAppTitle, MB_ICONQUESTION | MB_YESNO))
					return TRUE;

				// TODO: Complete
				if (DeleteFile(szPath)) {
					lstRemove(idx);
					ListView_DeleteItem(GetDlgItem(hWnd, IDC_RECORDINGS), idx);
				}
				else {
					TCHAR szBuffer[256];
					DWORD dwErr;

					dwErr = GetLastError();
					lstrcpy(szBuffer, TEXT("Cannot delete file. "));
					FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, (LPCVOID)FORMAT_MESSAGE_FROM_HMODULE, dwErr, 0, 
						szBuffer + lstrlen(szBuffer), sizeof szBuffer / sizeof szBuffer[0] - lstrlen(szBuffer), 0);

					ErrCallback(szBuffer);
				}
				return TRUE;
			}

		case IDC_SAVE:
			{
				int idx;
				TCHAR szFilename[MAX_PATH + 1] = TEXT("");
				OPENFILENAME ofn = { sizeof ofn, hWnd };

				ofn.lpstrFilter = TEXT("Audio (Waveform) Files (*.wav)\0*.wav\0\0");
				ofn.nFilterIndex = 1;
				ofn.lpstrFile = szFilename;
				ofn.nMaxFile = sizeof szFilename / sizeof szFilename[0];
				ofn.lpstrTitle = szAppTitle;
				ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
				ofn.lpstrDefExt = TEXT("wav");

				GetSelectedPath(szPath, sizeof szPath / sizeof szPath[0], &idx);

				if (GetSaveFileName(&ofn)) {
					if (!CopyFile(szPath, szFilename, FALSE)) {
						TCHAR szBuffer[256];
						DWORD dwErr;
						
						dwErr = GetLastError();
						lstrcpy(szBuffer, TEXT("Cannot save file. "));
						FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, (LPCVOID)FORMAT_MESSAGE_FROM_HMODULE, dwErr, 0, 
							szBuffer + lstrlen(szBuffer), sizeof szBuffer / sizeof szBuffer[0] - lstrlen(szBuffer), 0);

						ErrCallback(szBuffer);
					}
				}
				else
					ErrCallback(TEXT("Cannot save file."));

				return TRUE;
			}

		}

		break;

	case MM_MCINOTIFY:

		switch (wParam)
		{
		case MCI_NOTIFY_SUCCESSFUL:
			SendMessage(hWnd, WM_COMMAND, IDC_STOP, 0);
			break;
		}

		break;

	case WM_DESTROY:
		lstClear();
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return TRUE;
	}

	return FALSE;
}

void SetBtnBitmaps(void)
{
	SendMessage(GetDlgItem(hDlg, IDC_PLAY), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLAY)));
	SendMessage(GetDlgItem(hDlg, IDC_STOP), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_STOP)));
	SendMessage(GetDlgItem(hDlg, IDC_SAVE), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_SAVE)));
	SendMessage(GetDlgItem(hDlg, IDC_DELETE), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DELETE)));
}

void InitListView(HWND hWnd)
{
	LV_COLUMN col = { 0 };
	col.mask = LVCF_TEXT | LVCF_WIDTH;
	col.pszText = TEXT("Date");
	col.cx = 175;
	
	ListView_InsertColumn(hWnd, 0, &col);

	col.mask |= LVCF_FMT;
	col.fmt = LVCFMT_RIGHT;
	col.pszText = TEXT("Length");
	col.cx = 125;
	ListView_InsertColumn(hWnd, 1, &col);
}

void AddRecording(LPTSTR strName)
{
	static int idx = 0;
	TCHAR szItem[30];
	struct tm time = { 0 };
	LVITEM itm = { 0 };
	TCHAR* pszLocale;

	lstAdd(strName);

	_stscanf_s(strName, TEXT("%02d%02d%04d-%02d%02d%02d"), 
		&time.tm_mon, &time.tm_mday, &time.tm_year,
		&time.tm_hour, &time.tm_min, &time.tm_sec);

	time.tm_mon -= 1;
	time.tm_year -= 1900;
	
	pszLocale = _tsetlocale(LC_TIME, TEXT(""));

	itm.mask = LVIF_TEXT;
	
	_tcsftime(szItem, sizeof szItem / sizeof szItem[0], TEXT("%c"), &time);
	itm.pszText = szItem;
	itm.iItem = idx++;
	itm.cchTextMax = lstrlen(szItem);
	itm.iItem = ListView_InsertItem(GetDlgItem(hDlg, IDC_RECORDINGS), &itm);
	
	itm.iSubItem = 1;
	strName += 16;
	itm.pszText = strName;
	itm.cchTextMax = lstrlen(strName);
	ListView_SetItem(GetDlgItem(hDlg, IDC_RECORDINGS), &itm);
	
	_tsetlocale(LC_TIME, pszLocale);
}

void EnableDlgItems(void)
{
	HWND hWnd;
	HGDIOBJ hObj;
	BOOL bSelected;

	//SendMessage(GetDlgItem(hWnd, IDC_RECORDINGS), LVM_GETSELECTEDCOUNT,  0, 0)
	bSelected = ListView_GetSelectedCount(GetDlgItem(hDlg, IDC_RECORDINGS)) > 0;

	hWnd = GetDlgItem(hDlg, IDC_RECORD);
	SetWindowText(hWnd, bRecording ? TEXT("&Stop Recording") : TEXT("&Start Recording"));
	EnableWindow(hWnd, !bPlaying);

	EnableWindow(GetDlgItem(hWnd, IDC_RECORDINGS), !bPlaying && !bRecording);

	hWnd = GetDlgItem(hDlg, IDC_PLAY);
	hObj = (HGDIOBJ) SendMessage(hWnd, BM_SETIMAGE, IMAGE_BITMAP,
		(LPARAM) ((bPaused || (!bPlaying && !bPaused)) ? LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLAY)) : LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PAUSE))));
	if (hObj != 0) DeleteObject(hObj);
	EnableWindow(hWnd, !bRecording && bSelected);

	EnableWindow(GetDlgItem(hDlg, IDC_STOP), bPlaying);
	
	EnableWindow(GetDlgItem(hDlg, IDC_SAVE), !bPlaying && !bRecording && bSelected);
	EnableWindow(GetDlgItem(hDlg, IDC_DELETE), !bPlaying && !bRecording && bSelected);
}

void ErrCallback(LPTSTR pszError)
{
	MessageBox(hDlg, pszError, szAppTitle, MB_ICONERROR);
}

void TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	UINT uLength = 0;
	TCHAR szBuffer[21];	// max: 00:00:00 of 00:00:00


	if (bRecording) {
		sndRecGetLength(&uLength);
		TimeToStr(uLength, szBuffer, sizeof szBuffer / sizeof szBuffer[0]);
		SetWindowText(GetDlgItem(hDlg, IDC_LENGTH), szBuffer);
	}
	else {
		sndPlayGetPosition(&uLength);
		TimeToStr(uLength, szBuffer, sizeof szBuffer / sizeof szBuffer[0]);

		lstrcat(szBuffer, TEXT(" of "));
		
		uLength = 0;
		sndPlayGetLength(&uLength);
		TimeToStr(uLength, szBuffer + 12, sizeof szBuffer / sizeof szBuffer[0] - 12);

		SetWindowText(GetDlgItem(hDlg, IDC_POSITION), szBuffer);
	}
}

void StartTimer(void) { SetTimer(hDlg, ID_TIMER, 750, (TIMERPROC)TimerProc); }

void StopTimer(void) { KillTimer(hDlg, ID_TIMER); }

void GetSelectedPath(LPTSTR pszPath, UINT cchText, INT* pIdx)
{
	TCHAR szFilename[MAX_PATH + 1];
	HWND hList;
	int idx;

	hList = GetDlgItem(hDlg, IDC_RECORDINGS);
	idx = ListView_GetSelectionMark (GetDlgItem(hDlg, IDC_RECORDINGS));
	lstrcpy(szFilename, lstGetItem(idx)->pszItem);
	GetRecordPath(szFilename, sizeof szFilename / sizeof szFilename[0]);

	if (pIdx)
		*pIdx = idx;
	lstrcpyn(pszPath, szFilename, cchText);
}