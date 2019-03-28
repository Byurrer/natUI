
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "button.h"

CButton::CButton()
{

}

CButton::CButton(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent, BUTTON_IMAGE typeImage)
{
	UINT uStyle = BS_TEXT;

	if (typeImage == BUTTON_IMAGE_ICON)
		uStyle = BS_ICON;
	else if (typeImage == BUTTON_IMAGE_BITMAT)
		uStyle = BS_BITMAP;

	m_hWindow = CreateWindowEx(
		0,
		"BUTTON",
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | uStyle,
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0
	);

	initControl(GUI_TYPE_ELEMENT_BUTTON, pParent, false);
	IComponent *pComponent = dynamic_cast<IComponent*>(this);
	SetWindowLong(m_hWindow, GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

bool CButton::setIconFromFile(const char *szPath)
{
	long lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	if (!(lStyle & BS_ICON))
		return false;

	HICON hIcon = (HICON)LoadImage(NULL, szPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	if (hIcon == 0)
		return false;

	SendMessage(m_hWindow, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	return true;
}

bool CButton::setBmpFromFile(const char *szPath)
{
	long lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	if (!(lStyle & BS_BITMAP))
		return false;

	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hBmp == 0)
		return false;

	SendMessage(m_hWindow, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
	return true;
}


bool CButton::setIconFromResourse(UINT idRes)
{
	long lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	if (!(lStyle & BS_ICON))
		return false;

	HICON hIcon = LoadCursor(GetModuleHandle(0), MAKEINTRESOURCE(idRes));

	if (hIcon == 0)
		return false;

	SendMessage(m_hWindow, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	return true;
}

bool CButton::setBmpFromResourse(UINT idRes)
{
	long lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	if (!(lStyle & BS_BITMAP))
		return false;

	HBITMAP hBmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(idRes));

	if (hBmp == 0)
		return false;

	SendMessage(m_hWindow, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
	return true;
}

void CButton::addHandlerActivated(HandlerExCommon fnHandler)
{
	addHandlerEx(CODE_MESSAGE_EX_BUTTON_CLICK, fnHandler);
}