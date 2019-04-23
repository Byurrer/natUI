
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
	//! сама функция, которая будет вызываться
	HandlerSysFunc m_fnHandler;

	//! код сообщения
	UINT m_uMsg;

	//! надо ли передавать сообщение дальше (в стандартную функцию обработки сообщений)
	bool m_needPassOn;
};

//##########################################################################

//! массив с IDC_ идентификаторами стандартных курсоров
extern Array<LPCSTR> g_aStdCursorCode;

//! массив HCURSOR стандартных курсоров
extern Array<HCURSOR> g_aStdCursor;

//! инициализация стандартных курсоров
void InitCursor();

//##########################################################################

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

	bool getEnable();
	void setEnable(bool isEnable);


	bool modifyStyle(long lStyleAdd, long lStyleDel);
	void initStyle(UINT uStyle);
	bool modifyExStyle(long lStyleAdd, long lStyleDel);

	bool setWinRect(const RECT *pRect, bool isBoundScreen);
	void getWinRect(RECT *pRect);

	bool setClientRect(const RECT *pRect, bool isBoundScreen);
	void getClientRect(RECT *pRect);


	void getPos(POINT *pPoint);
	void getSize(POINT *pSize);
	void setPos(const POINT *pPoint);
	void setSize(const POINT *pSize);
	void adjustPos(int iAdjustX, int iAdjustY);


	void setShowHint(bool isShowHint);
	bool getShowHint();
	void setHintText(const char *szStr);
	const char* getHintText();
	void getHintText(char *szBuf);

	void setCursor(ID idCursor);
	ID getCursor();
	HCURSOR getHCursor();

	bool setColorBrush(UINT uColor);
	UINT getColorBrush();
	NativeHandle getBrush();


	//! добавление системного обработчика  сообщения uMsg, needPassOn - надо ли передавать сообщение дальше в стандартный обработчик
	void addHandlerSys(HandlerSysFunc Handler, UINT uMsg, bool needPassOn = true);

	//! выполняет функцию обработчик на основании сообщения uMsg
	bool procHandlerSys(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LONG *pRet);


	void updateSize();
	void updateRect();

	void setMinSize(UINT uMinWidth, UINT uMinHeght);
	UINT getMinWidth();
	UINT getMinHeight();

	void setStretchSides(bool canTop, bool canBottom, bool canRight, bool canLeft);
	void setStretchSide(SIDE side, bool can);
	bool getStretchSide(SIDE side);

	void setFollowParentSides(bool canTop, bool canBottom, bool canRight, bool canLeft);
	void setFollowParentSide(SIDE side, bool can);
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

	ID m_idCursor;
	HCURSOR m_hCursor;


	//! цвет заливки формы
	UINT m_uColorBrush;

	//! кисть заливки
	HBRUSH m_hBrush;


	//! минимальный размер окна по ширине
	int m_iMinSizeWidth;

	//! минимальный размер окна по высоте
	int m_iMinSizeHeight;

	//! данные растягивания объекта за стороны
	bool m_aStretchSide[SIDE_COUNT];

	//! данные привязки сторон объекта к сторонам родителя
	bool m_aFollowParentSide[SIDE_COUNT];
};

#endif