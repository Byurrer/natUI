
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __EDIT_H
#define __EDIT_H

#include "base.h"

class CEdit : public CTextual, public virtual IEdit
{
public:
	CEdit();
	~CEdit();
	CEdit(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent);

	bool getReadOnly();
	bool setReadOnly(bool bf);

	bool getStatePassword();
	bool setStatePassword(bool bf);

	TEXT_ALIGN getAlign();
	bool setAlign(TEXT_ALIGN align);
};

#endif