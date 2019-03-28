
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_CONTROL_H
#define __BASE_CONTROL_H

#include "natUI.h"

/*!
������ ������� �����, ������������ ��������� �� ������������
���������� ������ ��� �������, �� ���� �������� � ���� ������� ������ ���
���������� ��������
*/
class CControl : public virtual IControl
{
public:

	CControl();
	//CControl(HWND hWindow, HWND hParent, WNDPROC lpfnHandler);
	~CControl();

	void Release(){ mem_del(this); }

	//! ���������� �����������, � ������������� ����� ����������
	void initControl(GUI_TYPE_ELEMENT typeElement, IControl *pParent, bool isContainer = false, ID idObj = -1);


	//! ���������� ������� �������� ��������
	IControl* getParent();

	//! ������������� ��������
	bool setParent(IControl *pParent);

	//! ���������� HWND ��������
	HWND getParentHWND();


	//! ���������� �������� ���������� �������, � ����������� ����
	NativeHandle getNativeHandle();

	//! ���������� HWND ������� (��� ������������� ������ ����������)
	HWND getHWND();


	//! ��������� ��������� ��������
	void setVisible(bool isVisible);

	//! ����� �� �������?
	bool getVisible();


	//! ���������� ����� �� �������
	void setFocus();

	//! ���������� �� ����� �� ��������?
	bool getFocus();


	//! �������� ���������������� ������
	void* getUserPtr();

	//! ���������� ���������������� ������, ���������� ���������� ��������
	void* setUserPtr(void *ptr);

	void* getPrevWndProc();

	GUI_TYPE_ELEMENT getElementType();

private:

	//! ��������� �� ���������������� ������
	void *m_pUserPtr;

	//! ���������������� id �������
	ID m_id;

protected:

	//! hwnd �������
	HWND m_hParent;

	//! hwnd ��������
	HWND m_hWindow;

	bool m_isContainer;

	WNDPROC m_lpfnPrevProc;

	GUI_TYPE_ELEMENT m_typeElement;
};

#endif