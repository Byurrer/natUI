
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_STATIC_H
#define __SXGUI_STATIC_H

#include "base.h"

class CStatic : public CTextual, public virtual IStatic
{
public:
	CStatic();
	CStatic(const char *szCaption, int iPosX, int iPosY, int iWidth, int iHeight, IControl *pParent = 0);

	//������� �����
	CStatic(int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, bool isVertical = false);

	TEXT_ALIGN getAlign();			//���������� ���� ������������ ������
	bool setAlign(TEXT_ALIGN align);	//������������� ������������ ������

	bool getWordWrap();		//���������� �� ����������� �����
	bool setWordWrap(bool bf); //����������� �� ��������� ����������� �����
};

#endif