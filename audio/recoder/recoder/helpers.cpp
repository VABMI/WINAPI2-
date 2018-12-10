/*--------------------------------------------------------
 * helpers.c - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#include <windows.h>
#include <time.h>

void GetAppPath(LPTSTR pszPath, UINT cchText);

void GetAppPath(LPTSTR pszPath, UINT cchText)
{
	TCHAR szBuffer[MAX_PATH + 1];
	int i;

	GetModuleFileName(GetModuleHandle(0), szBuffer, MAX_PATH + 1);

	// strip file name
	for (i = lstrlen(szBuffer) - 1; i > 0; i--) {
		if ('\\' == szBuffer[i]) {
			szBuffer[i + 1] = '\0';
			break;
		}
	}

	lstrcpyn(pszPath, szBuffer, cchText);
}

void GetRecordingsPath(LPTSTR pszPath, UINT cchText)
{
	TCHAR szBuffer[MAX_PATH + 1];

	GetAppPath(szBuffer, MAX_PATH + 1);
	
	lstrcat(szBuffer, TEXT("Recordings\\"));

	lstrcpyn(pszPath, szBuffer, cchText);

	if (!SetCurrentDirectory(szBuffer))
		CreateDirectory(szBuffer, 0);
}

void GetNewRecording(LPTSTR pszTime, LPTSTR pszPath, UINT cchText)
{
	TCHAR szBuffer[MAX_PATH + 1];
	TCHAR szFilename[28];
	TCHAR szTimeBuffer[7];
	SYSTEMTIME systime;
	int i, j;

	j = 0;
	for (i = 0; i < lstrlen(pszTime); i++)
		if (isdigit(pszTime[i]))
			szTimeBuffer[j++] = pszTime[i];
	szTimeBuffer[j] = '\0';

	GetRecordingsPath(szBuffer, MAX_PATH + 1);

	i = lstrlen(szBuffer);

	GetLocalTime(&systime);

	//wsprintf(szFilename, TEXT("%d02%d02%d04-%d02%d02%d02-%s.wav"), 
	wsprintf(szFilename, TEXT("%02d%02d%04d-%02d%02d%02d-%s.wav"), 
		systime.wMonth, systime.wDay, systime.wYear,
		systime.wHour, systime.wMinute, systime.wSecond, 
		szTimeBuffer);

	lstrcat(szBuffer, szFilename);

	//lstrcpy(pszPath, szBuffer);
	lstrcpyn(pszPath, szBuffer, cchText);
}

void TimeToStr(UINT uTime, LPTSTR pszTime, UINT cchText)
{
	TCHAR szBuffer[9];

	wsprintf(szBuffer, TEXT("%02d:"), uTime / (60 * 60));
	uTime = uTime % (60 * 60);

	wsprintf(szBuffer + 3, TEXT("%02d:"), uTime / (60));
	uTime = uTime % (60);

	wsprintf(szBuffer + 6, TEXT("%02d"), uTime);

	lstrcpyn(pszTime, szBuffer, cchText);
}

void LoadRecordings(void (*lpCallback) (LPTSTR))
{
	TCHAR szPath[MAX_PATH + 1];
	HANDLE hFind;
	WIN32_FIND_DATA find;

	GetRecordingsPath(szPath, sizeof szPath / sizeof szPath[0]);

	hFind = FindFirstFile(TEXT("*.wav"), &find);

	if (INVALID_HANDLE_VALUE == hFind)
		return;
	
	do {
		// strip extension
		find.cFileName[lstrlen(find.cFileName) - 4] = '\0';
		lpCallback(find.cFileName);
	} while (FindNextFile(hFind, &find));

	FindClose(hFind);
}

void GetRecordPath(LPTSTR szFilename, UINT cchText)
{
	TCHAR szPath[MAX_PATH + 1];

	GetRecordingsPath(szPath, sizeof szPath / sizeof szPath[0]);

	lstrcat(szPath, szFilename);

	lstrcat(szPath, TEXT(".wav"));

	lstrcpyn(szFilename, szPath, cchText);
}