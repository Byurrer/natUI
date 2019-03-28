
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __RADIO_BUTTON_H
#define __RADIO_BUTTON_H

#include "base.h"
#include "button.h"


class CRadioButton : public CButton, public virtual IRadioButton
{
public:
	CRadioButton();
	CRadioButton(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	void setCheck(bool check);
	bool getCheck();
};

#endif