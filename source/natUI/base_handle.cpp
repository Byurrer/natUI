
#include "base_handle.h"
#include "base_component.h"
#include "window.h"

//##########################################################################

CHandle::CHandle()
{
	initMapKey();
}

CHandle::~CHandle()
{

}

void CHandle::initMapKey()
{
	m_aVkeys.resize(256);
	memset(&(m_aVkeys[0]), VKEY_NULL, sizeof(VKEY_NULL)* m_aVkeys.size());

	m_aVkeys[VK_BACK] = VKEY_BACK;
	m_aVkeys[VK_TAB] = VKEY_TAB;

	m_aVkeys[VK_CLEAR] = VKEY_CLEAR;
	m_aVkeys[VK_RETURN] = VKEY_RETURN;

	m_aVkeys[VK_SHIFT] = VKEY_SHIFT;
	m_aVkeys[VK_CONTROL] = VKEY_CONTROL;
	m_aVkeys[VK_MENU] = VKEY_MENU;
	m_aVkeys[VK_PAUSE] = VKEY_PAUSE;
	m_aVkeys[VK_CAPITAL] = VKEY_CAPITAL;

	m_aVkeys[VK_ESCAPE] = VKEY_ESCAPE;

	m_aVkeys[VK_CONVERT] = VKEY_CONVERT;
	m_aVkeys[VK_NONCONVERT] = VKEY_NONCONVERT;
	m_aVkeys[VK_ACCEPT] = VKEY_ACCEPT;
	m_aVkeys[VK_MODECHANGE] = VKEY_MODECHANGE;

	m_aVkeys[VK_SPACE] = VKEY_SPACE;
	m_aVkeys[VK_PRIOR] = VKEY_PRIOR;
	m_aVkeys[VK_NEXT] = VKEY_NEXT;
	m_aVkeys[VK_END] = VKEY_END;
	m_aVkeys[VK_HOME] = VKEY_HOME;
	m_aVkeys[VK_LEFT] = VKEY_LEFT;
	m_aVkeys[VK_UP] = VKEY_UP;
	m_aVkeys[VK_RIGHT] = VKEY_RIGHT;
	m_aVkeys[VK_DOWN] = VKEY_DOWN;
	m_aVkeys[VK_SELECT] = VKEY_SELECT;
	m_aVkeys[VK_PRINT] = VKEY_PRINT;
	m_aVkeys[VK_EXECUTE] = VKEY_EXECUTE;
	m_aVkeys[VK_SNAPSHOT] = VKEY_SNAPSHOT;
	m_aVkeys[VK_INSERT] = VKEY_INSERT;
	m_aVkeys[VK_DELETE] = VKEY_DELETE;
	m_aVkeys[VK_HELP] = VKEY_HELP;

	m_aVkeys[VK_0] = VKEY_0;
	m_aVkeys[VK_1] = VKEY_1;
	m_aVkeys[VK_2] = VKEY_2;
	m_aVkeys[VK_3] = VKEY_3;
	m_aVkeys[VK_4] = VKEY_4;
	m_aVkeys[VK_5] = VKEY_5;
	m_aVkeys[VK_6] = VKEY_6;
	m_aVkeys[VK_7] = VKEY_7;
	m_aVkeys[VK_8] = VKEY_8;
	m_aVkeys[VK_9] = VKEY_9;

	m_aVkeys[VK_A] = VKEY_A;
	m_aVkeys[VK_B] = VKEY_B;
	m_aVkeys[VK_C] = VKEY_C;
	m_aVkeys[VK_D] = VKEY_D;
	m_aVkeys[VK_E] = VKEY_E;
	m_aVkeys[VK_F] = VKEY_F;
	m_aVkeys[VK_G] = VKEY_G;
	m_aVkeys[VK_H] = VKEY_H;
	m_aVkeys[VK_I] = VKEY_I;
	m_aVkeys[VK_J] = VKEY_J;
	m_aVkeys[VK_K] = VKEY_K;
	m_aVkeys[VK_L] = VKEY_L;
	m_aVkeys[VK_M] = VKEY_M;
	m_aVkeys[VK_N] = VKEY_N;
	m_aVkeys[VK_O] = VKEY_O;
	m_aVkeys[VK_P] = VKEY_P;
	m_aVkeys[VK_Q] = VKEY_Q;
	m_aVkeys[VK_R] = VKEY_R;
	m_aVkeys[VK_S] = VKEY_S;
	m_aVkeys[VK_T] = VKEY_T;
	m_aVkeys[VK_U] = VKEY_U;
	m_aVkeys[VK_V] = VKEY_V;
	m_aVkeys[VK_W] = VKEY_W;
	m_aVkeys[VK_X] = VKEY_X;
	m_aVkeys[VK_Y] = VKEY_Y;
	m_aVkeys[VK_Z] = VKEY_Z;

	m_aVkeys[VK_LWIN] = VKEY_LWIN;
	m_aVkeys[VK_RWIN] = VKEY_RWIN;
	m_aVkeys[VK_APPS] = VKEY_APPS;

	m_aVkeys[VK_SLEEP] = VKEY_SLEEP;

	m_aVkeys[VK_NUMPAD0] = VKEY_NUMPAD0;
	m_aVkeys[VK_NUMPAD1] = VKEY_NUMPAD1;
	m_aVkeys[VK_NUMPAD2] = VKEY_NUMPAD2;
	m_aVkeys[VK_NUMPAD3] = VKEY_NUMPAD3;
	m_aVkeys[VK_NUMPAD4] = VKEY_NUMPAD4;
	m_aVkeys[VK_NUMPAD5] = VKEY_NUMPAD5;
	m_aVkeys[VK_NUMPAD6] = VKEY_NUMPAD6;
	m_aVkeys[VK_NUMPAD7] = VKEY_NUMPAD7;
	m_aVkeys[VK_NUMPAD8] = VKEY_NUMPAD8;
	m_aVkeys[VK_NUMPAD9] = VKEY_NUMPAD9;
	m_aVkeys[VK_MULTIPLY] = VKEY_MULTIPLY;
	m_aVkeys[VK_ADD] = VKEY_ADD;
	m_aVkeys[VK_SEPARATOR] = VKEY_SEPARATOR;
	m_aVkeys[VK_SUBTRACT] = VKEY_SUBTRACT;
	m_aVkeys[VK_DECIMAL] = VKEY_DECIMAL;
	m_aVkeys[VK_DIVIDE] = VKEY_DIVIDE;

	m_aVkeys[VK_F1] = VKEY_F1;
	m_aVkeys[VK_F2] = VKEY_F2;
	m_aVkeys[VK_F3] = VKEY_F3;
	m_aVkeys[VK_F4] = VKEY_F4;
	m_aVkeys[VK_F5] = VKEY_F5;
	m_aVkeys[VK_F6] = VKEY_F6;
	m_aVkeys[VK_F7] = VKEY_F7;
	m_aVkeys[VK_F8] = VKEY_F8;
	m_aVkeys[VK_F9] = VKEY_F9;
	m_aVkeys[VK_F10] = VKEY_F10;
	m_aVkeys[VK_F11] = VKEY_F11;
	m_aVkeys[VK_F12] = VKEY_F12;
	m_aVkeys[VK_F13] = VKEY_F13;
	m_aVkeys[VK_F14] = VKEY_F14;
	m_aVkeys[VK_F15] = VKEY_F15;
	m_aVkeys[VK_F16] = VKEY_F16;
	m_aVkeys[VK_F17] = VKEY_F17;
	m_aVkeys[VK_F18] = VKEY_F18;
	m_aVkeys[VK_F19] = VKEY_F19;
	m_aVkeys[VK_F20] = VKEY_F20;
	m_aVkeys[VK_F21] = VKEY_F21;
	m_aVkeys[VK_F22] = VKEY_F22;
	m_aVkeys[VK_F23] = VKEY_F23;
	m_aVkeys[VK_F24] = VKEY_F24;

	m_aVkeys[VK_NUMLOCK] = VKEY_NUMLOCK;
	m_aVkeys[VK_SCROLL] = VKEY_SCROLL;

	m_aVkeys[VK_LSHIFT] = VKEY_LSHIFT;
	m_aVkeys[VK_RSHIFT] = VKEY_RSHIFT;
	m_aVkeys[VK_LCONTROL] = VKEY_LCONTROL;
	m_aVkeys[VK_RCONTROL] = VKEY_RCONTROL;
	m_aVkeys[VK_LMENU] = VKEY_LMENU;
	m_aVkeys[VK_RMENU] = VKEY_RMENU;
}

void CHandle::addHandlerMouse(CODE_MESSAGE_MOUSE codeMsgMouse, HandlerMouse fnHandler)
{
	bool isUnic = true;
	for (int i = 0, il = m_aHandlersMouse.size(); i < il; ++i)
	{
		CHandlerMouse *pHandlerMouse = m_aHandlersMouse[i];
		if (pHandlerMouse->m_codeMouse == codeMsgMouse)
		{
			isUnic = false;
			break;
		}
	}

	if (isUnic)
		m_aHandlersMouse.push_back(new CHandlerMouse(codeMsgMouse, fnHandler));
	else
	{

	}
}

void CHandle::addHandlerKey(CODE_MESSAGE_KEY codeMsgKey, HandlerKey fnHandler)
{
	bool isUnic = true;
	for (int i = 0, il = m_aHandlersKey.size(); i < il; ++i)
	{
		CHandlerKey *pHandlerKey = m_aHandlersKey[i];
		if (pHandlerKey->m_codeKey == codeMsgKey)
		{
			isUnic = false;
			break;
		}
	}

	if (isUnic)
		m_aHandlersKey.push_back(new CHandlerKey(codeMsgKey, fnHandler));
	else
	{

	}
}

void CHandle::addHandlerTimer(UINT uiMlsec, HandlerTimer fnHandler, ID idTimer)
{
	ID idKeyTimer = -1;

	if (idTimer == -1)
	{
		ID idLast = -1;
		for (int i = 0, il = m_aHandlersTime.size(); i < il; ++i)
		{
			CHandlerTimer *pHandlerTimer = m_aHandlersTime[i];
			if (pHandlerTimer->m_idTimer > idLast)
				idLast = pHandlerTimer->m_idTimer;
		}

		idTimer = idLast+1;
	}
	else
	{
		for (int i = 0, il = m_aHandlersTime.size(); i < il; ++i)
		{
			CHandlerTimer *pHandlerTimer = m_aHandlersTime[i];
			if (pHandlerTimer->m_idTimer == idTimer)
			{
				idKeyTimer = i;
				break;
			}
		}
	}

	if (idKeyTimer == -1)
		m_aHandlersTime.push_back(new CHandlerTimer(idTimer, fnHandler));
	else
	{
		m_aHandlersTime[idKeyTimer]->m_fnHandler = fnHandler;
	}

	SetTimer(m_hWindow, idTimer, uiMlsec, 0);
}

void CHandle::addHandlerEx(CODE_MESSAGE_EX codeMsgEx, void *pHandler)
{
	bool isUnic = true;
	for (int i = 0, il = m_aHandlersEx.size(); i < il; ++i)
	{
		CHandlerEx *pHandlerEx = m_aHandlersEx[i];
		if (pHandlerEx->m_codeMsgEx == codeMsgEx)
		{
			isUnic = false;
			break;
		}
	}

	if (isUnic)
		m_aHandlersEx.push_back(new CHandlerEx(codeMsgEx, pHandler));
	else
	{

	}
}

//**************************************************************************

bool CHandle::isMsgMouse(UINT uMsg)
{
	return (
		uMsg == WM_MOUSEMOVE || 
		uMsg == WM_MOUSEWHEEL ||
		uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_LBUTTONDBLCLK || 
		uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_RBUTTONDBLCLK || 
		uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MBUTTONDBLCLK
		);
}

CODE_MESSAGE_MOUSE CHandle::getCodeMouseOfMsg(UINT uMsg)
{
	if (uMsg == WM_MOUSEMOVE)
		return CODE_MESSAGE_MOUSE_MOVE;

	else if (uMsg == WM_MOUSEWHEEL)
		return CODE_MESSAGE_MOUSE_SCROLL;

	else if (uMsg == WM_LBUTTONDOWN)
		return CODE_MESSAGE_MOUSE_LDOWN;
	else if (uMsg == WM_LBUTTONUP)
		return CODE_MESSAGE_MOUSE_LUP;
	else if (uMsg == WM_LBUTTONDBLCLK)
		return CODE_MESSAGE_MOUSE_LDBL;

	else if (uMsg == WM_RBUTTONDOWN)
		return CODE_MESSAGE_MOUSE_LDOWN;
	else if (uMsg == WM_RBUTTONUP)
		return CODE_MESSAGE_MOUSE_LUP;
	else if (uMsg == WM_RBUTTONDBLCLK)
		return CODE_MESSAGE_MOUSE_LDBL;

	return CODE_MESSAGE_MOUSE_NONE;
}

CHandlerMouse* CHandle::getHandlerMouse(CODE_MESSAGE_MOUSE codeMouse)
{
	if (codeMouse == CODE_MESSAGE_MOUSE_NONE)
		return 0;

	for (int i = 0; i < m_aHandlersMouse.size(); ++i)
	{
		CHandlerMouse *pHandlerMouse = m_aHandlersMouse[i];
		if (pHandlerMouse->m_codeMouse == codeMouse)
			return pHandlerMouse;
	}

	return 0;
}

//**************************************************************************

CODE_MESSAGE_KEY CHandle::getCodeKeyOfMsg(UINT uMsg)
{
	if (uMsg == WM_KEYDOWN)
		return CODE_MESSAGE_KEY_DOWN;
	else if (uMsg == WM_KEYUP)
		return CODE_MESSAGE_KEY_UP;

	return CODE_MESSAGE_KEY_NONE;
}

CHandlerKey* CHandle::getHandlerKey(CODE_MESSAGE_KEY codeKey)
{
	if (codeKey == CODE_MESSAGE_KEY_NONE)
		return 0;

	for (int i = 0; i < m_aHandlersKey.size(); ++i)
	{
		CHandlerKey *pHandlerKey = m_aHandlersKey[i];
		if (pHandlerKey->m_codeKey == codeKey)
			return pHandlerKey;
	}

	return 0;
}

//**************************************************************************

CHandlerEx* CHandle::getHandlerEx(CODE_MESSAGE_EX codeMsgEx)
{
	for (int i = 0; i < m_aHandlersEx.size(); ++i)
	{
		CHandlerEx *pHandlerEx = m_aHandlersEx[i];
		if (pHandlerEx->m_codeMsgEx == codeMsgEx)
			return pHandlerEx;
	}

	return 0;
}

CHandlerTimer* CHandle::getHandlerTimer(ID idTimer)
{
	for (int i = 0; i < m_aHandlersTime.size(); ++i)
	{
		CHandlerTimer *pHandlerTimer = m_aHandlersTime[i];
		if (pHandlerTimer->m_idTimer == idTimer)
			return pHandlerTimer;
	}

	return 0;
}

int CHandle::procCodeReturn(HANDLER_CODE_RETURN codeRet, LONG *pRet)
{
	if (codeRet == HANDLER_CODE_RETURN_DEFAULT)
		return HPROC_RET_DEFAULT;
	else if(codeRet == HANDLER_CODE_RETURN_SUPERCEDE)
	{
		if (pRet)
			*pRet = 0;

		return HPROC_RET_SUPERCEDE;
	}
	
	return HPROC_RET_DEFAULT;
}

//**************************************************************************

int CHandle::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet)
{
		GUI_TYPE_ELEMENT type = getElementType();

	if (isMsgMouse(uMsg))
	{
		//если сообщение пришло окну/групбоксу/тулбару тогда отправляем сообщение всем дочерним элементам и 
		//если хоть кто-то из них обработает тогда не пускаем обработчик дальше
		if (
			(type == GUI_TYPE_ELEMENT_WINDOW || type == GUI_TYPE_ELEMENT_GROUPBOX || type == GUI_TYPE_ELEMENT_TOOLBAR) &&
			SendMouseMsg2Children(hWnd, uMsg, wParam, lParam)
			)
			return HPROC_RET_DEFAULT;

		CHandlerMouse *pHandlerMouse = getHandlerMouse(getCodeMouseOfMsg(uMsg));
		if (!pHandlerMouse)
			return HPROC_RET_NOTCOM;

		CHandleMouseData oMouseData;
		oMouseData.m_oLocalPos.x = GET_X_LPARAM(lParam);
		oMouseData.m_oLocalPos.y = GET_Y_LPARAM(lParam);

		oMouseData.m_oGlobalPos = oMouseData.m_oLocalPos;
		MapWindowPoints(NULL, m_hWindow, &(oMouseData.m_oGlobalPos), 1);

		oMouseData.m_iScroll = 0;

		if (uMsg == WM_MOUSEWHEEL)
			oMouseData.m_iScroll = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

		HANDLER_CODE_RETURN codeRet = pHandlerMouse->m_fnHandler(dynamic_cast<IComponent*>(this), &oMouseData);
		return procCodeReturn(codeRet, pRet);
	}
	else if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
	{
		CHandlerKey *pHandlerKey = getHandlerKey(getCodeKeyOfMsg(uMsg));
		if (!pHandlerKey)
			return HPROC_RET_NOTCOM;

		CHandleKeyData oKeyData;
		oKeyData.m_key = m_aVkeys[wParam];

		if (uMsg == WM_KEYDOWN)
			oKeyData.m_isFirstDown = (MID(lParam, 30, 31) == 0 ? true : false);

		HANDLER_CODE_RETURN codeRet = pHandlerKey->m_fnHandler(dynamic_cast<IComponent*>(this), &oKeyData);
		return procCodeReturn(codeRet, pRet);
	}
	//если закрытие окна
	else if (uMsg == WM_CLOSE)
	{
		HANDLER_CODE_RETURN codeRet = procEx(CODE_MESSAGE_EX_WINDOW_CLOSE, &CHandlerDataWindow());
		
		if (pRet)
			*pRet = 0;

		if (codeRet == HANDLER_CODE_RETURN_DEFAULT)
		{
			IWindow *pWindow = dynamic_cast<IWindow*>(this);
			mem_release(pWindow);
			PostQuitMessage(0);
		}

		return HPROC_RET_SUPERCEDE;
	}
	//если изменение размеров
	else if (uMsg == WM_SIZE)
	{
		CHandlerDataWindow oDataExWindow;
		oDataExWindow.m_stateSize = GetWindowSizeStateByWparam(wParam); 
		oDataExWindow.m_oSizeNew.x = LOWORD(lParam);
		oDataExWindow.m_oSizeNew.y = HIWORD(lParam);
			
		HANDLER_CODE_RETURN codeRet = procEx(CODE_MESSAGE_EX_WINDOW_SIZE, &oDataExWindow);
		return procCodeReturn(codeRet, pRet);
	}
	//если перемещение объекта
	else if (uMsg == WM_MOVE)
	{
		CHandlerDataWindow oDataExWindow;
		oDataExWindow.m_oPosNew.x = (int)(short)LOWORD(lParam);
		oDataExWindow.m_oPosNew.y = (int)(short)HIWORD(lParam);

		HANDLER_CODE_RETURN codeRet = procEx(CODE_MESSAGE_EX_WINDOW_MOVE, &oDataExWindow);
		return procCodeReturn(codeRet, pRet);
	}
	//если была попытка вызова контекстного меню (клик ПКМ)
	else if (uMsg == WM_CONTEXTMENU)
	{
		HWND hWnd = (HWND)wParam;
		IComponent *pComponent = ((IComponent*)GetWindowLong(hWnd, GWL_USERDATA));

		if (!pComponent)
			return HPROC_RET_NOTCOM;

		CHandlerDataWindow oDataExWindow;
		oDataExWindow.m_oPosCMenu.x = GET_X_LPARAM(lParam);
		oDataExWindow.m_oPosCMenu.y = GET_Y_LPARAM(lParam);
		oDataExWindow.m_pTargetComponent4CMenu = pComponent;

		procEx(CODE_MESSAGE_EX_WINDOW_CALLCMENU, &oDataExWindow);
	}
	
	//если поступила команда клика/активации/выбора и текущий элемент это контейнер
	else if (uMsg == WM_COMMAND && m_isContainer)
	{
		int iNotification = HIWORD(wParam);
		HWND hElement = (HWND)(lParam);

		CHandle *pHandle = dynamic_cast<CHandle*>((IComponent*)GetWindowLong(hElement, GWL_USERDATA));
		
		//если удалось получить компонент, значит передаем ему исполнение
		if (pHandle)
		{
			//активация кнопки, отметка чекбокса, отметка радио
			if (iNotification == BN_CLICKED)
				pHandle->procEx(CODE_MESSAGE_EX_BUTTON_CLICK);

			//выбор в комбобоксе
			else if (iNotification == CBN_SELCHANGE)
				pHandle->procEx(CODE_MESSAGE_EX_COMBOBOX_SELCHANGE);

			//выбор в листбоксе
			else if (iNotification == CODE_MESSAGE_EX_LISTBOX_SELCHANGE)
				pHandle->procEx(CODE_MESSAGE_EX_EDIT_CHANGE);

			//изменение текста в edit
			else if (iNotification == EN_CHANGE)
				pHandle->procEx(CODE_MESSAGE_EX_LISTVIEW_CLICK);
			else
				return HPROC_RET_NOTCOM;
		}

		//иначе это команда для меню
		else
		{
			CWindow *pWindow = dynamic_cast<CWindow*>(this);
			int iId = LOWORD(wParam);
			CHandlerMenuData oData;
			oData.m_idSelected = iId;

			if (pWindow->getCurrCMenu())
			{
				CMenuPopup *pMenu = dynamic_cast<CMenuPopup*>(pWindow->getCurrCMenu());
				if (!pMenu)
					return HPROC_RET_NOTCOM;

				pMenu->proc(CODE_MSG_MENU_SELECT, &oData);
				pMenu->proc(CODE_MSG_MENU_CLOSE, &oData);
				pWindow->setCurrCMenu(0);
			}
			else
			{
				CMenuWindow *pMenu = dynamic_cast<CMenuWindow*>(pWindow->getMenu());
				if (!pMenu)
					return HPROC_RET_NOTCOM;

				pMenu->proc(CODE_MSG_MENU_SELECT, &oData);
				pMenu->proc(CODE_MSG_MENU_CLOSE, &oData);
			}

			return HPROC_RET_DEFAULT;
		}
	}
	//если есть нотификация от дочерних элементов (listview)
	else if (uMsg == WM_NOTIFY && m_isContainer)
	{
		NMHDR *pData = (NMHDR*)lParam;

		if (!pData)
			return HPROC_RET_NOTCOM;

		CHandle *pHandle = dynamic_cast<CHandle*>((IComponent*)GetWindowLong(pData->hwndFrom, GWL_USERDATA));
		if (!pHandle)
			return HPROC_RET_NOTCOM;

		//клик по listview
		if (pData->code == NM_CLICK)
		{
			pHandle->procEx(CODE_MESSAGE_EX_LISTVIEW_CLICK);
			return HPROC_RET_DEFAULT;
		}
		else
			return HPROC_RET_NOTCOM;
	}
	//если вызвана активация главного меню (нажатие на один из пунктов горизонтального меню)
	else if (uMsg == WM_INITMENU)
	{
		HMENU hMenu = (HMENU)wParam;
		LONG lUD = GetUserData4Menu(hMenu);
		if (lUD == 0)
			return HPROC_RET_NOTCOM;

		CWindow *pWindow = dynamic_cast<CWindow*>(this);
		CMenuBase *pMenu = dynamic_cast<CMenuBase*>((IMenuBase*)lUD);

		pWindow->setCurrCMenu(0);
		
		if (pMenu)
		{
			pMenu->proc(CODE_MSG_MENU_OPEN, &CHandlerMenuData());
			return HPROC_RET_DEFAULT;
		}
		else
			return HPROC_RET_NOTCOM;
	}
	
	//если была инициализация контекстного меню
	else if (uMsg == WM_INITMENUPOPUP)
	{
		HMENU hMenu = (HMENU)wParam;
		LONG lUD = GetUserData4Menu(hMenu);
		if (lUD == 0)
			return HPROC_RET_NOTCOM;

		CWindow *pWindow = dynamic_cast<CWindow*>(this);
		CMenuBase *pMenu = dynamic_cast<CMenuBase*>((IMenuBase*)lUD);

		pWindow->setCurrCMenu(dynamic_cast<IMenuPopup*>(pMenu));
		
		if (pMenu)
		{
			pMenu->proc(CODE_MSG_MENU_OPEN, &CHandlerMenuData());
			return HPROC_RET_DEFAULT;
		}
		else
			return HPROC_RET_NOTCOM;
	}

	//если сообщение таймера
	else if (uMsg == WM_TIMER)
	{
		ID idTimer = wParam;

		CHandlerTimer *pHandlerTimer = getHandlerTimer(idTimer);

		if (pHandlerTimer)
		{
			if (pHandlerTimer->m_fnHandler)
				pHandlerTimer->m_fnHandler(dynamic_cast<IComponent*>(this));

			return HPROC_RET_SUPERCEDE;
		}
	}

	//
	else if (uMsg == WM_SETCURSOR)
	{
		CComponent *pComponent = dynamic_cast<CComponent*>(this);

		if (pComponent && pComponent->getCursor() != CURSOR_NULL)
		{
			SetCursor(pComponent->getHCursor());
			*pRet = 1;
			return 1;
		}
	}

	return -1;
}

HANDLER_CODE_RETURN CHandle::procEx(CODE_MESSAGE_EX codeMsgEx, void *prt)
{
	CHandlerEx *pHandlerEx = getHandlerEx(codeMsgEx);

	if (pHandlerEx)
	{
		if (
			codeMsgEx == CODE_MESSAGE_EX_WINDOW_SIZE || 
			codeMsgEx == CODE_MESSAGE_EX_WINDOW_CLOSE ||
			codeMsgEx == CODE_MESSAGE_EX_WINDOW_MOVE ||
			codeMsgEx == CODE_MESSAGE_EX_WINDOW_CALLCMENU
			)
			return ((HandlerExWindow)(pHandlerEx->m_pHandler))(dynamic_cast<IComponent*>(this), (CHandlerDataWindow*)prt);
		else
			return ((HandlerExCommon)(pHandlerEx->m_pHandler))(dynamic_cast<IComponent*>(this));
	}

	return HANDLER_CODE_RETURN_DEFAULT;
}