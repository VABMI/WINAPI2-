/*--------------------------------------------------------
 * sndPlay.h - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#pragma once

typedef void (*LPMSGCALLBACK)(LPTSTR pszMsg);

BOOL sndPlayOpen(LPTSTR pszFilename);
BOOL sndPlayStart(void);
BOOL sndPlayPause(void);
BOOL sndPlayResume(void);
BOOL sndPlayStop(void);
BOOL sndPlayGetLength(DWORD *dwLength);
BOOL sndPlayGetPosition(DWORD *dwPos);
BOOL sndPlayClose(void);
void sndPlaySetMsgCallback(LPMSGCALLBACK lpCallback);
void sndPlaySetCallbackWnd(HWND hwndCallback);
void sndPlayGetLastError(LPTSTR pszErr);
DWORD sndPlayHandleError(DWORD dwErr);