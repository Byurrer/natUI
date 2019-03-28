
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __MEMO_H
#define __MEMO_H

#include "edit.h"

class CMemo : public CEdit, public virtual IMemo
{
public:
	CMemo();
	CMemo(const char *szCaption, int iX, int iY, int iWidth, int iHeigth, IControl *pParent);

	bool getWordWrap();
	bool setWordWrap(bool isWordWrap);
};

#endif