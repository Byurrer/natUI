
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "radiobutton.h"


CRadioButton::CRadioButton()
{

}

CRadioButton::CRadioButton(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		"BUTTON",
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | BS_AUTORADIOBUTTON,
		iX, iY, iWidth, iHeight,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_RADIOBUTTON, 0, false);
	SetWindowLong(getHWND(), GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initComponent();
}

void CRadioButton::setCheck(bool check)
{
	SendMessage(m_hWindow, BM_SETCHECK, (check ? BST_CHECKED : BST_UNCHECKED), 0);
}

bool CRadioButton::getCheck()
{
	return SendMessage(m_hWindow, BM_GETCHECK, 0, 0) ? true : false;
}