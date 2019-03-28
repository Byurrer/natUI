
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "listview.h"


CListView::CListView()
{

}

CListView::CListView(int iX, int iY, int iWidth, int iHeigth, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		WC_LISTVIEW,
		0,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | /*WS_VSCROLL | WS_HSCROLL | LVS_ALIGNLEFT |*/ LVS_SHOWSELALWAYS | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);

	ListView_SetExtendedListViewStyleEx(m_hWindow, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	initControl(GUI_TYPE_ELEMENT_LISTVIEW, 0, false);
	SetWindowLong(getHWND(), GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
}

int CListView::insertColumn(const char *szText, int iIndex, int iWidth)
{
	LVCOLUMN lvc;
	memset(&lvc, 0, sizeof(LVCOLUMN));
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = iWidth;
	lvc.pszText = (char*)szText;

	int iRes = ListView_InsertColumn(m_hWindow, iIndex, &lvc);

	if (iIndex < m_aStrings.size() - 1)
	{
		m_aStrings[m_aStrings.size()] = m_aStrings[iIndex];
		Array<String> aNewStrings;
		m_aStrings[iIndex] = aNewStrings;
	}
	else
		m_aStrings[m_aStrings.size()];

	return iRes;
}

int CListView::addColumn(const char *szText, int iWidth)
{
	m_aStrings[m_aStrings.size()];
	return insertColumn(szText, getColumnsCount(), iWidth);
}

void CListView::deleteColumn(int iIndex)
{
	m_aStrings.erase(iIndex);
	ListView_DeleteColumn(m_hWindow, iIndex);
}

int CListView::getColumnsCount()
{
	HWND hHeader = ListView_GetHeader(m_hWindow);
	return ::SendMessage(hHeader, HDM_GETITEMCOUNT, 0, 0);
}

int CListView::addString(LONG lData)
{
	LVITEM lvi;
	memset(&lvi, 0, sizeof(LVCOLUMN));
	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iItem = getStringCount();
	lvi.iSubItem = 0;
	lvi.lParam = lData;
	m_aStringData.push_back(lData);
	return ListView_InsertItem(m_hWindow, &lvi);
}

void CListView::deleteString(int iIndexString)
{
	ListView_DeleteItem(m_hWindow, iIndexString);
}

int CListView::getStringCount()
{
	return ListView_GetItemCount(m_hWindow);
}

void CListView::setItemText(const char* text, int iIndexColumn, int iIndexString)
{
	m_aStrings[iIndexColumn][iIndexString] = text;
	ListView_SetItemText(m_hWindow, iIndexString, iIndexColumn, (char*)m_aStrings[iIndexColumn][iIndexString].c_str());
}

void CListView::getItemText(char *szBuffer, int iIndexColumn, int iIndexString, int iSizeOfBuffer)
{
	ListView_GetItemText(m_hWindow, iIndexString, iIndexColumn, szBuffer, iSizeOfBuffer);
}

void CListView::setItemData(int iIndexString, LONG lData)
{
	LVITEM lvi;
	lvi.iItem = iIndexString;
	lvi.iSubItem = 0;

	ListView_GetItem(m_hWindow, &lvi);

	lvi.mask = lvi.mask | LVIF_PARAM;
	lvi.iSubItem = 0;
	lvi.lParam = lData;
	BOOL res = ListView_SetItem(m_hWindow, &lvi);
	m_aStringData[iIndexString] = lData;
}

LPARAM CListView::getItemData(int iIndexString)
{
	LVITEM lvi;
	lvi.iItem = iIndexString;
	lvi.iSubItem = 0;

	BOOL res = ListView_GetItem(m_hWindow, &lvi);
	return m_aStringData[iIndexString];// lvi.lParam;
}

int CListView::getSelString(int iStart)
{
	return ::SendMessage(m_hWindow, LVM_GETNEXTITEM, iStart, LVNI_SELECTED);
}

void CListView::setSelString(int iIndexString)
{
	if (iIndexString < 0)
	{
		for (int i = 0; i < this->getStringCount(); ++i)
			ListView_SetItemState(m_hWindow, i, 0x0, LVIS_SELECTED | LVIS_FOCUSED);
	}
	else
		ListView_SetItemState(m_hWindow, iIndexString, 0xF, LVIS_SELECTED | LVIS_FOCUSED);
	this->setFocus();
}

int CListView::getSelColumn()
{
	return ListView_GetSelectedColumn(m_hWindow);
}

void CListView::setSelColumn(int iIndexColumn)
{
	ListView_SetSelectedColumn(m_hWindow, iIndexColumn);
}

void CListView::clear()
{
	clearStrings();
	ListView_DeleteAllItems(m_hWindow);

	while (getColumnsCount() > 0)
	{
		deleteColumn(0);
	}
}

void CListView::clearStrings()
{
	int countstr = getStringCount();
	for (int i = 0; i < countstr; ++i)
		deleteString(0);

	for (int i = 0; i < m_aStrings.size(); ++i)
		m_aStrings[i].clear();

	m_aStringData.clear();
}