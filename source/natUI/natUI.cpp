
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

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

#include "manager.h"

#include <commctrl.h>
#include <Winuser.h>
#include <stdio.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Comctl32.lib")

//##########################################################################

CManager *g_pManager = 0;

NATUI_API IManager* ManagerInit()
{
	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);

	if (!g_pManager)
		g_pManager = new CManager();

	return g_pManager;
}

NATUI_API void ManagerDestroy()
{
	mem_release(g_pManager);
}

