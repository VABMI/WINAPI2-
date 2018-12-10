/*--------------------------------------------------------
 * sndRec.h - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#pragma once

typedef void (*LPMSGCALLBACK)(LPTSTR pszMsg);

BOOL sndRecOpen(void);
BOOL sndRecRecord(void);
BOOL sndRecStop(void);
BOOL sndRecSave(LPTSTR pszFilename);
BOOL sndRecGetLength(DWORD *dwLength);
BOOL sndRecClose(void);
void sndRecSetMsgCallback(LPMSGCALLBACK lpCallback);
void sndRecSetCallbackWnd(HWND hwndCallback);
void sndRecGetLastError(LPTSTR pszErr);
DWORD sndRecHandleError(DWORD dwErr);