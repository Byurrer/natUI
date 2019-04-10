
#include "base_component.h"

CComponent::CComponent()
{
	m_pHint = 0;

	m_aFollowParentSide[SIDE_TOP] = false;
	m_aFollowParentSide[SIDE_BOTTOM] = false;
	m_aFollowParentSide[SIDE_RIGHT] = false;
	m_aFollowParentSide[SIDE_LEFT] = false;

	m_rcParentScreen.top = m_rcParentScreen.bottom = m_rcParentScreen.left = m_rcParentScreen.right = 0;
	
	m_aStretchSide[SIDE_TOP] = true;
	m_aStretchSide[SIDE_BOTTOM] = true;
	m_aStretchSide[SIDE_RIGHT] = true;
	m_aStretchSide[SIDE_LEFT] = true;

	m_iMinSizeWidth = m_iMinSizeHeight = 0;
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

bool CComponent::setWinRect(const RECT *pRect, bool isBoundScreen)
{
	RECT oRectScreen;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &oRectScreen, 0);
	int iWidthScreen = oRectScreen.right;
	int iHeigthScreen = oRectScreen.bottom;

	int iX = pRect->left;
	int iY = pRect->top;
	int iWidth = pRect->right - pRect->left;
	int iHeigth = pRect->bottom - pRect->top;

	if (isBoundScreen)
	{
		iX = (iX < iWidthScreen ? iX : iWidthScreen);
		iY = (iX < iHeigthScreen ? iY : iHeigthScreen);

		iWidth = (pRect->right <= iWidthScreen ? iWidth : iWidthScreen - iX);
		iHeigth = (pRect->bottom <= iHeigthScreen ? iHeigth : iHeigthScreen - iY);
	}

	return ((bool)MoveWindow(m_hWindow, iX, iY, iWidth, iHeigth, TRUE));
}

void CComponent::getWinRect(RECT *pRect)
{
	GetWindowRect(m_hWindow, pRect);
}

bool CComponent::setClientRect(const RECT *pRect, bool isBoundScreen)
{
	RECT oRectScreen;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &oRectScreen, 0);
	int iWidthScreen = oRectScreen.right;
	int iHeigthScreen = oRectScreen.bottom;

	RECT pRect2 = *pRect;

	//используется ли меню
	bool useMenu = false;
	if (m_typeElement == GUI_TYPE_ELEMENT_WINDOW && GetMenu(m_hParent))
		useMenu = true;

	//выравнивание rect по размерам в соответсвии со стилем
	AdjustWindowRect(&pRect2, (DWORD)GetWindowLong(m_hParent, GWL_STYLE), useMenu);

	int iX = pRect2.left;
	int iY = pRect2.top;
	int iWidth = pRect2.right - pRect2.left;
	int iHeigth = pRect2.bottom - pRect2.top;
	
	if (isBoundScreen && m_typeElement == GUI_TYPE_ELEMENT_WINDOW)
	{
		iX = (iX < iWidthScreen ? iX : iWidthScreen);
		iY = (iX < iHeigthScreen ? iY : iHeigthScreen);

		iWidth = (pRect2.right <= iWidthScreen ? iWidth : iWidthScreen - iX);
		iHeigth = (pRect2.bottom <= iHeigthScreen ? iHeigth : iHeigthScreen - iY);
	}
	
	return ((bool)MoveWindow(m_hWindow, iX, iY, iWidth, iHeigth, TRUE));
}

void CComponent::getClientRect(RECT *pRect)
{
	GetClientRect(m_hWindow, pRect);
	MapWindowPoints(m_hWindow, 0, (LPPOINT)pRect, 1);
}


void CComponent::getPos(POINT *pPoint)
{
	RECT oRect;
	getWinRect(&oRect);
	pPoint->x = oRect.left;
	pPoint->y = oRect.top;
}

void CComponent::getSize(POINT *pSize)
{
	RECT oRect;
	getWinRect(&oRect);
	pSize->x = oRect.right - oRect.left;
	pSize->y = oRect.bottom - oRect.top;
}

void CComponent::setPos(const POINT *pPoint)
{
	POINT oSize;
	getSize(&oSize);

	RECT oNewRect;
	oNewRect.left = pPoint->x;
	oNewRect.top = pPoint->y;
	oNewRect.right = oNewRect.left + oSize.x;
	oNewRect.bottom = oNewRect.top + oSize.y;
	setWinRect(&oNewRect, false);
}

void CComponent::setSize(const POINT *pSize)
{
	POINT oPos;
	getPos(&oPos);

	RECT oNewRect;
	oNewRect.left = oPos.x;
	oNewRect.top = oPos.y;
	oNewRect.right = oNewRect.left + abs(pSize->x);
	oNewRect.bottom = oNewRect.top + abs(pSize->y);

	if (pSize->x < 0 && pSize->y < 0)
	{
		AdjustWindowRect(&oNewRect, GetWindowStyle(m_hWindow), 0);
	}

	setWinRect(&oNewRect, false);
}

void CComponent::adjustPos(int iAdjustX, int iAdjustY)
{
	RECT oWinRect;
	getWinRect(&oWinRect);

	int iCurrWidth = oWinRect.right - oWinRect.left;
	int iCurrHeight = oWinRect.bottom - oWinRect.top;

	RECT oParentRect;

	IComponent *pParent = (IComponent*)GetWindowLong(m_hParent, GWL_USERDATA);
	if (pParent)
		pParent->getClientRect(&oParentRect);
	else
		SystemParametersInfo(SPI_GETWORKAREA, 0, &oParentRect, 0);

	int iParentWidth = oParentRect.right - oParentRect.left;
	int iParentHeight = oParentRect.bottom - oParentRect.top;

	int iX, iY;
	iX = iY = 0;

	if (iAdjustX == ADJUSTPOS_X_LEFT)
		iX = 0;
	else if (iAdjustX == ADJUSTPOS_X_CENTER)
		iX = (iParentWidth / 2) - (iCurrWidth / 2);
	else if (iAdjustX == ADJUSTPOS_X_RIGHT)
		iX = iParentWidth - iCurrWidth;

	if (iAdjustY == ADJUSTPOS_Y_TOP)
		iY = 0;
	else if (iAdjustY == ADJUSTPOS_Y_CENTER)
		iY = (iParentHeight / 2) - (iCurrHeight / 2);
	else if (iAdjustY == ADJUSTPOS_Y_BOTTOM)
		iY = iParentHeight - iCurrHeight;

	MoveWindow(m_hWindow, iX, iY, iCurrWidth, iCurrHeight, TRUE);
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

	SetWindowPos(m_hWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
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

	if (m_hBrush)
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
	m_aStretchSide[SIDE_TOP] = canTop;
	m_aStretchSide[SIDE_BOTTOM] = canBottom;
	m_aStretchSide[SIDE_RIGHT] = canRight;
	m_aStretchSide[SIDE_LEFT] = canLeft;
}

void CComponent::setStretchSide(SIDE side, bool can)
{
	m_aStretchSide[side] = can;
}

bool CComponent::getStretchSide(SIDE side)
{
	return m_aStretchSide[side];
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