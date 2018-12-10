/*--------------------------------------------------------
 * sndPlay.c - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#include <windows.h>
#include "sndPlay.h"

#define BUFFER_SIZE		256

static MCI_OPEN_PARMS parmOpen = { 0 };
static MCI_PLAY_PARMS parmPlay = { 0 };
static MCI_GENERIC_PARMS parmGeneric = { 0 };
static MCI_STATUS_PARMS parmStatus = { 0 };
static DWORD wDeviceID = 0;
static DWORD dwErr = 0;
static LPMSGCALLBACK lpCallback;
static HWND hWnd = 0;


BOOL sndPlayOpen(LPTSTR pszFilename)
{
	parmOpen.wDeviceID = wDeviceID;
	parmOpen.lpstrDeviceType = TEXT("waveaudio");
	parmOpen.lpstrElementName = pszFilename;
	
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)&parmOpen));

	wDeviceID = parmOpen.wDeviceID;

	return !dwErr;
}

BOOL sndPlayStart(void)
{
	// notify window when finishes
	parmPlay.dwCallback = (DWORD)hWnd;

	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&parmPlay));

	return !dwErr;
}

BOOL sndPlayPause(void)
{
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_PAUSE, MCI_WAIT, (DWORD)&parmGeneric));

	return !dwErr;
}

BOOL sndPlayResume(void)
{
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_RESUME, MCI_WAIT, (DWORD)&parmGeneric));

	return !dwErr;
}

BOOL sndPlayStop(void)
{
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_STOP, MCI_WAIT, (DWORD)&parmGeneric));

	return !dwErr;
}

BOOL sndPlayGetLength(DWORD *dwLength)
{
	parmStatus.dwItem = MCI_STATUS_LENGTH;
	
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)&parmStatus));

	*dwLength = parmStatus.dwReturn / 1000;

	return !dwErr;
}

BOOL sndPlayGetPosition(DWORD *dwPos)
{
	parmStatus.dwItem = MCI_STATUS_POSITION;
	
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)&parmStatus));

	*dwPos = parmStatus.dwReturn / 1000;

	return !dwErr;
}

BOOL sndPlayClose(void)
{
	sndPlayHandleError(mciSendCommand(wDeviceID, MCI_CLOSE, MCI_WAIT, (DWORD)&parmGeneric));

	return !dwErr;
}

void sndPlaySetMsgCallback(LPMSGCALLBACK lpfnMsg) { lpCallback = lpfnMsg; }

void sndPlaySetCallbackWnd(HWND hwndCallback) { hWnd = hwndCallback; }

void sndPlayGetLastError(LPTSTR pszErr)
{
	TCHAR szBuffer[BUFFER_SIZE];

	mciGetErrorString(dwErr, szBuffer, BUFFER_SIZE);

	lstrcpy(pszErr, szBuffer);
}

DWORD sndPlayHandleError(DWORD dwErrCode)
{
	TCHAR szErr[BUFFER_SIZE];

	dwErr = dwErrCode;

	if (!dwErr) return dwErr; // succeeded

	sndPlayGetLastError(szErr);
	lpCallback(szErr);

	return dwErr;
}