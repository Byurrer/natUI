
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "updown.h"


CUpDown::CUpDown()
{

}

CUpDown::~CUpDown()
{

}

CUpDown::CUpDown(int iX, int iY, int iWidth, int iHeigth, IControl *pParent, IControl *pBuddy, bool isAlignLeft)
{
	m_hWindow = CreateWindowEx(
		0,
		UPDOWN_CLASS,
		0,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | UDS_WRAP | UDS_SETBUDDYINT | UDS_ARROWKEYS | (isAlignLeft ? UDS_ALIGNRIGHT : UDS_ALIGNLEFT),
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);

	SendMessage(m_hWindow, UDM_SETRANGE32, -65535, 65535);
    SendMessage(m_hWindow, UDM_SETPOS32, 0, 0);
		
	if (pBuddy)
		SendMessage(m_hWindow, UDM_SETBUDDY, (WPARAM)((HWND)(pBuddy->getNativeHandle())), 0);
		//setBuddy((HWND)(pBuddy->getNativeHandle()));

	initControl(GUI_TYPE_ELEMENT_UPDOWND, 0, false);
	SetWindowLong(m_hWindow,GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();
}

void CUpDown::setMinMax(int min, int max)
{
	SendMessage(m_hWindow, UDM_SETRANGE32, min, max);
}

int CUpDown::setPos(int pos)
{
	return SendMessage(m_hWindow, UDM_SETPOS32, 0, pos);
}

int CUpDown::getMin()
{
	int iMin = 0;
	SendMessage(m_hWindow, UDM_GETRANGE32, (WPARAM)&iMin, 0);
	return iMin;
}

int CUpDown::getMax()
{
	int iMax = 0;
	SendMessage(m_hWindow, UDM_GETRANGE32, 0, (LPARAM)&iMax);
	return iMax;
}

int CUpDown::getPos()
{
	return SendMessage(m_hWindow, UDM_GETPOS32, 0, 0);
}

/*HWND CUpDown::setBuddy(HWND buddy)
{
	return (HWND)SendMessage(m_hWindow, UDM_SETBUDDY, (WPARAM)buddy, 0);
}

HWND CUpDown::getBuddy()
{
	return (HWND)SendMessage(m_hWindow, UDM_GETBUDDY, 0, 0);
}*/