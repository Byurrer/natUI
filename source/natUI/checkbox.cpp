
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "checkbox.h"


CCheckBox::CCheckBox()
{

}

CCheckBox::CCheckBox(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent, bool is3State)
{
	m_hWindow = CreateWindowEx(
		0,
		"BUTTON",
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | (is3State ? BS_AUTO3STATE : BS_AUTOCHECKBOX),
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_CHECKBOX, 0, false);
	SetWindowLong(m_hWindow, GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

void CCheckBox::setCheckEx(CHECKBOX_STATE check)
{
	SendMessage(m_hWindow, BM_SETCHECK, check, 0);
}

void CCheckBox::setCheck(bool isCheck)
{
	SendMessage(m_hWindow, BM_SETCHECK, isCheck, 0);
}

CHECKBOX_STATE CCheckBox::getCheck()
{
	return (CHECKBOX_STATE)SendMessage(m_hWindow, BM_GETCHECK, 0, 0);
}