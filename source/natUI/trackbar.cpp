
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "trackbar.h"


CTrackBar::CTrackBar()
{

}

CTrackBar::CTrackBar(int iX, int iY, int iWidth, int iHeigth, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		TRACKBAR_CLASS,
		0,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | TBS_AUTOTICKS,
		iX, iY, iWidth, iHeigth,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_TRACKBAR, 0, false);
	SetWindowLong(getHWND(),GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();
}

void CTrackBar::setPos(int iPos)
{
	SendMessage(m_hWindow, TBM_SETPOS, WPARAM(TRUE), LPARAM(iPos));
}

int CTrackBar::getPos()
{
	return SendMessage(m_hWindow,TBM_GETPOS,0,0);
}

void CTrackBar::setMinMax(int iMin, int iMax)
{
	SendMessage(m_hWindow, TBM_SETRANGE, WPARAM(TRUE), MAKELPARAM(iMin, iMax));
}

int CTrackBar::getMin()
{
	return SendMessage(m_hWindow, TBM_GETRANGEMIN, 0, 0);
}

int CTrackBar::getMax()
{
	return SendMessage(m_hWindow, TBM_GETRANGEMAX, 0, 0);
}

bool CTrackBar::setTick(int iPos)
{
	return (SendMessage(m_hWindow, TBM_SETTIC, 0, LPARAM(iPos)));
}

int CTrackBar::getTick(int iIndex)
{
	return SendMessage(m_hWindow, TBM_GETTIC, WPARAM(iIndex), 0);
}

void CTrackBar::setTickFrequency(int iFreq)
{
	SendMessage(m_hWindow, TBM_SETTICFREQ, WPARAM(iFreq), 0);
}

/*bool CTrackBar::setBuddies(HWND hwnd_left,HWND hwnd_right)
{
		if(!hwnd_left && !hwnd_left)
			return false;
	
	SendMessage(m_hWindow,TBM_SETBUDDY,WPARAM(TRUE),LPARAM(hwnd_left));
	SendMessage(m_hWindow,TBM_SETBUDDY,WPARAM(FALSE),LPARAM(hwnd_right));

	return true;
}

HWND CTrackBar::getLeftBuddy()
{
	return HWND(SendMessage(m_hWindow,TBM_GETBUDDY,WPARAM(TRUE),0));
}

HWND CTrackBar::getRightBuddy()
{
	return HWND(SendMessage(m_hWindow,TBM_GETBUDDY,WPARAM(FALSE),0));
}*/