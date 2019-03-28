
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __TOOLBAR_H
#define __TOOLBAR_H

#include "base.h"


class CToolBar : public CComponent, public virtual IToolBar
{
public:
	CToolBar();
	CToolBar(int iX, int iY, int iWidth, int iHeigth, IControl *pParent, int iWidthElement, int iHeigthElement);
	
	~CToolBar();

	void Release(){ mem_del(this); }


	void addButton(WORD num,WORD id,const char* hint,WORD id_resource,DWORD mask);
	void addSeparator(WORD num);

private:
	HIMAGELIST HimList;
};

#endif