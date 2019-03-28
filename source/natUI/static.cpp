
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "static.h"


CStatic::CStatic()
{

}

CStatic::CStatic(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
							0,
							"STATIC",
							szCaption,
							(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | SS_LEFT,
							iX, iY, iWidth, iHeight,
							(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
							(HMENU)0,
							GetModuleHandle(0),
							0);
	
	initControl(GUI_TYPE_ELEMENT_STATIC, pParent, false);
	SetWindowLong(getHWND(),GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

CStatic::CStatic(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isVertical)
{
	m_hWindow = CreateWindowEx(
							WS_EX_TOPMOST,
							"STATIC",
							0,
							(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | SS_LEFT | (isVertical ? SS_ETCHEDVERT : SS_ETCHEDHORZ),
							iX, iY, iWidth, iHeight,
							(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
							(HMENU)0,
							GetModuleHandle(0),
							0);
	
	initControl(GUI_TYPE_ELEMENT_STATIC, pParent, false);
	SetWindowLong(getHWND(),GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

TEXT_ALIGN CStatic::getAlign()
{
	long style = GetWindowLong(this->getHWND(),GWL_STYLE);
		if(style & SS_RIGHT)
			return TEXT_ALIGN_RIGHT;
		else if(style & SS_CENTER)
			return TEXT_ALIGN_CENTER;
		else
			return TEXT_ALIGN_LEFT;
}

bool CStatic::setAlign(TEXT_ALIGN align)
{
	if (align == TEXT_ALIGN_LEFT)
		return this->modifyStyle(SS_LEFT,0);
	else if (align == TEXT_ALIGN_RIGHT)
		return this->modifyStyle(SS_RIGHT,0);
	else if (align == TEXT_ALIGN_CENTER)
		return this->modifyStyle(SS_CENTER,0);
	return false;
}

bool CStatic::getWordWrap()
{
	long style = GetWindowLong(this->getHWND(),GWL_STYLE);
		if(!(style & SS_LEFTNOWORDWRAP))
			return true;
	return false;
}

bool CStatic::setWordWrap(bool bf)
{
	return this->modifyStyle(!bf ? SS_LEFTNOWORDWRAP : 0,bf ? SS_LEFTNOWORDWRAP : 0);
}
