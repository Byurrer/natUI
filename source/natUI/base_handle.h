
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_HANDLE_H
#define __BASE_HANDLE_H

#include <windowsx.h>
#include "natUI.h"
#include "base_control.h"
#include <common/array.h>
#include <common/string.h>

//##########################################################################

/*! \name ���� ����������� ������ WinApi
@{*/

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

//!@}

//##########################################################################

//! ���������� WINDOW_SIZE_STATE �� wParam ��������� WM_SIZE
inline WINDOW_SIZE_STATE GetWindowSizeStateByWparam(WPARAM wParam)
{
	/*if (wParam == SIZE_MAXHIDE)
		return WINDOW_SIZE_STATE_MAXHIDE;*/
	/*else if (wParam == SIZE_MAXSHOW)
	return WINDOW_SIZE_STATE_MAXSHOW;*/
	if (wParam == SIZE_MAXIMIZED)
		return WINDOW_SIZE_STATE_MAXIMIZED;
	
	else if (wParam == SIZE_MINIMIZED)
		return WINDOW_SIZE_STATE_MINIMIZED;
	else if (wParam == SIZE_RESTORED)
		return WINDOW_SIZE_STATE_RESTORED;
	else
		return WINDOW_SIZE_STATE_STABLE;
}

//! ���������� ����������� ���������
struct CHandlerEx
{
	CHandlerEx(){}
	CHandlerEx(CODE_MESSAGE_EX codeMsgEx, void *pHandler){ m_codeMsgEx = codeMsgEx; m_pHandler = pHandler; }
	CODE_MESSAGE_EX m_codeMsgEx;
	void *m_pHandler;
};

//! ���������� ��������� ����
struct CHandlerMouse
{
	CHandlerMouse(){}
	CHandlerMouse(CODE_MESSAGE_MOUSE codeMouse, HandlerMouse fnHandler){ m_codeMouse = codeMouse; m_fnHandler = fnHandler; }
	CODE_MESSAGE_MOUSE m_codeMouse;
	HandlerMouse m_fnHandler;
};

//! ���������� ��������� ����������
struct CHandlerKey
{
	CHandlerKey(){}
	CHandlerKey(CODE_MESSAGE_KEY codeKey, HandlerKey fnHandler){ m_codeKey = codeKey; m_fnHandler = fnHandler; }
	CODE_MESSAGE_KEY m_codeKey;
	HandlerKey m_fnHandler;
};

//##########################################################################

//! ����� ��������� ���������
class CHandle : public CControl, public virtual IHandle
{
public:

	CHandle();
	~CHandle();

	void Release(){ mem_del(this); }

	void addHandlerMouse(CODE_MESSAGE_MOUSE codeMsgMouse, HandlerMouse fnHandler);

	void addHandlerKey(CODE_MESSAGE_KEY codeMsgKey, HandlerKey fnHandler);

	/*! �������� ���������� ����������� ���������
	 \param pHandler - ����������
	*/
	void addHandlerEx(CODE_MESSAGE_EX codeMsgEx, void *pHandler);

	/*! ���������� ���������, 
	 \note ���� ���� ����� ��������� �� ������� � ����������� ����������, ���� ������� true � ���������� pRet
	 \param pRet - ������������ ������� ������������ ��������, ���� ������������� ������ ���� ������� ���������� true
	*/
	int proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet);

	/*! ���������� ����������� ��������� (���� ���������� ��� ���� ����������)
	 \param prt - ��������� �� ��������� ������, ������������ � �������-����������
	*/
	HANDLER_CODE_RETURN procEx(CODE_MESSAGE_EX codeMsgEx, void *prt = 0);

protected:

	//! ������������� ����� ����������� winapi ����� ������ � enum-�� VKEY
	void initMapKey();

	/*! ��������� ���� �������� �� �������-����������� codeRet, ���������� � pRet �������� ���� ���������, 
	���������� true ���� ��������� ������� �������� � ������� ����������� (� �� ���������� ��������� ������)
	*/
	int procCodeReturn(HCR codeRet, LONG *pRet);


	//! �������� �� ��������� ��������
	bool isMsgMouse(UINT uMsg);

	//! ���������� ��������� �� #CODE_MESSAGE_MOUSE ���������� winapi-�����
	CODE_MESSAGE_MOUSE getCodeMouseOfMsg(UINT uMsg);

	//! ���������� ������ ����������� ��� ��������� ����, ���� ��� ����������� ��������� NULL
	CHandlerMouse* getHandlerMouse(CODE_MESSAGE_MOUSE codeMouse);


	//! ���������� ��������� �� #CODE_MESSAGE_KEY ���������� winapi-�����
	CODE_MESSAGE_KEY getCodeKeyOfMsg(UINT uMsg);

	//! ���������� ������ ����������� ��� ��������� ������, ���� ��� ����������� ��������� NULL
	CHandlerKey* getHandlerKey(CODE_MESSAGE_KEY codeKey);


	//! ���������� ������-���������� ����������� ���������
	CHandlerEx* getHandlerEx(CODE_MESSAGE_EX codeEx);


	//! ������ ��������-������������ ��� ��������� ����
	Array<CHandlerMouse*> m_aHandlersMouse;

	//! ������ ��������-������������ ��� ��������� ������ ����������
	Array<CHandlerKey*> m_aHandlersKey;

	//! //! ������ ��������-������������ ����������� ���������
	Array<CHandlerEx*> m_aHandlersEx;

	//! ����� ������������ winapi ����� ������ enum VKEY
	Array<VKEY> m_aVkeys;
};

#endif