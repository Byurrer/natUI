
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __HINT_H
#define __HINT_H

#include <stdio.h>
#include <windows.h>
#include <commctrl.h>

#include "base_handle.h"
#include "natUI.h"


class CHint : public virtual IHint
{
public:
	CHint();
	CHint(IControl *pParent);
	~CHint();

	void nullingData();

	void Release(){ mem_del(this); }

	void setDelayTime(UINT uInit, UINT uAutopop);

	bool setParent(IControl *pParent);
	IControl* getParent();

	NativeHandle getNativeHandle();

	void setVisible(bool isVisible);
	bool getVisible();

	void setText(const char *szText);
	const char* getText();
	void getText(char *szBuf);

protected:
	HWND m_hHint;
	IControl *m_pParent;
	TOOLINFO m_oHintInfo;
	char m_szText[HINT_COUNT_BUF_SIZE];
	bool m_isVisible;
};

#endif