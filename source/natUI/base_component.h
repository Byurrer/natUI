
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_COMPONENT_H
#define __BASE_COMPONENT_H

#include "hint.h"
#include "natUI.h"
#include "base_handle.h"
#include <common/array.h>

//##########################################################################

//! тип обработчика
typedef LRESULT(*HandlerSysFunc) (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! структура данных для обработчика
struct CHandlerSysData
{
	HandlerSysFunc m_fnHandler;//!< сама функция, которая будет вызываться
	UINT m_uMsg;			//!< код сообщения
	bool m_needPassOn;	//!< надо ли передавать сообщение дальше (в стандартную функцию обработки сообщений)
};



//второй в очереди родитель, часто наследование идет именно от него
//более расширенное управление большинством элементов
class CComponent : public CHandle, public virtual IComponent
{
public:
	CComponent();
	~CComponent();

	void Release(){ mem_del(this); }

	/*! устанавливает необходимые данные для управления элементом
	\note необходимо вызывать после инициализации
	*/
	void initComponent();

	//! возвращает действителен ли элемент
	bool getEnable();

	//! установка действительности элемента
	void setEnable(bool isEnable);


	//работа со стилями (в т.ч. специальным)
	//style_add - добавляемые стили
	//style_del - удаляемые
	bool modifyStyle(long lStyleAdd, long lStyleDel);
	void initStyle(UINT uStyle);
	bool modifyExStyle(long lStyleAdd, long lStyleDel);

	//устанавливает/возвращает область окна RECT элемента в глобальных координатах
	bool setWinRect(const RECT *pRect, bool alignment_screen_space);	//alignment_screen_space - использовать ли только работчую область (рабочий стол кроме панели задач)
	RECT* getWinRect();
	void getWinRect(RECT *pRect);

	//устанавливает/возвращает клиентскую область RECT элемента в глобальных координатах
	bool setClientRect(const RECT *pRect, bool isBoundScreen);	//alignment_screen_space - использовать ли только работчую область (рабочий стол кроме панели задач)
	void getClientRect(RECT *pRect);


	//! установка видимости подсказки
	void setShowHint(bool isShowHint);

	//! видна ли подсказка
	bool getShowHint();

	//! установка текста подсказки
	void setHintText(const char *szStr);

	//! возвращает текст подсказки
	const char* getHintText();

	//! записывает текст подсказки в буфер
	void getHintText(char *szBuf);


	//! установка цвета заднего фона элемента
	bool setColorBrush(UINT uColor);

	//! возвращает цвет заднего фона элемента
	UINT getColorBrush();

	//! возвращает кисть заднего фона элемента
	NativeHandle getBrush();


	void addHandlerSys(HandlerSysFunc Handler, UINT uMsg, bool needPassOn = true);	//все что необъявлено из функции выше не учитывается
	bool procHandlerSys(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet);	//выполняет функцию обработчик, в аргументы отправляет свои аргументы


	//! если есть привязка к сторонам родителя то при изменении размеров родителя обработает это
	void updateSize();

	//! считает смещение родителя, по старым данным, в #m_rcOffsetParent записывается смещение, если там 0, значит смещения не было
	void updateRect();


	//! установить минимальные размеры окна, установливать надо оба, один работать не будет, по умолчанию 0 - нет минмума
	void setMinSize(UINT uMinWidth, UINT uMinHeght);

	//! возвращает минимальную ширину
	UINT getMinWidth();

	//! возвращает минимальную высоту
	UINT getMinHeight();


	//! установка возможности растягивать элемент за стороны, по умолчанию все true
	void setStretchSides(bool canTop, bool canBottom, bool canRight, bool canLeft);

	//! установка возможности растягивать элемент за сторону
	void setStretchSide(SIDE side, bool can);

	//! возвращает можно ли растягивать элемент за сторону
	bool getStretchSide(SIDE side);


	//! закрепление сторон элемента за позициями его родителя, если сторона закреплена, то будет реагировать на изменения размеров родителя, по умолчанию все false
	void setFollowParentSides(bool canTop, bool canBottom, bool canRight, bool canLeft);

	//! закрепление стороны элемента за позициями его родителя
	void setFollowParentSide(SIDE side, bool can);

	//! закреплена ли сторона за родителем?
	bool getFollowParentSide(SIDE side);

protected:

	/*! \name Данные для updateSize
	@{*/

	//! координаты родителя
	RECT m_rcParentScreen;

	//! на сколько был изменен родитель
	RECT m_rcOffsetParent;

	//! координаты текущего окна относительно рабочего стола
	RECT m_rcWinScreen;

	/*!@}*/


	//! всплывающая подсказка
	IHint *m_pHint;


	//! массив обработчиков сообщений
	Array<CHandlerSysData> m_aHandlers;


	//! цвет заливки формы
	UINT m_uColorBrush;

	//! кисть заливки
	HBRUSH m_hBrush;


	//! минимальный размер окна по ширине
	int m_iMinSizeWidth;

	//! минимальный размер окна по высоте
	int m_iMinSizeHeight;

	bool m_aStrethSide[SIDE_COUNT];
	bool m_aFollowParentSide[SIDE_COUNT];
};

#endif