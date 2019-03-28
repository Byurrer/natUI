
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __LIST_VIEW_H
#define __LIST_VIEW_H

#include "base.h"
#include "common/string.h"
#include "common/array.h"


class CListView : public CTextual, public virtual IListView
{
public:
	CListView();
	CListView(int iX, int iY, int iWidth, int iHeigth, IControl *pParent);

	int insertColumn(const char *szText, int iIndexColumn, int iWidth);
	int addColumn(const char *iIndexColumn, int iWidth);
	void deleteColumn(int iIndexColumn);
	int getColumnsCount();

	int addString(LONG lData = -1);
	void deleteString(int iIndexString);
	int getStringCount();

	void setItemText(const char *szText, int iIndexColumn, int iIndexString);
	void getItemText(char *szText, int iIndexColumn, int iIndexString, int iSizeBuffer);

	void setItemData(int iIndexString, LONG lData);
	LONG getItemData(int iIndexString);

	int getSelString(int iStart = -1);
	void setSelString(int iIndexString);

	int getSelColumn();
	void setSelColumn(int iIndexColumn);

	void clear();
	void clearStrings();

private:
	Array<Array<String>> m_aStrings;
	Array<LONG> m_aStringData;
};

#endif