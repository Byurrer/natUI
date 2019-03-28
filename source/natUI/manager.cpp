
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "manager.h"

#include "Windows.h"

#include "natUI.h"
#include "base.h"
#include "window.h"
#include "static.h"
#include "button.h"
#include "edit.h"
#include "updown.h"
#include "memo.h"
#include "combobox.h"
#include "listbox.h"
#include "listview.h"
#include "groupbox.h"
#include "progressbar.h"
#include "radiobutton.h"
#include "checkbox.h"
#include "trackbar.h"
#include "statusbar.h"
#include "hint.h"
#include "menu.h"
#include "toolbar.h"

//##########################################################################

CManager::CManager()
{

}

CManager::~CManager()
{

}

//##########################################################################

IWindow* CManager::newWnd(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent, WND_STYLE style)
{
	return new CWindow(szCaption, iX, iY, iWidth, iHeight, pParent, style);
}

//**********************************************************************

IListBox* CManager::newListBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isMultipleSel)
{
	return new CListBox(iX, iY, iWidth, iHeight, pParent, isMultipleSel);
}

IListView* CManager::newListView(int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CListView(iX, iY, iWidth, iHeight, pParent);
}

IComboBox* CManager::newComboBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CComboBox(iX, iY, iWidth, iHeight, pParent);
}

//**********************************************************************

IButton* CManager::newButton(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent, BUTTON_IMAGE typeImage)
{
	return new CButton(szCaption, iX, iY, iWidth, iHeight, pParent, typeImage);
}

ICheckBox* CManager::newCheckBox(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool is3State)
{
	return new CCheckBox(szCaption, iX, iY, iWidth, iHeight, pParent, is3State);
}

IRadioButton* CManager::newRadioButton(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CRadioButton(szCaption, iX, iY, iWidth, iHeight, pParent);
}

//*************************************************************************

IStatic* CManager::newStatic(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CStatic(szCaption, iX, iY, iWidth, iHeight, pParent);
}

IStatic* CManager::newStaticLine(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isVertical)
{
	return new CStatic(iX, iY, iWidth, iHeight, pParent, isVertical);
}

IEdit* CManager::newEdit(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CEdit(szCaption, iX, iY, iWidth, iHeight, pParent);
}

IMemo* CManager::newMemo(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CMemo(szCaption, iX, iY, iWidth, iHeight, pParent);
}

//**********************************************************************

IToolBar* CManager::newToolBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent, int iWidthElement, int iHeigthElement)
{
	return new CToolBar(iX, iY, iWidth, iHeight, pParent, iWidthElement, iHeigthElement);
}

IStatusBar* CManager::newStatusBar(const char *szCaption, IControl *pParent)
{
	return new CStatusBar(szCaption, pParent);
}

ITrackBar* CManager::newTrackBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent)
{
	return new CTrackBar(iX, iY, iWidth, iHeight, pParent);
}

IProgressBar* CManager::newProgressBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isVertical, bool isSmooth)
{
	return new CProgressBar(iX, iY, iWidth, iHeight, pParent, isVertical, isSmooth);
}

//**********************************************************************

IMenuWindow* CManager::newMenuWindow(UINT uIdRes)
{
	return new CMenuWindow(uIdRes);
}

IMenuPopup* CManager::newMenuContext(UINT uIdRes, int iIndex)
{
	return new CMenuPopup(uIdRes, iIndex);
}