
#include "base_textual.h"
#include "base.h"

CTextual::CTextual()
{

}

CTextual::~CTextual()
{

}

void CTextual::initTextual()
{
	UINT uColorTextBk = GetBkColor(GetDC(m_hWindow));
	UINT uColorText = GetTextColor(GetDC(m_hWindow));

	m_uColorText = uColorText;
	m_uColorTextBk = uColorTextBk;
}

bool CTextual::setText(const char *szStr)
{
	return SetText(this, szStr);
}

void CTextual::getText(char *szBuffer, int iSize)
{
	GetText(this, szBuffer, iSize);
}

int CTextual::getTextLen()
{
	return GetTextLen(this);
}

void CTextual::setFont(const char *szName, int iHeight, int iWidth, int iWeight, UINT uStyle)
{
	const HDC hdc = GetWindowDC(m_hWindow);
	HFONT hFont = (HFONT)SendMessage(m_hWindow, WM_GETFONT, 0, 0);
	LOGFONT oLogFont;
	ZeroMemory(&oLogFont, sizeof(LOGFONT));

	if (hFont)
		GetObject(hFont, sizeof(LOGFONT), &oLogFont);

	if (szName != 0)
		strcpy(oLogFont.lfFaceName, szName);

	if (iHeight != -1)
		oLogFont.lfHeight = -MulDiv(iHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72); //iHeight;

	if (iWidth != -1)
		oLogFont.lfWidth = iWidth;
	else
		oLogFont.lfWidth = 0;

	if (iWeight != -1)
		oLogFont.lfWeight = iWeight;

	oLogFont.lfItalic = (uStyle & TEXTUAL_STYLE_ITALIC);
	oLogFont.lfUnderline = (uStyle & TEXTUAL_STYLE_UNDERLINE);
	oLogFont.lfStrikeOut = (uStyle & TEXTUAL_STYLE_STRIKEOUT);

	oLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;

	oLogFont.lfPitchAndFamily = VARIABLE_PITCH;

	DeleteObject(hFont);
	hFont = ::CreateFontIndirect(&oLogFont);

	SendMessage(m_hWindow, WM_SETFONT, WPARAM(hFont), 1);
	//DeleteObject(hFont);
}

bool CTextual::hasParentFont()
{
	HFONT hChildFont = (HFONT)SendMessage(m_hWindow, WM_GETFONT, 0, 0);
	HFONT hParentFont = (HFONT)SendMessage(getParentHWND(), WM_GETFONT, 0, 0);

	LOGFONT oChildLF, oParentLF;

	ZeroMemory(&oChildLF, sizeof(&oChildLF));
	GetObject(hChildFont, sizeof(LOGFONT), &oChildLF);

	ZeroMemory(&oParentLF, sizeof(&oParentLF));
	GetObject(hParentFont, sizeof(LOGFONT), &oParentLF);

	if (oChildLF.lfCharSet != oParentLF.lfCharSet)
		return false;
	if (oChildLF.lfClipPrecision != oParentLF.lfClipPrecision)
		return false;
	if (oChildLF.lfEscapement != oParentLF.lfEscapement)
		return false;
	if (oChildLF.lfHeight != oParentLF.lfHeight)
		return false;
	if (oChildLF.lfItalic != oParentLF.lfItalic)
		return false;
	if (oChildLF.lfOrientation != oParentLF.lfOrientation)
		return false;
	if (oChildLF.lfOutPrecision != oParentLF.lfOutPrecision)
		return false;
	if (oChildLF.lfPitchAndFamily != oParentLF.lfPitchAndFamily)
		return false;
	if (oChildLF.lfQuality != oParentLF.lfQuality)
		return false;
	if (oChildLF.lfStrikeOut != oParentLF.lfStrikeOut)
		return false;
	if (oChildLF.lfUnderline != oParentLF.lfUnderline)
		return false;
	if (oChildLF.lfWeight != oParentLF.lfWeight)
		return false;
	if (oChildLF.lfWidth != oParentLF.lfWidth)
		return false;
	if (strcmp(oChildLF.lfFaceName, oParentLF.lfFaceName) != 0)
		return false;

	return true;
}

void CTextual::setParentHFont()
{
	HFONT hParentFont = (HFONT)SendMessage(getParentHWND(), WM_GETFONT, 0, 0);
	SendMessage(getHWND(), WM_SETFONT, WPARAM(hParentFont), 1);
}

void CTextual::setColorText(UINT uColor)
{
	m_uColorText = uColor;
	InvalidateRect(getHWND(), 0, 1);
}

UINT CTextual::getColorText()
{
	return m_uColorText;
}

void CTextual::setTransparentTextBk(bool isTransparent)
{
	m_isTransparentTextBk = isTransparent;
	InvalidateRect(getHWND(), 0, 1);
}

bool CTextual::getTransparentTextBk()
{
	return m_isTransparentTextBk;
}

void CTextual::setColorTextBk(UINT uColor)
{
	m_uColorTextBk = uColor;
	InvalidateRect(getHWND(), 0, 1);
}

UINT CTextual::getColorTextBk()
{
	return m_uColorTextBk;
}