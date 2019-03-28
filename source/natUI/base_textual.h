
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_TEXTUAL_H
#define __BASE_TEXTUAL_H

#include "natUI.h"
#include "base_component.h"

/*!
третий (если нужен текст) родитель, непосредтсвенно не используется
характеризует элемент как содержащий единый текст (caption), текстовый компонент
*/
class CTextual : public CComponent, public virtual ITextual
{
public:
	CTextual();
	~CTextual();

	void Release(){ mem_del(this); }

	void initTextual();


	//! установка текста
	bool setText(const char *szStr);

	//! записывает в buf текущий текст элемента, не больше size
	void getText(char *szBuf, int iSize);

	//! возвращает размер строки
	int getTextLen();


	/*! установка шрифта
	если szName == 0 то меняет шрифт на дефолтный,
	если остальные значения в -1 то не учитываются*/
	void setFont(const char *szName, int iHeight, int iWidth, int iWeight = TEXTUAL_BOLD_NORMAL, UINT uStyle = TEXTUAL_STYLE_NONE);

	//! наследуется ли шрифт родителя
	bool hasParentFont();

	//! установка родительского шрифта
	void setParentHFont();


	//! установить цвет текста
	void setColorText(UINT uColor);

	//! получить цвет текста
	UINT getColorText();

	//! установить прозрачность заднего фона текста
	void setTransparentTextBk(bool isTransparent);

	//! получить прозрачность заднего фона текста
	bool getTransparentTextBk();

	//! установить цвет заднего фона
	void setColorTextBk(UINT uColor);

	//! получить цвет заднего фона
	UINT getColorTextBk();

protected:

	//! цвет текста
	UINT m_uColorText;

	//! используется прозрачность? если true то заднего фона у текста не будет
	bool m_isTransparentTextBk;

	//! цвет заднего фона у текста
	UINT m_uColorTextBk;
};

#endif