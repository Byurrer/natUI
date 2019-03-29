
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __MENU_H
#define __MENU_H

#include "base.h"

//! базовый класс меню
class CMenuBase : public virtual IMenuBase
{
public:
	CMenuBase();
	~CMenuBase();

	void Release(){ mem_del(this); }

	void init();

	bool insertItem(int iIndex, const char *szStr, ID id, ID idSubMenu);
	bool insertPopupItem(int iIndex, const char *szStr, ID id, ID idSubMenu);
	bool insertSeparator(int iIndex, ID id, ID idSubMenu);

	bool deleteItem(ID id);

	NativeHandle getSubMenu(ID id);

	bool setCheckItem(ID id, bool isChecked);
	bool setEnableItem(ID id, bool isEnabled);

	bool getCheckedItem(ID id);
	bool getEnabledItem(ID id);


	NativeHandle getNativeHandle();
	bool setToWindow(HWND hWnd);

	void addHandler(CODE_MSG_MENU codeMsg, HandlerMenu fnHandler);

	void proc(CODE_MSG_MENU codeMsg, const CHandlerMenuData *pData);

protected:

	//! дескриптор меню
	HMENU m_hMenu;

	//! обработчик открытия меню
	HandlerMenu m_fnHandlerOpen;

	//! обработчик выделения элемента меню
	HandlerMenu m_fnHandlerSelect;

	//! обработчик закрытия меню
	HandlerMenu m_fnHandlerClose;
};

//##########################################################################

//! класс главного меню для окна
class CMenuWindow : public CMenuBase, public virtual IMenuWindow
{
public:
	CMenuWindow();
	CMenuWindow(UINT uIdRes);

	void createMenu();

	void Release(){ mem_del(this); }

	//! установка меню для окна
	bool setToWindow(IWindow *pWindow);
};

//##########################################################################

//! класс контекстного окна
class CMenuPopup : public CMenuBase, public virtual IMenuPopup
{
public:
	CMenuPopup();
	CMenuPopup(UINT uRes=-1, int iIndex = 0);

	void createMenu();

	void Release(){ mem_del(this); }

	//! возвращает id по индексу итема
	ID getItemID(int iIndex);

	//! открыть контекстное меню
	bool track(IWindow *pWindow,int iX,int iY);

	void setTargetComponent(IComponent *pComponent);
	IComponent* getTargetComponent();

protected:
	IComponent *m_pTargetComponent = 0;
};

#endif