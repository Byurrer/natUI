
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __STATUS_BAR_H
#define __STATUS_BAR_H

#include "base.h"

class CStatusBar : public CTextual, public virtual IStatusBar
{
public:
	CStatusBar();
	CStatusBar(const char *szCaption, IControl *pParent);
	
	~CStatusBar();

	void Release(){ mem_del(this); }


	bool setPartsCount(int iCount, int *pArr);
	int getPartsCount(int **ppArr);
	bool setPartText(int iPos, const char *szText);
	bool getPartText(int iPos, char *szBuf, int iLen);

	void update();
	void updateSize();

	void setAlignReSize(STATUSBAR_ALIGN_RESIZE alignrs);
	STATUSBAR_ALIGN_RESIZE getAlignReSize();

protected:

	STATUSBAR_ALIGN_RESIZE m_alignReSizing;

	RECT m_oOldRect;

	void comCoef();

	float*	ArrCoef;
	int*	ArrWidth;
	WORD	CountArr;
};

#endif