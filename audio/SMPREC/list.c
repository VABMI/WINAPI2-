/*--------------------------------------------------------
 * list.c - (c) Mohammad Elsheimy, 2010
 * http://JustLikeAMagic.WordPress.com
  --------------------------------------------------------*/

#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include "list.h"



static TEXT_ITEM *pFirst, *pLast;

static int iCount = 0;


int lstAdd(TCHAR* pszItem)
{
	PTEXT_ITEM pItem;
	int iSize;

	iSize = (lstrlen(pszItem)) * sizeof pszItem[0];

	pItem = (PTEXT_ITEM)malloc(sizeof (TEXT_ITEM) + iSize);

	//memset(pItem, 0, sizeof (TEXT_ITEM) + sizeof pszItem - 1);

	if (!pItem)
		return -1;

	lstrcpy(pItem->pszItem, pszItem);
	/*memcpy(pItem->pszItem, pszItem, iSize);*/

	if (pFirst) {
		pLast->pNext = pItem;
		pLast = pLast->pNext;
	}
	else
		pFirst = pLast = pItem;

	pItem->pNext = 0;
	
	return iCount++;
}

PTEXT_ITEM lstGetItem(int idx)
{
	int i;
	PTEXT_ITEM pItem;

	pItem = pFirst;

	for (i = 0; (i <= idx) && (i < iCount); i++) {
		if (i == idx)
			return pItem;
		pItem = pItem->pNext;
	}

	return 0;
}

void lstRemove(int idx)
{
	int i;
	PTEXT_ITEM pItem, pPrev = 0;

	pItem = pFirst;

	for (i = 0; (i <= idx) && (i < iCount); i++) {
		if (i == idx) {
			if (!pPrev) // first itm
				pFirst = pItem->pNext;
			else
				pPrev->pNext = pItem->pNext;

			free(pItem);
			return;
		}
		pPrev = pItem;
		pItem = pItem->pNext;
	}
}

void lstClear(void)
{
	PTEXT_ITEM pItem;
	PTEXT_ITEM pNext;

	pItem = pNext = pFirst;

	while (pNext) {
		pNext = pItem->pNext;
		free(pItem);
		pItem = pNext;
	}
}