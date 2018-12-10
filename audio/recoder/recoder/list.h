/*--------------------------------------------------------
 * list.h - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#pragma once

#include <windows.h>
#include <stdlib.h>
#include <tchar.h>

typedef struct tagTEXT_ITEM {
	struct tagTEXT_ITEM* pNext;
	TCHAR pszItem[1];
} TEXT_ITEM, *PTEXT_ITEM;

int lstAdd(TCHAR* pszItem);
PTEXT_ITEM lstGetItem(int idx);
void lstRemove(int idx);
void lstClear(void);