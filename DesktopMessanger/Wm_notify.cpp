case WM_NOTIFY:
        {
#include"HBRUSHES.cpp"

            LPNMHDR some_item = (LPNMHDR)lparam;
////////////////////////////////////////////////////////////////////  EXIT BUTTONNNNN  //////////////////////////////////////////////////

            if (some_item->idFrom == CLOSE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

                if (item->uItemState & CDIS_SELECTED)
                {
                    //Select our color when the button is selected
						if (selectbrush == NULL)
                        selectbrush = CreateGradientBrush(RGB(180, 0, 0), RGB(255, 180, 0), item);

                    //Create pen for button border
                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    //Select our brush into hDC
                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, selectbrush);

                    //If you want rounded button, then use this, otherwise use FillRect().
                    RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0);

                    //Clean up
                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);
                    return CDRF_DODEFAULT;

                }
                else
                {
                    if (item->uItemState & CDIS_HOT) //Our mouse is over the button
                    {
                        //Select our color when the mouse hovers our button
                        if (hotbrush == NULL)
                            hotbrush = CreateGradientBrush(RGB(255, 230, 51), RGB(245, 128, 0), item);

                        HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                        HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                        HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

                        RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0); //// hoveri exit buttonis ??

                        SelectObject(item->hdc, old_pen);
                        SelectObject(item->hdc, old_brush);
                        DeleteObject(pen);

                        return CDRF_DODEFAULT;
                    }

                    //Select our color when our button is doing nothing
                    if (defaultbrush == NULL)
                        defaultbrush = CreateGradientBrush(RGB(255, 180, 89), RGB(180, 0, 0), item);

                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

                   RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0); /// exit button

                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);

                    return CDRF_DODEFAULT;
                }
    }
  	else   if (some_item->idFrom ==   ACTIVEBOW  && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

                if (item->uItemState & CDIS_SELECTED)
                {
                    //Select our color when the button is selected
						if (selectbrush == NULL)
                        selectbrush = CreateGradientBrush(RGB(180, 0, 0), RGB(255, 255, 225), item);

                    //Create pen for button border
                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    //Select our brush into hDC
                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, selectbrush);

                    //If you want rounded button, then use this, otherwise use FillRect().
                    RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0);

                    //Clean up
                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);
                    return CDRF_DODEFAULT;

                }
                else
                {
                    if (item->uItemState & CDIS_HOT) //Our mouse is over the button
                    {
                        //Select our color when the mouse hovers our button
                        if (hotbrush == NULL)
                            hotbrush = CreateGradientBrush(RGB(255, 230, 51), RGB(245, 128, 0), item);

                        HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(225, 0, 225));

                        HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                        HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

                        RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0); //// hoveri exit buttonis ??

                        SelectObject(item->hdc, old_pen);
                        SelectObject(item->hdc, old_brush);
                        DeleteObject(pen);

                        return CDRF_DODEFAULT;
                    }

                    //Select our color when our button is doing nothing
                    if (defaultbrush == NULL)
                        defaultbrush = CreateGradientBrush(RGB(255, 180, 89), RGB(180, 0, 0), item);

                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

                   RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 0, 0); /// exit button

                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);

                    return CDRF_DODEFAULT;
                }
    }

            return CDRF_DODEFAULT;

		}  break;