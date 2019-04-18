
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "statusbar.h"


CStatusBar::CStatusBar()
{

}

CStatusBar::CStatusBar(const char *szCaption, IControl *pParent)
{
	m_hWindow = CreateWindowEx(
		0,
		STATUSCLASSNAME,
		szCaption,
		(pParent != 0 ? WS_CHILD : 0) | WS_VISIBLE | TBS_AUTOTICKS | SBARS_SIZEGRIP | CCS_BOTTOM,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		(pParent ? (HWND)(pParent->getNativeHandle()) : 0),
		(HMENU)0,
		GetModuleHandle(0),
		0);
	
	initControl(GUI_TYPE_ELEMENT_STATUSBAR, 0, false);
	SetWindowLong(getHWND(),GWL_USERDATA,(LONG)dynamic_cast<IComponent*>(this));
	initComponent();
	initTextual();
	
	m_alignReSizing = STATUSBAR_ALIGN_RESIZE_PERCENT;
	ArrWidth = 0;
	ArrCoef = 0;
	CountArr = 0;

	m_aFollowParentSide[SIDE_TOP] = false;
	m_aFollowParentSide[SIDE_BOTTOM] = false;
	m_aFollowParentSide[SIDE_RIGHT] = false;
	m_aFollowParentSide[SIDE_LEFT] = false;

	::GetClientRect(m_hWindow,&this->m_oOldRect);
}

CStatusBar::~CStatusBar()
{
	mem_delete_a(ArrCoef);
	mem_delete_a(ArrWidth);
}

bool CStatusBar::setPartsCount(int iCount, int *pArr)
{
	CountArr = iCount;
	mem_delete_a(ArrWidth);
	ArrWidth = 0;
	ArrWidth = pArr;

	comCoef();

	return (SendMessage(m_hWindow, SB_SETPARTS, iCount, (LPARAM)pArr));
}

void CStatusBar::comCoef()
{
	WORD GWidth = 0;
	RECT rect;
	::GetClientRect(m_hWindow,&rect);
	GWidth = rect.right;
	float OnePercent = 100.0 / float(GWidth);

	mem_delete_a(ArrCoef);
	ArrCoef = new float[CountArr];

		for(int i=0;i<CountArr;i++)
		{
			ArrCoef[i] = OnePercent *  ((ArrWidth[i] != -1 ? ArrWidth[i] : GWidth) - (i > 0 ? ArrWidth[i-1] : 0));
		}
}

bool CStatusBar::setPartText(int iPos, const char *szText)
{
	SendMessage(m_hWindow, SB_SETTEXT, iPos, (LPARAM)szText);
	return true;
}

int CStatusBar::getPartsCount(int **ppArr)
{
	int iCount = SendMessage(m_hWindow, SB_GETPARTS, 0, 0);
	int *aParts = new int[iCount];

	int tmpcp = SendMessage(m_hWindow, SB_GETPARTS, iCount, (LPARAM)aParts);

	if (ppArr != 0)
		*ppArr = aParts;
	else
	{
		mem_delete_a(aParts);
	}

	return iCount;
}

bool CStatusBar::getPartText(int iPos, char *szBuf, int iLen)
{
	int iCountSym = SendMessage(m_hWindow, SB_GETTEXTLENGTH, iPos, 0);
	
	if (iLen < iCountSym)
		return false;

	if (!SendMessage(m_hWindow, SB_GETTEXT, iPos, (LPARAM)szBuf))
		return false;

	return true;
}

void CStatusBar::setAlignReSize(STATUSBAR_ALIGN_RESIZE alignrs)
{
	m_alignReSizing = alignrs;
}

STATUSBAR_ALIGN_RESIZE CStatusBar::getAlignReSize()
{
	return m_alignReSizing;
}

void CStatusBar::update()
{
	//RECT m_oOldRect;
	RECT NewRect;
	//::GetClientRect(m_hWindow,&this->m_oOldRect);
	SendMessage(m_hWindow,WM_SIZE,0,0);
	::GetClientRect(m_hWindow,&NewRect);

	int width = NewRect.right - m_oOldRect.right;
		/*if(width != 0)
			MessageBox(0,ToPointChar(width),0,0);*/
	int *Arr;
	
	WORD CountParts = getPartsCount(&Arr);
	int *NewArr = new int[CountParts];

	bool Updatem_oOldRect = true;

	WORD tmpCountParts = (Arr[CountParts-1] == -1 ? CountParts - 1 : CountParts);
	if (m_alignReSizing == STATUSBAR_ALIGN_RESIZE_PERCENT)
	{
		for (int i = 0; i<tmpCountParts; i++)
		{
			float coef = ArrCoef[i] / 100.0;
			//MessageBox(0,ToPointChar(coef),0,0);
			float part_width = (float)(Arr[i] - (i > 0 ? Arr[i - 1] : 0));
			float new_part_width = part_width + (int(width * coef));
			//MessageBox(0,ToPointChar(ToString(width) + "|" + ToString(coef)),ToPointChar(new_part_width),0);
			NewArr[i] = (int)(new_part_width + (i > 0 ? NewArr[i - 1] : 0));
			if (Arr[i] == NewArr[i])
				Updatem_oOldRect = false;
			//MessageBox(0,ToPointChar(ToString(Arr[i]) + "|" + ToString(NewArr[i])),0,0);
		}
	}
	else if (m_alignReSizing == STATUSBAR_ALIGN_RESIZE_EQUALLY)
	{
		for (int i = 0; i<tmpCountParts; i++)
			NewArr[i] = Arr[i] + (width / CountParts);
	}
	else
	{
		for (int i = 0; i<tmpCountParts; i++)
			NewArr[i] = Arr[i];
	}

	if (Arr[CountParts - 1] == -1)
		NewArr[CountParts - 1] = Arr[CountParts - 1];

	if (Updatem_oOldRect)
		::GetClientRect(m_hWindow, &this->m_oOldRect);

	SendMessage(m_hWindow, SB_SETPARTS, CountParts, (LPARAM)NewArr);
	mem_delete_a(Arr);
	mem_delete_a(NewArr);
}

void CStatusBar::updateSize()
{
	update();
}