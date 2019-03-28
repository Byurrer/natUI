
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "memo.h"

CMemo::CMemo()
{

}

CMemo::CMemo(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		"EDIT",
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN,
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_MEMO, 0, false);
	SetWindowLong(m_hWindow, GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

bool CMemo::getWordWrap()
{
	LONG lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	return ((lStyle & ES_AUTOVSCROLL) && !(lStyle & ES_AUTOHSCROLL));
}

bool CMemo::setWordWrap(bool isWordWrap)
{
	return modifyStyle((isWordWrap ? ES_AUTOVSCROLL : 0), (!isWordWrap ? ES_AUTOVSCROLL : 0));
}