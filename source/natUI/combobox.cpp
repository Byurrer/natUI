
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "combobox.h"

CComboBox::CComboBox()
{

}

CComboBox::CComboBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		"COMBOBOX",
		0,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		iX, iY, iWidth, iHeight,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_COMBOBOX, 0, false);
	SetWindowLong(getHWND(), GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

bool CComboBox::insertItem(int iIndex, const char *szText)
{
	return (SendMessage(m_hWindow, CB_INSERTSTRING, (WPARAM)iIndex, (LPARAM)szText) < 0);
}

bool CComboBox::deleteItem(int iIndex)
{
	return (SendMessage(m_hWindow, CB_DELETESTRING, WPARAM(iIndex), 0) < 0);
}

int CComboBox::getCount()
{
	return SendMessage(m_hWindow, CB_GETCOUNT, 0, 0);
}

bool CComboBox::setSel(int iIndex)
{
	return (SendMessage(m_hWindow, CB_SETCURSEL, WPARAM(iIndex), 0) < 0);
}

int CComboBox::getSel()
{
	return SendMessage(m_hWindow, CB_GETCURSEL, 0, 0);
}


bool CComboBox::clear()
{
	return (SendMessage(m_hWindow, CB_RESETCONTENT, 0, 0));
}

bool CComboBox::setItemData(int iIndex,LONG lData)
{
	return (SendMessage(m_hWindow, CB_SETITEMDATA, WPARAM(iIndex), lData));
}

LPARAM CComboBox::getItemData(int iIndex)
{
	return SendMessage(m_hWindow, CB_GETITEMDATA, WPARAM(iIndex), 0);
}

bool CComboBox::setItemText(int iIndex, const char *szText)
{
	LONG lData = getItemData(iIndex);
		
	if (!deleteItem(iIndex))
		return false;
	if (!insertItem(iIndex, szText))
		return false;
	if (!setItemData(iIndex, lData))
		return false;

	return true;
}

void CComboBox::getItemText(int iIndex, char *szBuffer)
{
	SendMessage(m_hWindow, CB_GETLBTEXT, WPARAM(iIndex), LPARAM(szBuffer));
}

int CComboBox::getItemTextLength(int iIndex)
{
	return SendMessage(m_hWindow, CB_GETLBTEXTLEN, WPARAM(iIndex), 0);
}

bool CComboBox::addItem(const char *szText)
{
	return this->insertItem(-1, szText);
}