
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_GROUP_BOX_H
#define __SXGUI_GROUP_BOX_H

#include "base.h"


class CGroupBox : public CTextual, public virtual IGroupBox
{
public:
	CGroupBox();
	~CGroupBox();
	void Release(){ mem_del(this); }
	CGroupBox(const char* caption, WORD x, WORD y, WORD width, WORD heigth, IControl *pParent);
};

#endif