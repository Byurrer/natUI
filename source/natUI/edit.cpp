
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "edit.h"

CEdit::CEdit() 
{

}

CEdit::~CEdit()
{

}

CEdit::CEdit(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		"EDIT",
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_EDIT, 0, false);
	SetWindowLong(m_hWindow, GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

bool CEdit::getReadOnly()
{
	LONG lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	return (lStyle & ES_READONLY);
}

bool CEdit::setReadOnly(bool isReadOnly)
{
	SendMessage(m_hWindow, EM_SETREADONLY, (isReadOnly ? 1 : 0), 0);
	return (getReadOnly() == isReadOnly);
}

TEXT_ALIGN CEdit::getAlign()
{
	LONG lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	if (lStyle & ES_RIGHT)
		return TEXT_ALIGN_RIGHT;
	else if (lStyle & ES_CENTER)
		return TEXT_ALIGN_CENTER;
	else
		return TEXT_ALIGN_LEFT;
}

bool CEdit::setAlign(TEXT_ALIGN align)
{
	if (align == TEXT_ALIGN_LEFT)
		return modifyStyle(ES_LEFT,0);
	else if (align == TEXT_ALIGN_RIGHT)
		return modifyStyle(ES_RIGHT,0);
	else if (align == TEXT_ALIGN_CENTER)
		return modifyStyle(ES_CENTER,0);
	
	return false;
}

bool CEdit::getStatePassword()
{
	LONG lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	return (lStyle & ES_PASSWORD);
}

bool CEdit::setStatePassword(bool isPasword)
{
	SendMessage(m_hWindow, EM_SETPASSWORDCHAR, (isPasword ? '*' : 0), 0);
	setFocus();
	UpdateWindow(m_hWindow);

	return (getStatePassword() == isPasword);
}