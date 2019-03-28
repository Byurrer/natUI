
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __LIST_BOX_H
#define __LIST_BOX_H

#include "base.h"


class CListBox : public CTextual, public virtual IListBox
{
public:
	CListBox();
	CListBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isMultipleSel = false);

	bool getStateMultiSel();
	void setStateMultiSel(bool isMultiSel);

	bool insertItem(int index, const char *szText);
	bool addItem(const char *szText);
	int getItemCount();

	bool deleteItem(int iIndex);

	bool setSel(int iIndex);
	int	getSel();

	bool setItemData(int iIndex, LONG lData);
	LONG getItemData(int iIndex);

	bool clear();

	bool setItemText(int iIndex, const char *szText);
	void getItemText(int iIndex, char *szBuf);

	int	getItemTextLength(int iIndex);

	int getMultiSelCount();

	bool setMultiSel(int iIndex, bool sel);
	bool getMultiSel(int iIndex);

	
	int getMultiSelArr(int **ppArr);
};

#endif