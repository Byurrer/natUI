
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BUTTON_H
#define __BUTTON_H

#include "base.h"


class CButton : public CTextual, public virtual IButton
{
public:
	CButton();
	CButton(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent = 0, BUTTON_IMAGE typeImage = BUTTON_IMAGE_NONE);

	bool setIconFromFile(const char *szPath);
	bool setBmpFromFile(const char *szPath);

	bool setIconFromResourse(UINT uIdRes);
	bool setBmpFromResourse(UINT uIdRes);

	void addHandlerActivated(HandlerExCommon fnHandler);
};

#endif