
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __UP_DOWN_H
#define __UP_DOWN_H

#include "base.h"


class CUpDown : public CComponent, public virtual IUpDown
{
public:
	CUpDown();
	CUpDown(int iX, int iY, int iWidth, int iHeigth, IControl *pParent, IControl *pBuddy, bool isAlignLeft);

	~CUpDown();


	void setMinMax(int iMin, int iMax);
	int setPos(int iPos);

	int getMin();
	int getMax();
	int getPos();

	/*void setBuddy(IControl *pBuddy);
	IControl* getBuddy();*/
};

#endif