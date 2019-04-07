
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "base.h"

//##########################################################################

BOOL IsEdit(HWND hWnd)
{
	if (hWnd == NULL)
		return FALSE;

	TCHAR szClassName[6];
	return ::GetClassNameA(hWnd, szClassName, 6) &&
		stricmp(szClassName, "Edit") == 0;
}

bool SetUserData4Menu(HMENU hMenu, LONG lUserData)
{
	MENUINFO oMI;
	ZeroMemory(&oMI, sizeof(MENUINFO));
	oMI.cbSize = sizeof(MENUINFO);
	oMI.fMask = MIM_MENUDATA;// | MIM_STYLE | MIM_MAXHEIGHT | MIM_BACKGROUND | MIM_HELPID | MIM_APPLYTOSUBMENUS;
	
	GetMenuInfo(hMenu, &oMI);

	oMI.dwMenuData = (DWORD)lUserData;

	return SetMenuInfo(hMenu, &oMI);
}

LONG GetUserData4Menu(HMENU hMenu)
{
	MENUINFO oMI;
	ZeroMemory(&oMI, sizeof(MENUINFO));
	oMI.cbSize = sizeof(MENUINFO);
	oMI.fMask = MIM_MENUDATA;
	
	GetMenuInfo(hMenu, &oMI);
	
	return oMI.dwMenuData;
}


LRESULT CALLBACK WndProcAllDefault(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CComponent *pComponent = dynamic_cast<CComponent*>((IComponent*)GetWindowLong(hWnd, GWL_USERDATA));

	if (pComponent)
	{
		if (uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_MBUTTONDOWN)
		{
			pComponent->setFocus();
		}

		if (uMsg == WM_KEYDOWN)
		{
			if (wParam == 'A' && (GetKeyState(VK_CONTROL) & 0x80))
			{
				// User pressed Ctrl-A.  Let's select-all
				if (IsEdit(hWnd))
				{
					SendMessage(hWnd, EM_SETSEL, 0, -1);
					return(1);
				}
			}
		}

		LONG lRetSys = 0;
		if (pComponent->procHandlerSys(hWnd, uMsg, wParam, lParam, &lRetSys))
			return lRetSys;

		LONG lRetUser = 0;
		if (pComponent->proc(hWnd, uMsg, wParam, lParam, &lRetUser) == 1)
			return lRetUser;

		if (pComponent->getPrevWndProc())
			return CallWindowProc((WNDPROC)(pComponent->getPrevWndProc()), hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//##########################################################################

bool SetText(IControl *pControl, const char* text)
{
	if (!SetWindowText((HWND)(pControl->getNativeHandle()), text))
		return false;
	else
		return true;
}

void GetText(IControl *pControl, char* buf, int count)
{
	GetWindowText((HWND)(pControl->getNativeHandle()), buf, count);
}

int GetTextLen(IControl *pControl)
{
	return GetWindowTextLength((HWND)(pControl->getNativeHandle()));
}

//##########################################################################

BOOL CALLBACK EnumChildProcUpdateSize(HWND hwnd, LPARAM lParam)
{
	IComponent *Component = (IComponent *)GetWindowLong(hwnd, GWL_USERDATA);
	if (Component)
		Component->updateSize();

	return TRUE;
}

BOOL CALLBACK EnumChildProcUpdateRect(HWND hwnd, LPARAM lParam)
{
	IComponent *Component = (IComponent *)GetWindowLong(hwnd, GWL_USERDATA);
	if (Component)
		Component->updateRect();

	return TRUE;
}

BOOL CALLBACK EnumChildProcMouseMove(HWND hwnd, LPARAM lParam)
{
	IComponent *pComponent = (IComponent *)GetWindowLong(hwnd, GWL_USERDATA);

	if (pComponent)
	{
		POINT p;
		GetCursorPos(&p);
		RECT rect;
		GetWindowRect(hwnd, &rect);

		if (pComponent && !((p.x >= rect.left && p.x <= rect.right) && (p.y >= rect.top && p.y <= rect.bottom)))
		{
			SendMessage((HWND)(pComponent->getNativeHandle()), WM_NCMOUSEMOVE, lParam, 0);
		}
	}

	return TRUE;
}

//##########################################################################

void StdHandlerInitMsg(IComponent *pComponent)
{
	CComponent *pComponent2 = dynamic_cast<CComponent*>(pComponent);

	pComponent2->addHandlerSys(StdHandlerCtlColorChange, WM_CTLCOLORSTATIC, true);
	pComponent2->addHandlerSys(StdHandlerCtlColorChange, WM_CTLCOLOREDIT, true);
	pComponent2->addHandlerSys(StdHandlerCtlColorChange, WM_CTLCOLORBTN, true);
	pComponent2->addHandlerSys(StdHandlerCtlColorChange, WM_CTLCOLORLISTBOX, true);

	pComponent2->addHandlerSys(StdHandlerSizeChange, WM_SIZE, true);
	pComponent2->addHandlerSys(StdHandlerSizingChange, WM_SIZING, true);
	pComponent2->addHandlerSys(StdHandlerWinDestroy, WM_DESTROY, true);

	pComponent2->addHandlerSys(StdHandlerMoveChange, WM_MOVE, true);
	pComponent2->addHandlerSys(StdHandlerMouseMoveChange, WM_MOUSEMOVE, true);
	//pComponent->addHandlerSys(StdHandlerMaximuzeWinChange, WM_SYSCOMMAND, SC_MAXIMIZE, true, 0, 0, true);
	pComponent2->addHandlerSys(StdHandlerSetCursorChange, WM_SETCURSOR, true);
}

LRESULT StdHandlerCtlColorChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ITextual *pTextual = dynamic_cast<ITextual*>((IComponent *)GetWindowLong((HWND)lParam, GWL_USERDATA));

	GUI_TYPE_ELEMENT type = pTextual->getElementType();

	if (pTextual)
	{
		if (pTextual->getTransparentTextBk())
			SetBkMode((HDC)wParam, TRANSPARENT);
		else
			SetBkColor((HDC)wParam, pTextual->getColorTextBk());
		SetTextColor((HDC)wParam, pTextual->getColorText());
		return (LONG)pTextual->getBrush();
	}
	return((LRESULT)INVALID_HANDLE_VALUE);
}

//**************************************************************************

BOOL CALLBACK EnumChildProcSendMouseMsg2Children(HWND hwnd, LPARAM lParam)
{
	CComponent *pComponent = dynamic_cast<CComponent*>((IComponent*)GetWindowLong(hwnd, GWL_USERDATA));
	CMsg2EnumChild *pMsg = ((CMsg2EnumChild*)lParam);

	if (pComponent && pMsg)
	{
		RECT oRect;
		pComponent->getWinRect(&oRect);

		POINT oPoint;
		GetCursorPos(&oPoint);

		if (
			oPoint.x >= oRect.left && oPoint.x <= oRect.right &&
			oPoint.y >= oRect.top && oPoint.y <= oRect.bottom
		)
		{
			if (pComponent->proc(hwnd, pMsg->m_uMsg, pMsg->m_wParam, pMsg->m_lParam, 0) != 0)
			{
				pMsg->m_isProc = true;
				return FALSE;
			}
		}
	}

	return TRUE;
}

bool SendMouseMsg2Children(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMsg2EnumChild oMsg;
	oMsg.m_uMsg = msg;
	oMsg.m_wParam = wParam;
	oMsg.m_lParam = lParam;
	oMsg.m_isProc = false;

	EnumChildWindows(hwnd, (WNDENUMPROC)&EnumChildProcSendMouseMsg2Children, LONG(&oMsg));
	return oMsg.m_isProc;
}

//**************************************************************************

LRESULT StdHandlerSizeChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EnumChildWindows(hwnd, (WNDENUMPROC)&EnumChildProcUpdateSize, lParam);
	return TRUE;
}

LRESULT StdHandlerSizingChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IComponent *pComponent = (IComponent *)GetWindowLong(hwnd, GWL_USERDATA);

	if (!pComponent)
		return TRUE;

	RECT rc;
	GetWindowRect(hwnd, &rc);
	POINT p;
	GetCursorPos(&p);

	RECT lpRect = *((LPRECT)lParam);

	if (pComponent)
	{
		if (!pComponent->getStretchSide(SIDE_TOP))
			lpRect.top = rc.top;

		if (!pComponent->getStretchSide(SIDE_LEFT))
			lpRect.left = rc.left;

		if (!pComponent->getStretchSide(SIDE_RIGHT))
			lpRect.right = rc.right;

		if (!pComponent->getStretchSide(SIDE_BOTTOM))
			lpRect.bottom = rc.bottom;

		if (pComponent->getMinWidth() != 0 && pComponent->getMinHeight() != 0)
		{
			if (lpRect.right - lpRect.left < pComponent->getMinWidth() && pComponent->getStretchSide(SIDE_RIGHT))
			{
				lpRect.right += pComponent->getMinWidth() - (lpRect.right - lpRect.left);
			}

			if (lpRect.bottom - lpRect.top < pComponent->getMinHeight() && pComponent->getStretchSide(SIDE_BOTTOM))
			{
				lpRect.bottom += pComponent->getMinHeight() - (lpRect.bottom - lpRect.top);
			}
		}
	}

	*((LPRECT)lParam) = lpRect;

	return TRUE;
}

LRESULT StdHandlerMoveChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EnumChildWindows(hwnd, (WNDENUMPROC)&EnumChildProcUpdateRect, lParam);
	return TRUE;
}

LRESULT StdHandlerMouseMoveChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EnumChildWindows(hwnd, (WNDENUMPROC)&EnumChildProcMouseMove, lParam);
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT StdHandlerSetCursorChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EnumChildWindows(hwnd, (WNDENUMPROC)&EnumChildProcMouseMove, lParam);
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

/*LRESULT StdHandlerMaximuzeWinChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EnumChildWindows(hwnd, (WNDENUMPROC)&EnumChildProcUpdateSize, lParam);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}*/

LRESULT StdHandlerWinDestroy(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}
