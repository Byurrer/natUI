
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
	HandlerSysFunc m_fnHandler;//!< ���� �������, ������� ����� ����������
	UINT m_uMsg;			//!< ��� ���������
	bool m_needPassOn;	//!< ���� �� ���������� ��������� ������ (� ����������� ������� ��������� ���������)
};



//������ � ������� ��������, ����� ������������ ���� ������ �� ����
//����� ����������� ���������� ������������ ���������
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

	//! ���������� ������������ �� �������
	bool getEnable();

	//! ��������� ���������������� ��������
	void setEnable(bool isEnable);


	//������ �� ������� (� �.�. �����������)
	//style_add - ����������� �����
	//style_del - ���������
	bool modifyStyle(long lStyleAdd, long lStyleDel);
	void initStyle(UINT uStyle);
	bool modifyExStyle(long lStyleAdd, long lStyleDel);

	//�������������/���������� ������� ���� RECT �������� � ���������� �����������
	bool setWinRect(const RECT *pRect, bool alignment_screen_space);	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	RECT* getWinRect();
	void getWinRect(RECT *pRect);

	//�������������/���������� ���������� ������� RECT �������� � ���������� �����������
	bool setClientRect(const RECT *pRect, bool isBoundScreen);	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	void getClientRect(RECT *pRect);


	//! ��������� ��������� ���������
	void setShowHint(bool isShowHint);

	//! ����� �� ���������
	bool getShowHint();

	//! ��������� ������ ���������
	void setHintText(const char *szStr);

	//! ���������� ����� ���������
	const char* getHintText();

	//! ���������� ����� ��������� � �����
	void getHintText(char *szBuf);


	//! ��������� ����� ������� ���� ��������
	bool setColorBrush(UINT uColor);

	//! ���������� ���� ������� ���� ��������
	UINT getColorBrush();

	//! ���������� ����� ������� ���� ��������
	NativeHandle getBrush();


	void addHandlerSys(HandlerSysFunc Handler, UINT uMsg, bool needPassOn = true);	//��� ��� ����������� �� ������� ���� �� �����������
	bool procHandlerSys(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet);	//��������� ������� ����������, � ��������� ���������� ���� ���������


	//! ���� ���� �������� � �������� �������� �� ��� ��������� �������� �������� ���������� ���
	void updateSize();

	//! ������� �������� ��������, �� ������ ������, � #m_rcOffsetParent ������������ ��������, ���� ��� 0, ������ �������� �� ����
	void updateRect();


	//! ���������� ����������� ������� ����, ������������� ���� ���, ���� �������� �� �����, �� ��������� 0 - ��� �������
	void setMinSize(UINT uMinWidth, UINT uMinHeght);

	//! ���������� ����������� ������
	UINT getMinWidth();

	//! ���������� ����������� ������
	UINT getMinHeight();


	//! ��������� ����������� ����������� ������� �� �������, �� ��������� ��� true
	void setStretchSides(bool canTop, bool canBottom, bool canRight, bool canLeft);

	//! ��������� ����������� ����������� ������� �� �������
	void setStretchSide(SIDE side, bool can);

	//! ���������� ����� �� ����������� ������� �� �������
	bool getStretchSide(SIDE side);


	//! ����������� ������ �������� �� ��������� ��� ��������, ���� ������� ����������, �� ����� ����������� �� ��������� �������� ��������, �� ��������� ��� false
	void setFollowParentSides(bool canTop, bool canBottom, bool canRight, bool canLeft);

	//! ����������� ������� �������� �� ��������� ��� ��������
	void setFollowParentSide(SIDE side, bool can);

	//! ���������� �� ������� �� ���������?
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


	//! ���� ������� �����
	UINT m_uColorBrush;

	//! ����� �������
	HBRUSH m_hBrush;


	//! ����������� ������ ���� �� ������
	int m_iMinSizeWidth;

	//! ����������� ������ ���� �� ������
	int m_iMinSizeHeight;

	bool m_aStrethSide[SIDE_COUNT];
	bool m_aFollowParentSide[SIDE_COUNT];
};

#endif