
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "listbox.h"


CListBox::CListBox()
{

}

CListBox::CListBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isMultipleSel)
{
	m_hWindow = CreateWindowEx(
		0,
		"LISTBOX",
		0,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | LBS_HASSTRINGS | LBS_NOTIFY | WS_VSCROLL | WS_BORDER | (isMultipleSel ? LBS_EXTENDEDSEL : 0),
		iX, iY, iWidth, iHeight,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_LISTBOX, 0, false);
	SetWindowLong(getHWND(), GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initComponent();
}

bool CListBox::getStateMultiSel()
{
	LONG lStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		
	return (lStyle & LBS_EXTENDEDSEL);
}

void CListBox::setStateMultiSel(bool isMultiSel)
{
	modifyStyle((isMultiSel ? LBS_EXTENDEDSEL : 0), (isMultiSel ? LBS_EXTENDEDSEL : 0));
}


bool CListBox::insertItem(int iIndex,const char *szText)
{
	return (SendMessage(m_hWindow, LB_INSERTSTRING, WPARAM(iIndex), LPARAM(szText)));
}

bool CListBox::addItem(const char *szText)
{
	return (SendMessage(m_hWindow, LB_ADDSTRING, 0, LPARAM(szText)));
}

bool CListBox::deleteItem(int iIndex)
{
	return (SendMessage(m_hWindow, LB_DELETESTRING, WPARAM(iIndex), 0));
}

int CListBox::getItemCount()
{
	return SendMessage(m_hWindow,LB_GETCOUNT,0,0);
}

bool CListBox::setSel(int iIndex)
{
	return SendMessage(m_hWindow, LB_SETCURSEL, (WPARAM)iIndex, 0);
}

int CListBox::getSel()
{
	return SendMessage(m_hWindow,LB_GETCURSEL,0,0);
}


bool CListBox::setItemData(int iIndex, LONG lData)
{
	return (SendMessage(m_hWindow, LB_SETITEMDATA, WPARAM(iIndex), lData));
}

LONG CListBox::getItemData(int iIndex)
{
	return SendMessage(m_hWindow, LB_GETITEMDATA, WPARAM(iIndex), 0);
}

bool CListBox::clear()
{
	return (SendMessage(m_hWindow, LB_RESETCONTENT, 0, 0));
}

bool CListBox::setItemText(int iIndex, const char *szText)
{
	LPARAM data = getItemData(iIndex);
	int sel = getSel();

	deleteItem(iIndex);
	insertItem(iIndex, szText);

	if (sel == iIndex)
		setSel(iIndex);

	return setItemData(iIndex, data);
}

void CListBox::getItemText(int iIndex, char *szBuf)
{
	SendMessage(m_hWindow, LB_GETTEXT, WPARAM(iIndex), LPARAM(szBuf));
}

int CListBox::getItemTextLength(int iIndex)
{
	return SendMessage(m_hWindow, LB_GETTEXTLEN, WPARAM(iIndex), 0);
}


int CListBox::getMultiSelCount()
{
	return SendMessage(m_hWindow,LB_GETSELCOUNT,0,0);
}

bool CListBox::setMultiSel(int iIndex, bool sel)
{
	return (SendMessage(m_hWindow, LB_SETSEL, WPARAM(sel ? 1 : 0), LPARAM(iIndex)));
}

bool CListBox::getMultiSel(int iIndex)
{
	return (!SendMessage(m_hWindow, LB_GETSEL, WPARAM(iIndex), 0));
}

int CListBox::getMultiSelArr(int **ppArr)
{
	if (!ppArr)
		return 0;

	int iCount = getMultiSelCount();

	if (iCount <= 0)
		return iCount;

	*ppArr = new int[iCount];
	SendMessage(m_hWindow, LB_GETSELITEMS, WPARAM(iCount), LPARAM(*ppArr));
	return iCount;
}
