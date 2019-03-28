
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __CHECK_BOX_H
#define __CHECK_BOX_H

#include "base.h"
#include "button.h"

class CCheckBox : public CButton, public virtual ICheckBox
{
public:
	CCheckBox();
	CCheckBox(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent, bool is3State = false);

	void setCheckEx(CHECKBOX_STATE check);
	void setCheck(bool isCheck);
	CHECKBOX_STATE getCheck();
};

#endif