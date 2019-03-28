
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "toolbar.h"


CToolBar::CToolBar()
{

}

CToolBar::CToolBar(int iX, int iY, int iWidth, int iHeigth, IControl *pParent, int iWidthElement, int iHeigthElement)
{
	m_hWindow = CreateWindowEx(
		0,
		TOOLBARCLASSNAME,
		0,
		(pParent != 0 ? WS_CHILD : 0) | TBSTYLE_FLAT | WS_BORDER | CCS_NOMOVEY | CCS_NORESIZE | TBSTYLE_TOOLTIPS | TBSTYLE_WRAPABLE,
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_TOOLBAR, 0, true);
	SetWindowLong(getHWND(),GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();

	HimList = ImageList_Create(iWidthElement, iHeigthElement, ILC_COLOR24 | ILC_MASK, 1, 256);
	SendMessage(m_hWindow, TB_SETIMAGELIST, 0, (LPARAM)HimList);
	ShowWindow(m_hWindow, SW_SHOW);
	StdHandlerInitMsg(this);
}

CToolBar::~CToolBar()
{
	ImageList_Destroy(HimList);
}

void CToolBar::addButton(WORD num,WORD id,const char* hint,WORD id_resource,DWORD mask)
{
	TBBUTTON tbb[1];
	tbb[0].iBitmap = num;
	tbb[0].idCommand = id;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].dwData = 0;
	tbb[0].iString = (INT_PTR)hint;

	HBITMAP HBitmap = LoadBitmap (GetModuleHandle(NULL), MAKEINTRESOURCE(id_resource));
    ImageList_AddMasked (HimList, HBitmap, mask);

	SendMessage (m_hWindow, TB_ADDBUTTONS, 1, (LPARAM)&tbb);
	SendMessage (m_hWindow, TB_SETMAXTEXTROWS, 0, 0);
	SendMessage(m_hWindow, TB_ADDSTRING, 0, (LPARAM)hint);
	ShowWindow (m_hWindow, SW_SHOW);
}

void CToolBar::addSeparator(WORD num)
{
	TBBUTTON tbb[1];
	tbb[0].iBitmap = num;
	tbb[0].idCommand = 0;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_SEP;
	tbb[0].dwData = 0;

	SendMessage(m_hWindow, TB_ADDBUTTONS, 1, (LPARAM)&tbb);
	SendMessage(m_hWindow, TB_SETMAXTEXTROWS, 0, 0);
	ShowWindow(m_hWindow, SW_SHOW);
}