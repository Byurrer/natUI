
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_COMPONENT_H
#define __BASE_COMPONENT_H

#include "hint.h"
#include "natUI.h"
#include "base_handle.h"
#include <common/array.h>

//##########################################################################

//! ��� �����������
typedef LRESULT(*HandlerSysFunc) (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! ��������� ������ ��� �����������
struct CHandlerSysData
{
	//! ���� �������, ������� ����� ����������
	HandlerSysFunc m_fnHandler;

	//! ��� ���������
	UINT m_uMsg;

	//! ���� �� ���������� ��������� ������ (� ����������� ������� ��������� ���������)
	bool m_needPassOn;
};

//##########################################################################

//! ������ � IDC_ ���������������� ����������� ��������
extern Array<LPCSTR> g_aStdCursorCode;

//! ������ HCURSOR ����������� ��������
extern Array<HCURSOR> g_aStdCursor;

//! ������������� ����������� ��������
void InitCursor();

//##########################################################################

class CComponent : public CHandle, public virtual IComponent
{
public:
	CComponent();
	~CComponent();

	void Release(){ mem_del(this); }

	/*! ������������� ����������� ������ ��� ���������� ���������
	\note ���������� �������� ����� �������������
	*/
	void initComponent();

	bool getEnable();
	void setEnable(bool isEnable);


	bool modifyStyle(long lStyleAdd, long lStyleDel);
	void initStyle(UINT uStyle);
	bool modifyExStyle(long lStyleAdd, long lStyleDel);

	bool setWinRect(const RECT *pRect, bool isBoundScreen);
	void getWinRect(RECT *pRect);

	bool setClientRect(const RECT *pRect, bool isBoundScreen);
	void getClientRect(RECT *pRect);


	void getPos(POINT *pPoint);
	void getSize(POINT *pSize);
	void setPos(const POINT *pPoint);
	void setSize(const POINT *pSize);
	void adjustPos(int iAdjustX, int iAdjustY);


	void setShowHint(bool isShowHint);
	bool getShowHint();
	void setHintText(const char *szStr);
	const char* getHintText();
	void getHintText(char *szBuf);

	void setCursor(ID idCursor);
	ID getCursor();
	HCURSOR getHCursor();

	bool setColorBrush(UINT uColor);
	UINT getColorBrush();
	NativeHandle getBrush();


	//! ���������� ���������� �����������  ��������� uMsg, needPassOn - ���� �� ���������� ��������� ������ � ����������� ����������
	void addHandlerSys(HandlerSysFunc Handler, UINT uMsg, bool needPassOn = true);

	//! ��������� ������� ���������� �� ��������� ��������� uMsg
	bool procHandlerSys(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet);


	void updateSize();
	void updateRect();

	void setMinSize(UINT uMinWidth, UINT uMinHeght);
	UINT getMinWidth();
	UINT getMinHeight();

	void setStretchSides(bool canTop, bool canBottom, bool canRight, bool canLeft);
	void setStretchSide(SIDE side, bool can);
	bool getStretchSide(SIDE side);

	void setFollowParentSides(bool canTop, bool canBottom, bool canRight, bool canLeft);
	void setFollowParentSide(SIDE side, bool can);
	bool getFollowParentSide(SIDE side);

protected:

	/*! \name ������ ��� updateSize
	@{*/

	//! ���������� ��������
	RECT m_rcParentScreen;

	//! �� ������� ��� ������� ��������
	RECT m_rcOffsetParent;

	//! ���������� �������� ���� ������������ �������� �����
	RECT m_rcWinScreen;

	/*!@}*/


	//! ����������� ���������
	IHint *m_pHint;


	//! ������ ������������ ���������
	Array<CHandlerSysData> m_aHandlers;

	ID m_idCursor;
	HCURSOR m_hCursor;


	//! ���� ������� �����
	UINT m_uColorBrush;

	//! ����� �������
	HBRUSH m_hBrush;


	//! ����������� ������ ���� �� ������
	int m_iMinSizeWidth;

	//! ����������� ������ ���� �� ������
	int m_iMinSizeHeight;

	//! ������ ������������ ������� �� �������
	bool m_aStretchSide[SIDE_COUNT];

	//! ������ �������� ������ ������� � �������� ��������
	bool m_aFollowParentSide[SIDE_COUNT];
};

#endif