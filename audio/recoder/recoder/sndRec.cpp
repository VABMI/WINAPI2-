/*--------------------------------------------------------
 * sndRec.c - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#include <windows.h>
#include "sndRec.h"
#include <vfw.h>

#define BUFFER_SIZE		256

static MCI_OPEN_PARMS parmOpen = { 0 };
static MCI_RECORD_PARMS parmRecord = { 0 };
static MCI_GENERIC_PARMS parmGeneric = { 0 };
static MCI_STATUS_PARMS parmStatus = { 0 };
static MCI_SAVE_PARMS parmSave = { 0 };
static DWORD wDeviceID = 0;
static volatile DWORD dwErr = 0;
static LPMSGCALLBACK lpCallback;
static HWND hWnd = 0;

BOOL sndRecOpen(void)
{
	parmOpen.wDeviceID = wDeviceID;
	parmOpen.lpstrDeviceType = TEXT("waveaudio");
	parmOpen.lpstrElementName = TEXT("");

	sndRecHandleError(mciSendCommand(wDeviceID, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)&parmOpen));

	wDeviceID = parmOpen.wDeviceID;

	return !dwErr;
}

BOOL sndRecRecord(void)
{
	sndRecHandleError(mciSendCommand(wDeviceID, MCI_RECORD, 0, (DWORD)&parmRecord));

	return !dwErr;
}

BOOL sndRecStop(void)
{
	sndRecHandleError(mciSendCommand(wDeviceID, MCI_STOP, MCI_WAIT, (DWORD)&parmGeneric));

	return !dwErr;
}

BOOL sndRecSave(LPTSTR pszFilename)
{
	parmSave.lpfilename = pszFilename;

	sndRecHandleError(mciSendCommand(wDeviceID, MCI_SAVE, MCI_WAIT | MCI_SAVE_FILE, (DWORD)&parmSave));

	return !dwErr;
}

BOOL sndRecGetLength(DWORD *dwLength)
{
	parmStatus.dwItem = MCI_STATUS_LENGTH;
	
	sndRecHandleError(mciSendCommand(wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)&parmStatus));

	*dwLength = parmStatus.dwReturn / 1000;

	return !dwErr;
}

BOOL sndRecClose(void)
{
	sndRecHandleError(mciSendCommand(wDeviceID, MCI_CLOSE, MCI_WAIT, (DWORD)&parmGeneric));

	return !dwErr;
}

void sndRecSetMsgCallback(LPMSGCALLBACK lpfnMsg) { lpCallback = lpfnMsg; }

void sndRecSetCallbackWnd(HWND hwndCallback) { hWnd = hwndCallback; }

void sndRecGetLastError(LPTSTR pszErr)
{
	TCHAR szBuffer[BUFFER_SIZE];

	mciGetErrorString(dwErr, szBuffer, BUFFER_SIZE);

	lstrcpy(pszErr, szBuffer);
}

DWORD sndRecHandleError(DWORD dwErrCode)
{
	TCHAR szErr[BUFFER_SIZE];

	dwErr = dwErrCode;

	if (!dwErr) return dwErr; // succeeded

	sndRecGetLastError(szErr);
	lpCallback(szErr);

	return dwErr;
}