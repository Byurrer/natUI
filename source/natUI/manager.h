
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __MANAGER_H
#define __MANAGER_H

#include "natUI.h"

class CManager : public IManager
{
public:
	CManager();
	~CManager();

	void Release(){ mem_del(this); }

	IWindow* newWnd(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, WND_STYLE style = WND_STYLE_DEFAULT);

	//**********************************************************************
	IButton* newButton(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent, BUTTON_IMAGE typeImage = BUTTON_IMAGE_NONE);

	ICheckBox* newCheckBox(const char *szCaption, int iPosX, int iPosY, int iWidth, int iHeight, IControl *pParent = 0, bool is3State = false);

	IRadioButton* newRadioButton(const char *szCaption, int iPosX, int iPosY, int iWidth, int iHeight, IControl *pParent = 0);
	
	//*************************************************************************

	IListBox* newListBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isMultipleSel = false);

	IListView* newListView(int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	IComboBox* newComboBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	//*************************************************************************

	IStatic* newStatic(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	IStatic* newStaticLine(int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, bool isVertical = false);

	IEdit* newEdit(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	IMemo* newMemo(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent);

	//**********************************************************************

	IToolBar* newToolBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent, int iWidthElement, int iHeigthElement);

	IStatusBar* newStatusBar(const char *szCaption, IControl *pParent = 0);

	ITrackBar* newTrackBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0);

	IProgressBar* newProgressBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, bool isVertical = false, bool isSmooth = true);
	
	//**********************************************************************
	
	IMenuWindow* newMenuWindow(UINT uIdRes = -1) ;

	IMenuPopup* newMenuContext(UINT uIdRes = -1, int iIndex = 0);
};


#endif