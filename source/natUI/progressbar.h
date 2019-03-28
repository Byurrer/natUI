
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __PROGRESS_BAR_H
#define __PROGRESS_BAR_H

#include "base.h"


class CProgressBar : public CComponent, public virtual IProgressBar
{
public:
	CProgressBar();
	CProgressBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, bool isVertical = false, bool isSmooth = true);

	int getPos();
	int setPos(int iPos);

	int getStep();
	int setStep(int iStep);

	int setPosSteps(int iSteps);
	int setOneStep();

	bool setMinMax(int iMin,int iMax);	

	int getMin();
	int getMax();

	bool setColorBar(UINT uColor);
	UINT getColorBar();

	bool setColorBk(UINT uColor);
	UINT getColorBk();
};

#endif