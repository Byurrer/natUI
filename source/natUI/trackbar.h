
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2018
See the license in LICENSE
***********************************************************/

#ifndef __TRACK_BAR_H
#define __TRACK_BAR_H

#include "base.h"


class CTrackBar : public CComponent, public virtual ITrackBar
{
public:
	CTrackBar();
	CTrackBar(int iX, int iY, int iWidth, int iHeigth, IControl *pParent);

	void setPos(int iPos);
	int getPos();

	void setMinMax(int iMin,int iMax);
	int getMin();
	int getMax();

	bool setTick(int iPos);
	int getTick(int iIndex);

	void setTickFrequency(int iFreq);

	/*bool setBuddies(HWND hwnd_left,HWND hwnd_right);
	HWND getLeftBuddy();
	HWND getRightBuddy();*/
};

#endif