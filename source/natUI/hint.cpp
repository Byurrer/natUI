
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#include "hint.h"


CHint::CHint()
{
	nullingData();
}

CHint::CHint(IControl *pParent)
{
	static UINT uId = 0;
	uId++;

	if (!pParent)
	{
		nullingData();
	}
	else
	{
		m_pParent = pParent;

		
		RECT rect;

		m_hHint = CreateWindowEx(
			WS_EX_TOPMOST,
			TOOLTIPS_CLASS,
			NULL,
			WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			(HWND)(m_pParent->getNativeHandle()),
			NULL,
			GetModuleHandle(NULL),
			NULL
			);

		SetWindowPos(m_hHint, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

		GetClientRect((HWND)(m_pParent->getNativeHandle()), &rect);

		ZeroMemory(&m_oHintInfo, sizeof(m_oHintInfo));

		m_szText[0] = 0;

		m_oHintInfo.cbSize = TTTOOLINFO_V1_SIZE;
		m_oHintInfo.uFlags = TTF_SUBCLASS;
		m_oHintInfo.hwnd = (HWND)(m_pParent->getNativeHandle());
		//Hint.hinst = GetModuleHandle(NULL);
		m_oHintInfo.uId = uId;
		m_oHintInfo.lpszText = m_szText;

		m_oHintInfo.rect.left = rect.left;
		m_oHintInfo.rect.top = rect.top;
		m_oHintInfo.rect.right = rect.right;
		m_oHintInfo.rect.bottom = rect.bottom;

		SendMessage(m_hHint, TTM_ADDTOOL, 0, (LPARAM)&m_oHintInfo);

		m_isVisible = true;
	}
}

CHint::~CHint()
{
	::DestroyWindow(m_hHint);
}

void CHint::nullingData()
{
	m_hHint = 0;
	m_pParent = 0;
	m_isVisible = false;

	ZeroMemory(&m_oHintInfo, sizeof(m_oHintInfo));
}

NativeHandle CHint::getNativeHandle()
{
	return m_hHint;
}

void CHint::setDelayTime(UINT uInit, UINT uAutopop)
{
	SendMessage(m_hHint, TTM_SETDELAYTIME, TTDT_AUTOPOP, uAutopop);
	SendMessage(m_hHint, TTM_SETDELAYTIME, TTDT_INITIAL, uInit);
}

void CHint::setText(const char *szText)
{
	SendMessage(m_hHint, TTM_DELTOOL, 0, (LPARAM)&m_oHintInfo);
	sprintf(m_szText, "%s", szText);
	m_oHintInfo.lpszText = m_szText;
	SendMessage(m_hHint, TTM_ADDTOOL, 0, (LPARAM)&m_oHintInfo);
	//SendMessage(m_hHint, TTM_SETTOOLINFO , 0, (LPARAM) &m_oHintInfo);
}

const char* CHint::getText()
{
	return m_szText;
}

void CHint::getText(char *szBuf)
{
	if (szBuf)
		sprintf(szBuf, "%s", m_szText);
}

bool CHint::setParent(IControl *pParent)
{
	HWND hOldParent = GetParent(m_hHint);
	HWND hNewParent = (HWND)(pParent->getNativeHandle());
	m_pParent = pParent;
		
	return (SetParent(m_hHint, hNewParent) == hOldParent);
}

IControl* CHint::getParent()
{
	return m_pParent;
}

void CHint::setVisible(bool isVisible)
{
	SendMessage(m_hHint, TTM_ACTIVATE, (isVisible ? 1 : 0), 0);
	m_isVisible = isVisible;
}

bool CHint::getVisible()
{
	return m_isVisible;
}