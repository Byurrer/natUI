
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_WND_H
#define __BASE_WND_H

#include "base.h"
#include "menu.h"
#include "common/string.h"

//##########################################################################

static String g_sWndClassName = "WndClassName";
static int g_iWndNum = 0;

//##########################################################################

#define WND_STD_STYLE WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_HREDRAW | CS_VREDRAW

static UINT g_aWndStyle[] = {
	/*WND_STYLE_DEFAULT =>*/ 
	WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,
	/*WND_STYLE_AREA =>*/ 
	0,
	/*WND_STYLE_AREA_BORDER =>*/ 
	WS_BORDER,
	/*WND_STYLE_AREA_BORDER_SUNKEN =>*/ 
	SS_SUNKEN,
	/*WND_STYLE_DIALOG =>*/ 
	WS_DLGFRAME | WS_SYSMENU | WS_CAPTION,
	/*WND_STYLE_DIALOG_MINIMIZE =>*/ 
	WS_DLGFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,
	/*WND_STYLE_MINDIALOG =>*/ 
	WS_CAPTION | WS_SYSMENU | WS_OVERLAPPED
};

//##########################################################################

//! 
class CWindow : public CTextual, public virtual IWindow
{
public:
	CWindow(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, WND_STYLE style = WND_STYLE_DEFAULT, bool isTopMost=false);
	~CWindow();

	void setStyle(WND_STYLE style);
	WND_STYLE getStyle();

	void setTopMost(bool isTopMost);
	bool getTopMost();

	bool setColorBrush(UINT uColor);
	UINT getColorBrush();
	NativeHandle getBrush();

	bool setAlpha(float fAlpha);
	float getAlpha();
	bool setAlphaBlend(bool isBlend);
	bool getAlphaBlend();

	bool setMenu(IMenuWindow *pMenu);
	IMenuWindow* getMenu();

	bool setCurrCMenu(IMenuPopup *pCMenu);
	IMenuPopup* getCurrCMenu();

	void addHandlerSize(HandlerExWindow fnHandler);
	void addHandlerCallCMenu(HandlerExWindow fnHandler);
	void addHandlerExit(HandlerExWindow fnHandler);

protected:
	WND_STYLE m_style;
	IMenuWindow *m_pMenu;
	IMenuPopup *m_pCMenu;
	bool m_isTopMost;
};

#endif