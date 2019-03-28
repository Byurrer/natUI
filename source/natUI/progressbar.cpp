
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "progressbar.h"


CProgressBar::CProgressBar()
{

}

CProgressBar::CProgressBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isVertical, bool isSmooth)
{
	m_hWindow = CreateWindowEx(
		0,
		PROGRESS_CLASS,
		0,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | (isSmooth ? PBS_SMOOTH : 0) | (isVertical ? PBS_VERTICAL : 0),
		iX, iY, iWidth, iHeight,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_PROGRESSBAR, 0, false);
	IComponent *pComponent = dynamic_cast<IComponent*>(this);
	SetWindowLong(m_hWindow, GWL_USERDATA, (LONG)dynamic_cast<IComponent*>(this));
	initComponent();
}

int CProgressBar::getPos()
{
	return SendMessage(m_hWindow, PBM_GETPOS, 0, 0);
}

int CProgressBar::setPos(int iPos)
{
	return SendMessage(m_hWindow, PBM_SETPOS, WPARAM(iPos), 0);
}

int CProgressBar::getStep()
{
	int iStep = SendMessage(m_hWindow,PBM_SETSTEP,WPARAM(0),0);

	SendMessage(m_hWindow, PBM_SETSTEP, WPARAM(iStep), 0);
	return iStep;
}

int CProgressBar::setStep(int iStep)
{
	return SendMessage(m_hWindow, PBM_SETSTEP, WPARAM(iStep), 0);
}

int CProgressBar::setPosSteps(int iSteps)
{
	return SendMessage(m_hWindow, PBM_DELTAPOS, WPARAM(iSteps), 0);
}

int CProgressBar::setOneStep()
{
	return SendMessage(m_hWindow, PBM_STEPIT, 0, 0);
}

bool CProgressBar::setMinMax(int iMin,int iMax)
{
	return SendMessage(m_hWindow, PBM_SETRANGE32, WPARAM(iMin), LPARAM(iMax));
}


int CProgressBar::getMin()
{
	return SendMessage(m_hWindow, PBM_GETRANGE, WPARAM(1), 0);
}

int CProgressBar::getMax()
{
	return SendMessage(m_hWindow, PBM_GETRANGE, WPARAM(0), 0);
}

bool CProgressBar::setColorBar(UINT uColor)
{
	return SendMessage(m_hWindow, PBM_SETBARCOLOR, 0, LPARAM(uColor));
}

bool CProgressBar::setColorBk(UINT uColor)
{
	return SendMessage(m_hWindow, PBM_SETBKCOLOR, 1, LPARAM(uColor));
}

UINT CProgressBar::getColorBar()
{
	COLORREF uColor = SendMessage(m_hWindow, PBM_SETBARCOLOR, 0, 0);
	return uColor;
}

UINT CProgressBar::getColorBk()
{
	UINT uColor = SendMessage(m_hWindow, PBM_SETBKCOLOR, 0, 0);
	return uColor;
}