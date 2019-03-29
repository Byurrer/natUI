
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "menu.h"


CMenuBase::CMenuBase()
{
	m_hMenu = 0;

	m_fnHandlerOpen = 0;
	m_fnHandlerSelect = 0;
	m_fnHandlerClose = 0;
}

CMenuBase::~CMenuBase()
{
	DestroyMenu(m_hMenu);
}

void CMenuBase::init()
{
	SetUserData4Menu(m_hMenu, (LONG)dynamic_cast<IMenuBase*>(this));
}

bool CMenuBase::insertItem(int iIndex, const char *szStr, ID idItem, ID idSubMenu)
{
	char szBuffer[256];
	sprintf(szBuffer, "%s", szStr);

	MENUITEMINFO oMII;
	ZeroMemory(&oMII, sizeof(MENUITEMINFO));
	oMII.cbSize = sizeof(MENUITEMINFO);
	oMII.fMask = MIIM_STRING | MIIM_ID;
	oMII.dwTypeData = szBuffer;
	oMII.wID = idItem;

	HMENU hSubMenu = 0;
	if (idSubMenu != -1)
		hSubMenu = (HMENU)getSubMenu(idSubMenu);

	int iRes = InsertMenuItem((hSubMenu ? hSubMenu : m_hMenu), iIndex, TRUE, &oMII);
	
	return iRes;
}

bool CMenuBase::insertPopupItem(int iIndex, const char *szStr, ID idItem, ID idSubMenu)
{
	char szBuffer[256];
	sprintf(szBuffer, "%s", szStr);
	
	HMENU hSubMenu = CreatePopupMenu();
	
	MENUITEMINFO oMII;
	ZeroMemory(&oMII, sizeof(MENUITEMINFO));
	oMII.cbSize = sizeof(MENUITEMINFO);
	oMII.fMask = MIIM_STRING | MIIM_SUBMENU | MIIM_FTYPE | MIIM_ID;
	oMII.fType = MFT_STRING;
	oMII.dwTypeData = szBuffer;
	oMII.wID = idItem;
	oMII.hSubMenu = hSubMenu;

	HMENU hSubMenu2 = 0;
	if (idSubMenu != -1)
		hSubMenu2 = (HMENU)getSubMenu(idSubMenu);

	int iRes = InsertMenuItem((hSubMenu2 ? hSubMenu2 : m_hMenu), iIndex, TRUE, &oMII);
	
	return iRes;
}

bool CMenuBase::insertSeparator(int iIndex, ID id, ID idSubMenu)
{
	MENUITEMINFO oMII;
	ZeroMemory(&oMII, sizeof(MENUITEMINFO));
	oMII.cbSize = sizeof(MENUITEMINFO);
	oMII.fMask = MIIM_ID | MIIM_FTYPE;
	oMII.wID = id;
	oMII.fType = MFT_SEPARATOR;

	HMENU hSubMenu = 0;
	if (idSubMenu != -1)
		hSubMenu = (HMENU)getSubMenu(idSubMenu);

	int iRes = InsertMenuItem((hSubMenu ? hSubMenu : m_hMenu), iIndex, TRUE, &oMII);
	
	return iRes;
}

bool CMenuBase::deleteItem(ID id)
{
	return (bool)(DeleteMenu(m_hMenu,id,MF_BYCOMMAND));
}

NativeHandle CMenuBase::getSubMenu(ID id)
{
	MENUITEMINFO oMI;
	ZeroMemory(&oMI, sizeof(MENUITEMINFO));
	oMI.cbSize = sizeof(MENUITEMINFO);
	oMI.fMask = MIIM_SUBMENU;
	oMI.hSubMenu = 0;

	int iRes = GetMenuItemInfo(m_hMenu, id, FALSE, &oMI);

	return (NativeHandle)(iRes ? oMI.hSubMenu : 0);
}

bool CMenuBase::setCheckItem(ID id, bool isChecked)
{
	DWORD dwVar = CheckMenuItem(m_hMenu, id, (isChecked ? MF_CHECKED : MF_UNCHECKED));
	
	return ((dwVar != 0xFFFFFFFF) || (dwVar == -1)) ? true : false;
}

bool CMenuBase::getCheckedItem(ID id)
{
	MENUITEMINFO oMI;
	ZeroMemory(&oMI, sizeof(MENUITEMINFO));
	oMI.cbSize = sizeof(MENUITEMINFO);
	oMI.fMask = MIIM_STATE;
	BOOL bf = GetMenuItemInfo(m_hMenu, id, FALSE, &oMI);

	return (oMI.fState & MFS_CHECKED);
}

bool CMenuBase::setEnableItem(ID id, bool isEnabled)
{
	DWORD dwEnable = (isEnabled ? MFS_ENABLED : MFS_DISABLED);

	int iRes = EnableMenuItem(m_hMenu, id, dwEnable);
	
	return ((iRes != 0xFFFFFFFF) || (iRes == -1));
}

bool CMenuBase::getEnabledItem(ID id)
{
	MENUITEMINFO oMI;
	ZeroMemory(&oMI, sizeof(MENUITEMINFO));
	oMI.cbSize = sizeof(MENUITEMINFO);
	oMI.fMask = MIIM_STATE;
	
	BOOL iRes = GetMenuItemInfo(m_hMenu, id, FALSE, &oMI);
	
	return (oMI.fState & MFS_ENABLED);
}

NativeHandle CMenuBase::getNativeHandle()
{
	return m_hMenu;
}

void CMenuBase::addHandler(CODE_MSG_MENU codeMsg, HandlerMenu fnHandler)
{
	if (codeMsg == CODE_MSG_MENU_OPEN)
		m_fnHandlerOpen = fnHandler;
	else if (codeMsg == CODE_MSG_MENU_SELECT)
		m_fnHandlerSelect = fnHandler;
	else if (codeMsg == CODE_MSG_MENU_CLOSE)
		m_fnHandlerClose = fnHandler;
}

void CMenuBase::proc(CODE_MSG_MENU codeMsg, const CHandlerMenuData *pData)
{
	if (codeMsg == CODE_MSG_MENU_OPEN)
	{
		if (!m_fnHandlerOpen)
			return;

		m_fnHandlerOpen(this, pData);
	}
	else if (codeMsg == CODE_MSG_MENU_SELECT)
	{
		if (!m_fnHandlerSelect)
			return;

		m_fnHandlerSelect(this, pData);
	}
	else if (codeMsg == CODE_MSG_MENU_CLOSE)
	{
		if (!m_fnHandlerClose)
			return;

		m_fnHandlerClose(this, pData);
	}
}

//##########################################################################

CMenuWindow::CMenuWindow()
{
	createMenu();
	init();
}

CMenuWindow::CMenuWindow(UINT uIdRes)
{
	if (uIdRes != -1)
		m_hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(uIdRes));
	else
		createMenu();

	init();
}

void CMenuWindow::createMenu()
{
	m_hMenu = CreateMenu();
}

bool CMenuWindow::setToWindow(IWindow *pWindow)
{
	if (!pWindow || !SetMenu((HWND)(pWindow->getNativeHandle()), m_hMenu))
		return false;

	return true;
}

//##########################################################################

CMenuPopup::CMenuPopup(UINT uIdRes, int iIndex)
{
	if (uIdRes != -1)
	{
		m_hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(uIdRes));
		m_hMenu = ::GetSubMenu(m_hMenu, iIndex);
	}
	else
	{
		createMenu();
	}

	init();
}

CMenuPopup::CMenuPopup()
{
	createMenu();

	init();
}

void CMenuPopup::createMenu()
{
	m_hMenu = CreatePopupMenu();
}

bool CMenuPopup::track(IWindow *pWindow, int iX, int iY)
{
	int iPosX, iPosY;

	if ((iX == -1) && (iY == -1))
	{
		POINT oPoint;
		GetCursorPos(&oPoint);
		iPosX = oPoint.x;
		iPosY = oPoint.y;
	}
	else
	{
		iPosX = iX;
		iPosY = iY;
	}

	return TrackPopupMenu(m_hMenu, TPM_LEFTALIGN, iPosX, iPosY, 0, (HWND)(pWindow->getNativeHandle()), 0);
}

ID CMenuPopup::getItemID(int iIndex)
{
	return GetMenuItemID(m_hMenu, iIndex);
}

void CMenuPopup::setTargetComponent(IComponent *pComponent)
{
	m_pTargetComponent = pComponent;
}

IComponent* CMenuPopup::getTargetComponent()
{
	return m_pTargetComponent;
}