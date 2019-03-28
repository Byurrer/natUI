
#include "base_component.h"

CComponent::CComponent()
{
	m_pHint = 0;

	m_aFollowParentSide[SIDE_TOP] = false;
	m_aFollowParentSide[SIDE_BOTTOM] = false;
	m_aFollowParentSide[SIDE_RIGHT] = false;
	m_aFollowParentSide[SIDE_LEFT] = false;

	m_rcParentScreen.top = m_rcParentScreen.bottom = m_rcParentScreen.left = m_rcParentScreen.right = 0;
	//m_isTransparentTextBk = true;

	m_aStrethSide[SIDE_TOP] = true;
	m_aStrethSide[SIDE_BOTTOM] = true;
	m_aStrethSide[SIDE_RIGHT] = true;
	m_aStrethSide[SIDE_LEFT] = true;

	m_iMinSizeWidth = m_iMinSizeHeight = 0;
	//Font = 0;
}

CComponent::~CComponent()
{
	mem_delete(m_pHint);
}

void CComponent::initComponent()
{
	UINT uColorBrush = GetDCBrushColor(GetDC(m_hWindow));

	m_uColorBrush = uColorBrush;

	m_hBrush = CreateSolidBrush(m_uColorBrush);

	GetWindowRect(getParentHWND(), &m_rcParentScreen);

	GetWindowRect(m_hWindow, &m_rcWinScreen);
	MapWindowPoints(getParentHWND(), HWND_DESKTOP, (LPPOINT)&m_rcWinScreen, 2);

	RECT rc;
	GetWindowRect(m_hWindow, &rc);

	m_rcOffsetParent.top = m_rcOffsetParent.bottom = m_rcOffsetParent.left = m_rcOffsetParent.right = 0;

	//MinSizeX = rc.right - rc.left;
	//MinSizeY = rc.bottom - rc.top;

	//HFONT HandleFont;
	//SystemParametersInfo(SPI_GETICONTITLELOGFONT, 0, &HandleFont, 0);

	HFONT HandleFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(
		m_hWindow,
		WM_SETFONT,
		WPARAM(HandleFont),
		0);
	DeleteObject(HandleFont);
	//Font = new SXFont();
	//SetFont(Font);
}

bool CComponent::getEnable()
{
	return ((IsWindowEnabled(m_hWindow) == 0) ? false : true);
}

void CComponent::setEnable(bool bf)
{
	EnableWindow(m_hWindow, (bf ? 1 : 0));
}

bool CComponent::setWinRect(const RECT* rect, bool alignment_screen_space)
{
	RECT wrect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	UINT width_screen = wrect.right;
	UINT heigth_screen = wrect.bottom;

	//MessageBox(0,ToPointChar(ToString(width_screen) + "|" + ToString(heigth_screen)),0,0);

	WORD x = rect->left;
	WORD y = rect->top;
	WORD width = rect->right - rect->left;
	WORD heigth = rect->bottom - rect->top;
	//MessageBox(0,ToPointChar(ToString(width) + "|" + ToString(heigth)),"wh",0);
	if (alignment_screen_space)
	{
		x = x < width_screen ? x : width_screen;
		y = y < heigth_screen ? y : heigth_screen;
		//MessageBox(0,ToPointChar(ToString(rect->right) + "|" + ToString(rect->bottom)),"wh",0);
		width = rect->right <= width_screen ? width : width_screen - x;
		heigth = rect->bottom <= heigth_screen ? heigth : heigth_screen - y;

		/*if(x < 0)
		x = 0;
		if(y < 0)
		y = 0;*/
	}
	//MessageBox(0,ToPointChar(ToString(width) + "|" + ToString(heigth)),"wh",0);
	BOOL bf = MoveWindow(m_hWindow, x, y, width, heigth, true);
	return bf == TRUE ? true : false;
}

void CComponent::getWinRect(RECT* rect)
{
	GetWindowRect(m_hWindow, rect);
}

bool CComponent::setClientRect(const RECT* rect, bool alignment_screen_space)
{
	RECT wrect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	long width_screen = wrect.right;
	long heigth_screen = wrect.bottom;

	//MessageBox(0,ToPointChar(ToString(width_screen) + "|" + ToString(heigth_screen)),0,0);

	long x = rect->left;
	long y = rect->top;
	long width = rect->right - rect->left;
	long heigth = rect->bottom - rect->top;
	//MessageBox(0,ToPointChar(ToString(width) + "|" + ToString(heigth)),"wh",0);
	if (alignment_screen_space)
	{
		x = x < width_screen ? x : width_screen;
		y = y < heigth_screen ? y : heigth_screen;
		//MessageBox(0,ToPointChar(ToString(rect->right) + "|" + ToString(rect->bottom)),"wh",0);
		width = rect->right <= width_screen ? width : width_screen - x;
		heigth = rect->bottom <= heigth_screen ? heigth : heigth_screen - y;
	}
	//MessageBox(0,ToPointChar(ToString(width) + "|" + ToString(heigth)),"wh",0);
	BOOL bf = MoveWindow(m_hWindow, x, y, width, heigth, TRUE);
	/*RECT* qwerr = GetClientRect();
	if(x != qwerr->left || y != qwerr->top || width != qwerr->right - qwerr->left || heigth != qwerr->bottom - qwerr->top)
	MessageBox(0,0,0,0);*/
	return bf == TRUE ? true : false;
}

void CComponent::getClientRect(RECT* rect)
{
	GetWindowRect(m_hWindow, rect);
	MapWindowPoints(NULL, getParentHWND(), (LPPOINT)rect, 2);
}

bool CComponent::modifyStyle(long style_add, long style_del)
{

	if (style_add)
	{
		if (!SetWindowLong(m_hWindow, GWL_STYLE, GetWindowLong(m_hWindow, GWL_STYLE) | style_add))
			return false;
	}

	if (style_del)
	{
		if (!SetWindowLong(m_hWindow, GWL_STYLE, GetWindowLong(m_hWindow, GWL_STYLE)&~style_del))
			return false;
	}
	return true;
}

void CComponent::initStyle(UINT uStyle)
{
	SetWindowLong(m_hWindow, GWL_STYLE, uStyle);
	SetWindowPos(m_hWindow, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

bool CComponent::modifyExStyle(long style_add, long style_del)
{

	if (style_add)
	{
		if (!SetWindowLong(m_hWindow, GWL_EXSTYLE, GetWindowLong(m_hWindow, GWL_EXSTYLE) | style_add))
			return false;
	}

	if (style_del)
	{
		if (!SetWindowLong(m_hWindow, GWL_EXSTYLE, GetWindowLong(m_hWindow, GWL_EXSTYLE)&~style_del))
			return false;
	}
	return true;
}

void CComponent::setShowHint(bool bf)
{
	if (m_pHint != 0)
		m_pHint->setVisible(bf);
	else
	{
		m_pHint = new CHint(this);
		m_pHint->setVisible(bf);
	}
}

bool CComponent::getShowHint()
{
	if (m_pHint != 0)
		return m_pHint->getVisible();
	return false;
}

void CComponent::setHintText(const char* text)
{
	if (m_pHint == 0)
		m_pHint = new CHint(this);

	m_pHint->setText(text);
}

const char* CComponent::getHintText()
{
	if (m_pHint != 0)
		return m_pHint->getText();

	return 0;
}

void CComponent::updateSize()
{
	RECT oRect;
	RECT oWinRect;
	BOOL bf = GetWindowRect(m_hWindow, &oRect);

	GetWindowRect(m_hWindow, &oWinRect);
	//MapWindowPoints(m_hParent, HWND_DESKTOP, (LPPOINT)&oWinRect, 2);

	RECT oWinRectParent;
	GetWindowRect(getParentHWND(), &oWinRectParent);

	//трансляция координат в пространство родителя
	//MapWindowPoints(NULL, m_hParent, (LPPOINT)&rect, 2);

	//если не имзеняет память, то значения за пределаеми (-30000, 30000) сигнализируют о сворачивании окна, в этом случае обработка не нужна
	if (abs(m_rcOffsetParent.left) > 30000 || abs(m_rcOffsetParent.right) > 30000 || abs(m_rcOffsetParent.top) > 30000 || abs(m_rcOffsetParent.bottom) > 30000)
		return;

	//смещение по всем направлениям
	RECT oOffset;
	oOffset.left = m_rcOffsetParent.left ? m_rcOffsetParent.left : oWinRectParent.left - m_rcParentScreen.left;
	oOffset.right = m_rcOffsetParent.right ? m_rcOffsetParent.right : oWinRectParent.right - m_rcParentScreen.right;
	oOffset.top = m_rcOffsetParent.top ? m_rcOffsetParent.top : oWinRectParent.top - m_rcParentScreen.top;
	oOffset.bottom = m_rcOffsetParent.bottom ? m_rcOffsetParent.bottom : oWinRectParent.bottom - m_rcParentScreen.bottom;


	if (m_aFollowParentSide[SIDE_LEFT]) //oRect.left
	{
		if (m_aFollowParentSide[SIDE_RIGHT])
			oRect.right -= oOffset.left;
		/*else
		rect.right += offset.left;*/
	}
	else
	{
		oRect.left = oRect.left - oOffset.left;
		oRect.right -= oOffset.left;
	}

	if (m_aFollowParentSide[SIDE_TOP]) //oRect.top
	{
		//oRect.top = oRect.top + offset.top;
		if (m_aFollowParentSide[SIDE_BOTTOM])
			oRect.bottom -= oOffset.top;
	}
	else
	{
		oRect.top = oRect.top - oOffset.top;
		oRect.bottom -= oOffset.top;
	}

	if (m_aFollowParentSide[SIDE_RIGHT]) //oRect.right
	{
		oRect.right = oRect.right + oOffset.right;
		if (!m_aFollowParentSide[SIDE_LEFT]) //oRect.left
			oRect.left += oOffset.right;
	}

	if (m_aFollowParentSide[SIDE_BOTTOM]) //oRect.bottom
	{

		oRect.bottom = oRect.bottom + oOffset.bottom;
		if (!m_aFollowParentSide[SIDE_TOP]) //oRect.top
			oRect.top += oOffset.bottom;
	}

	MapWindowPoints(NULL, getParentHWND(), (LPPOINT)&oRect, 2);

	bf = MoveWindow(m_hWindow, oRect.left, oRect.top, oRect.right - oRect.left, oRect.bottom - oRect.top, true);
	//SetWinRect(&oRect,true);
	GetWindowRect(getParentHWND(), &m_rcParentScreen);
	GetWindowRect(m_hWindow, &m_rcWinScreen);

	m_rcOffsetParent.top = m_rcOffsetParent.bottom = m_rcOffsetParent.left = m_rcOffsetParent.right = 0;

	/*DWORD err = GetLastError();
	int qweerty = 0;*/
}

void CComponent::updateRect()
{
	RECT oRect;
	GetWindowRect(getParentHWND(), &oRect);
	m_rcOffsetParent.top = oRect.top - m_rcParentScreen.top;
	m_rcOffsetParent.left = oRect.left - m_rcParentScreen.left;
	m_rcOffsetParent.bottom = oRect.bottom - m_rcParentScreen.bottom;
	m_rcOffsetParent.right = oRect.right - m_rcParentScreen.right;

	GetWindowRect(getParentHWND(), &m_rcParentScreen);
}


bool CComponent::setColorBrush(UINT uColor)
{
	m_uColorBrush = uColor;

	DeleteObject(m_hBrush);
	m_hBrush = CreateSolidBrush(m_uColorBrush);
	InvalidateRect(m_hWindow, 0, 1);
	return true;
}

UINT CComponent::getColorBrush()
{
	return m_uColorBrush;
}

NativeHandle CComponent::getBrush()
{
	return m_hBrush;
}

void CComponent::addHandlerSys(HandlerSysFunc Handler, UINT uMsg, bool needPassOn)
{
	CHandlerSysData oHandler;
	oHandler.m_fnHandler = Handler;
	oHandler.m_uMsg = uMsg;
	oHandler.m_needPassOn = needPassOn;

	m_aHandlers.push_back(oHandler);
}

bool CComponent::procHandlerSys(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet)
{
	bool isFound = false;
	for (int i = 0, il = m_aHandlers.size(); i < il; ++i)
	{
		if (m_aHandlers[i].m_uMsg == uMsg)
		{
			LONG lRet = (m_aHandlers[i].m_fnHandler)(hWnd, uMsg, wParam, lParam);
			if (pRet)
				*pRet = lRet;

			isFound = true;
			break;
		}
	}

	return isFound;
}

void CComponent::setMinSize(UINT uMinWidth, UINT uMinHeght)
{
	m_iMinSizeWidth = uMinWidth;
	m_iMinSizeHeight = uMinHeght;
}

UINT CComponent::getMinWidth()
{
	return m_iMinSizeWidth;
}

UINT CComponent::getMinHeight()
{
	return m_iMinSizeHeight;
}

void CComponent::setStretchSides(bool canTop, bool canBottom, bool canRight, bool canLeft)
{
	m_aStrethSide[SIDE_TOP] = canTop;
	m_aStrethSide[SIDE_BOTTOM] = canBottom;
	m_aStrethSide[SIDE_RIGHT] = canRight;
	m_aStrethSide[SIDE_LEFT] = canLeft;
}

void CComponent::setStretchSide(SIDE side, bool can)
{
	m_aStrethSide[side] = can;
}

bool CComponent::getStretchSide(SIDE side)
{
	return m_aStrethSide[side];
}


void CComponent::setFollowParentSides(bool canTop, bool canBottom, bool canRight, bool canLeft)
{
	m_aFollowParentSide[SIDE_TOP] = canTop;
	m_aFollowParentSide[SIDE_BOTTOM] = canBottom;
	m_aFollowParentSide[SIDE_RIGHT] = canRight;
	m_aFollowParentSide[SIDE_LEFT] = canLeft;
}

void CComponent::setFollowParentSide(SIDE side, bool can)
{
	m_aFollowParentSide[side] = can;
}

bool CComponent::getFollowParentSide(SIDE side)
{
	return m_aFollowParentSide[side];
}