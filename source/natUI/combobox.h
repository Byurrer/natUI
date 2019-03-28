
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __COMBO_BOX_H
#define __COMBO_BOX_H

#include "base.h"


class CComboBox : public CTextual, public virtual IComboBox
{
public:
	CComboBox();
	
	CComboBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	bool insertItem(int index,const char* text);
	bool deleteItem(int index);

	int	getCount();

	bool setSel(int index);
	int	getSel();

	bool setItemData(int index,LONG data);
	LONG getItemData(int index);

	bool clear();

	bool setItemText(int index,const char* text);
	void getItemText(int index,char* buf);
	int	getItemTextLength(int index);
	bool addItem(const char* text);
};

#endif