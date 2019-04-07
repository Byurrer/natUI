
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "window.h"

CWindow::CWindow(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent, WND_STYLE style, bool isTopMost)
{
	String sClass = g_sWndClassName + g_iWndNum;
	++g_iWndNum;
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));

	if (style < WND_STYLE_COUNT)
		m_style = style;
	else
		m_style = WND_STYLE_DEFAULT;

	/*wc.style = CS_HREDRAW | CS_VREDRAW | g_aWndStyle[m_style];*/
	wc.lpfnWndProc = DefWindowProc; 
	wc.hInstance = GetModuleHandle(0);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = sClass.c_str();

	m_isTopMost = isTopMost;

	if(!RegisterClass(&wc)) 
	{
		MessageBox(0, "Ошибка при регистрации класса окна!", sClass.c_str(), 0);
	}

	if (iWidth < 0 && iHeight < 0)
	{
		RECT oRect = { iX, iY, abs(iWidth) + iX, abs(iHeight) + iY };
		AdjustWindowRect(&oRect, g_aWndStyle[m_style] | WND_STD_STYLE, 0);

		iWidth = oRect.right - oRect.left;
		iHeight = oRect.bottom - oRect.top;
	}

	iWidth = abs(iWidth);
	iHeight = abs(iHeight);
		
	m_hWindow = CreateWindowEx(
		(isTopMost ? WS_EX_TOPMOST : 0),
		sClass.c_str(),
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) |g_aWndStyle[m_style] | WND_STD_STYLE,
		iX, iY, iWidth, iHeight,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0); 

	if (!m_hWindow)
	{
		MessageBox(0, "Ошибка создания окна!!!", szCaption, 0);
	}

	initControl(GUI_TYPE_ELEMENT_WINDOW, pParent, true);
	SetWindowLong(m_hWindow, GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();

	StdHandlerInitMsg(this);

	/*ShowWindow(m_hWindow, SW_SHOW);
	UpdateWindow(m_hWindow);*/

	m_pMenu = 0;
}

CWindow::~CWindow()
{

}


void CWindow::setStyle(WND_STYLE style)
{
	if (style < WND_STYLE_COUNT)
		m_style = style;
	else
		m_style = WND_STYLE_DEFAULT;

	initStyle(g_aWndStyle[m_style] | WND_STD_STYLE);
}

WND_STYLE CWindow::getStyle()
{
	return m_style;
}

void CWindow::setTopMost(bool isTopMost)
{
	SetWindowPos(m_hWindow, (isTopMost ? HWND_TOPMOST : HWND_NOTOPMOST), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_isTopMost = isTopMost;
}

bool CWindow::getTopMost()
{
	return m_isTopMost;
}

bool CWindow::setAlphaBlend(bool bf)
{
	return this->modifyExStyle(bf ? WS_EX_LAYERED : 0,!bf ? WS_EX_LAYERED : 0);
}

bool CWindow::getAlphaBlend()
{
	long style = GetWindowLong(m_hWindow, GWL_EXSTYLE);
	return (style & WS_EX_LAYERED);
}

bool CWindow::setAlpha(float fAlpha)
{
	return SetLayeredWindowAttributes(m_hWindow, 0, (BYTE)(fAlpha * 255.f), LWA_ALPHA);
}

float CWindow::getAlpha()
{
	WORD alpha = 0;
	if (!GetLayeredWindowAttributes(m_hWindow, 0, (BYTE*)&alpha, 0))
			return -1;
	return float(alpha) / 255.f;
}

bool CWindow::setColorBrush(UINT uColor)
{
	DWORD color2 = SetClassLong(m_hWindow, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(uColor));
	InvalidateRect(m_hWindow, 0, TRUE);
	return color2 > 0 ? true : false;
}

UINT CWindow::getColorBrush()
{
	HBRUSH hbrush = (HBRUSH)GetClassLong(m_hWindow, GCL_HBRBACKGROUND);
	LOGBRUSH lbr;
	ZeroMemory(&lbr,sizeof(LOGBRUSH));
	GetObject(hbrush,sizeof(LOGBRUSH),&lbr);
	return (lbr.lbColor);
}

NativeHandle CWindow::getBrush()
{
	//return GetClassLongPtr(m_hWindow,GCLP_HBRBACKGROUND);
	return (HBRUSH)GetClassLong(m_hWindow, GCL_HBRBACKGROUND);
}

bool CWindow::setMenu(IMenuWindow *pMenu)
{
	if (pMenu)
	{
		m_pMenu = pMenu;
		HMENU hMenu = (HMENU)(pMenu->getNativeHandle());
		BOOL iRet = SetMenu(m_hWindow, hMenu);
		return iRet;
	}

	return false;
}

IMenuWindow* CWindow::getMenu()
{
	return m_pMenu;
}

bool CWindow::setCurrCMenu(IMenuPopup *pCMenu)
{
	bool wasIt = (m_pCMenu ? true : false);

	m_pCMenu = pCMenu;

	return wasIt;
}

IMenuPopup* CWindow::getCurrCMenu()
{
	return m_pCMenu;
}

//##########################################################################

void CWindow::addHandlerSize(HandlerExWindow fnHandler)
{
	addHandlerEx(CODE_MESSAGE_EX_WINDOW_SIZE, fnHandler);
}

void CWindow::addHandlerCallCMenu(HandlerExWindow fnHandler)
{
	addHandlerEx(CODE_MESSAGE_EX_WINDOW_CALLCMENU, fnHandler);
}

void CWindow::addHandlerExit(HandlerExWindow fnHandler)
{
	addHandlerEx(CODE_MESSAGE_EX_WINDOW_CLOSE, fnHandler);
}