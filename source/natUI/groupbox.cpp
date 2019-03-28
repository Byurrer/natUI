
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "groupbox.h"


CGroupBox::CGroupBox()
{
	
}

CGroupBox::~CGroupBox()
{
	
}

CGroupBox::CGroupBox(const char* caption, WORD x, WORD y, WORD width, WORD heigth, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
							0,
							"BUTTON",
							caption,
							BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
							x,y,width,heigth,
							(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
							(HMENU)0,
							GetModuleHandle(0),
							0);
	
	initControl(GUI_TYPE_ELEMENT_GROUPBOX, 0, true);
	SetWindowLong(getHWND(),GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	StdHandlerInitMsg(this);
}


