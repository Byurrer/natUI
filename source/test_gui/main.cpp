
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2019
See the license in LICENSE
******************************************************/

//#include <vld.h> 
#include <natUI/natUI.h>
#include <common/string.h>
#include <common/string_utils.h>
#include <common/array.h>
#include <windows.h>
#include "resource.h"
#include <shellapi.h>

#pragma comment(lib, "natui_d.lib")


HANDLER_CODE_RETURN TestMouseMove(IComponent *pComponent, const CHandleMouseData *pMouseData)
{
	//MessageBox(0,0,0,0);
	return HANDLER_CODE_RETURN_DEFAULT;
}

HANDLER_CODE_RETURN TestButtonClick(IComponent *pComponent)
{
	//MessageBox(0,0,0,0);
	return HANDLER_CODE_RETURN_DEFAULT;
}

HANDLER_CODE_RETURN TestKey(IComponent *pComponent, const CHandleKeyData *pKeyData)
{
	//MessageBox(0,0,0,0);
	if (pKeyData->m_isFirstDown == false)
		int qwerty = 0;
	return HANDLER_CODE_RETURN_DEFAULT;
}

IWindow *pWnd = 0;
IButton *pButton = 0;
IStatic *pStatic = 0;
IMenuWindow *pMenu = 0;
IMenuPopup *pMenuPopup = 0;

HANDLER_CODE_RETURN TestSize(IComponent *pComponent, const CHandlerDataWindow *pDataWindow)
{
	pStatic->setText(String(pDataWindow->m_stateSize).c_str());
	//MessageBox(0, 0, 0, 0);
	return HANDLER_CODE_RETURN_DEFAULT;
}

HANDLER_CODE_RETURN TestInitMMenu(IComponent *pComponent, const CHandlerDataWindow *pDataWindow)
{
	pStatic->setText("TestInitMMenu");
	//MessageBox(0, 0, 0, 0);
	return HANDLER_CODE_RETURN_DEFAULT;
}

HANDLER_CODE_RETURN TestInitCMenu(IComponent *pComponent, const CHandlerDataWindow *pDataWindow)
{
	pStatic->setText("TestInitCMenu");
	//MessageBox(0, 0, 0, 0);
	return HANDLER_CODE_RETURN_DEFAULT;
}

HANDLER_CODE_RETURN TestCallCMenu(IComponent *pComponent, const CHandlerDataWindow *pDataWindow)
{
	pStatic->setText("TestCallCMenu");
	pMenuPopup->track(pWnd, 0, 0);
	//MessageBox(0, 0, 0, 0);
	return HANDLER_CODE_RETURN_DEFAULT;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	pWnd = GUI_NewWnd("Window", WND_STYLE_DEFAULT, 0, 10, 10, 300, 300);
	pWnd->setVisible(true);
	//pWnd->setStyle(SXGUI_WND_STYLE_MINDIALOG);
	pWnd->addHandlerSize(TestSize);
	pWnd->addHandlerCMenu(TestCallCMenu);
	pWnd->addHandlerKey(CODE_MESSAGE_KEY_DOWN, TestKey);

	NewGroupBox("group box", 50, 50, 100, 100, pWnd);

	//pMenuPopup = SXGUICrPopupMenuEx(IDR_MENU1, 1);
	pMenuPopup = SXGUICrPopupMenu();
	pMenuPopup->insertItem(0, "p1", 98, 0);
	pMenuPopup->insertItem(0, "p2", 99, 0);
	pMenuPopup->insertPopupItem(2, "p3", 100, -1);
	pMenuPopup->insertItem(0, "p3", 101, 100);
	pMenuPopup->setEnableItem(98, false);
	pMenuPopup->setEnableItem(99, false);
	

	pButton = GUI_NewButton("button", 10, 10, 100, 20, pWnd);
	pButton->setVisible(true);
	pButton->addHandlerActivated(TestButtonClick);
	pButton->addHandlerMouse(CODE_MESSAGE_MOUSE_LDOWN, TestMouseMove);

	pStatic = GUI_NewStatic("--", 100, 100, 100, 20, pWnd);

	pMenu = GUI_NewMenuWindowRes(IDR_MENU1);
	pWnd->setMenu(pMenu);

	MSG msg = { 0 };
	::ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	return msg.message;
}



