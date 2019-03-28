
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_TEXTUAL_H
#define __BASE_TEXTUAL_H

#include "natUI.h"
#include "base_component.h"

/*!
������ (���� ����� �����) ��������, ��������������� �� ������������
������������� ������� ��� ���������� ������ ����� (caption), ��������� ���������
*/
class CTextual : public CComponent, public virtual ITextual
{
public:
	CTextual();
	~CTextual();

	void Release(){ mem_del(this); }

	void initTextual();


	//! ��������� ������
	bool setText(const char *szStr);

	//! ���������� � buf ������� ����� ��������, �� ������ size
	void getText(char *szBuf, int iSize);

	//! ���������� ������ ������
	int getTextLen();


	/*! ��������� ������
	���� szName == 0 �� ������ ����� �� ���������,
	���� ��������� �������� � -1 �� �� �����������*/
	void setFont(const char *szName, int iHeight, int iWidth, int iWeight = TEXTUAL_BOLD_NORMAL, UINT uStyle = TEXTUAL_STYLE_NONE);

	//! ����������� �� ����� ��������
	bool hasParentFont();

	//! ��������� ������������� ������
	void setParentHFont();


	//! ���������� ���� ������
	void setColorText(UINT uColor);

	//! �������� ���� ������
	UINT getColorText();

	//! ���������� ������������ ������� ���� ������
	void setTransparentTextBk(bool isTransparent);

	//! �������� ������������ ������� ���� ������
	bool getTransparentTextBk();

	//! ���������� ���� ������� ����
	void setColorTextBk(UINT uColor);

	//! �������� ���� ������� ����
	UINT getColorTextBk();

protected:

	//! ���� ������
	UINT m_uColorText;

	//! ������������ ������������? ���� true �� ������� ���� � ������ �� �����
	bool m_isTransparentTextBk;

	//! ���� ������� ���� � ������
	UINT m_uColorTextBk;
};

#endif