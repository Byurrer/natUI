
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

/*!
\file
Заголовочный файл библиотеки графического пользовательского интерфейса посредством WinApi
*/

/*! \defgroup natui natUI - библиотека графического пользовательского интерфейса реализованного на WinApi
 \note Для начала нужно инициализировать вызвать функции инициализации #ManagerInit
@{*/ 

#ifndef __NATUI_H
#define __NATUI_H

#pragma warning(disable: 4250)

#include <common/types.h>
#include <windows.h>

#if defined(_NATUI_BUILD_DLL) || defined(_NATUI_BUILD_LIB)
#define NATUI_API extern "C" __declspec (dllexport)
#elif defined(NATUI_USE_DLL)
#define NATUI_API extern "C" __declspec (dllimport)
#elif defined(NATUI_USE_LIB)
#define NATUI_API extern "C"
#else
#define NATUI_API
#endif

//##########################################################################

//! тип нативного дескриптора (для независимости от типов winapi)
typedef void* NativeHandle;

//**************************************************************************

struct IComponent;
struct IHint;
struct IMenuBase;
struct IMenuWindow;
struct IMenuPopup;


//##########################################################################

//! выравнивание текста в элементе
enum TEXT_ALIGN
{
	//! по левому краю
	TEXT_ALIGN_LEFT = 0,

	//! по правому краю
	TEXT_ALIGN_RIGHT,

	//! по центру
	TEXT_ALIGN_CENTER,
};

//! стороны элемента
enum SIDE
{
	//! верх
	SIDE_TOP = 0,

	//! низ
	SIDE_BOTTOM,

	//! правая сторона
	SIDE_RIGHT,

	//! левая сторона
	SIDE_LEFT,

	SIDE_COUNT
};

//#############################################################################

//! тип элемента
enum GUI_TYPE_ELEMENT
{
	GUI_TYPE_ELEMENT_WINDOW,
	GUI_TYPE_ELEMENT_GROUPBOX,
	GUI_TYPE_ELEMENT_TOOLBAR,

	GUI_TYPE_ELEMENT_BUTTON,
	GUI_TYPE_ELEMENT_CHECKBOX,
	GUI_TYPE_ELEMENT_RADIOBUTTON,

	GUI_TYPE_ELEMENT_STATIC,

	GUI_TYPE_ELEMENT_UPDOWND,
	GUI_TYPE_ELEMENT_EDIT,
	GUI_TYPE_ELEMENT_MEMO,

	GUI_TYPE_ELEMENT_COMBOBOX,
	GUI_TYPE_ELEMENT_LISTBOX,
	GUI_TYPE_ELEMENT_LISTVIEW,

	GUI_TYPE_ELEMENT_PROGRESSBAR,
	GUI_TYPE_ELEMENT_STATUSBAR,
	GUI_TYPE_ELEMENT_TRACKBAR,
};

//#############################################################################

struct IBaseObject
{
	virtual ~IBaseObject(){};
	virtual void Release() = 0;
};


/*! интерфейс control - базовое управление элементарным функционалом объекта
*/
struct IControl : public IBaseObject
{
	virtual ~IControl(){};

	//! возвращает HWND родителя
	virtual IControl* getParent() = 0;

	//! устанавливает родителя
	virtual bool setParent(IControl *pParent) = 0;


	//! возвращает нативный дескриптор объекта
	virtual NativeHandle getNativeHandle() = 0;


	//! установка видимости контрола
	virtual void setVisible(bool isVisible) = 0;

	//! возвращает видим ли элемент
	virtual bool getVisible() = 0;


	//! установить фокус
	virtual void setFocus() = 0;

	//! установлен ли фокус?
	virtual bool getFocus() = 0;						

	//! возвращает предыдущий обработчик
	virtual void* getPrevWndProc() = 0;


	//! получить пользовательские данные
	virtual void* getUserPtr() = 0;

	//! установить пользовательские данные, возвращает предыдущее значение
	virtual void* setUserPtr(void *ptr) = 0;

	//! возвращает тип объекта #GUI_TYPE_ELEMENT
	virtual GUI_TYPE_ELEMENT getElementType() = 0;
};

//##########################################################################

//! коды возвратов из обработчиков, HANDLER_CODE_RETURN
enum HANDLER_CODE_RETURN
{
	//! ничего не предпринимать, сообщение отправится в стандартный обработчик
	HANDLER_CODE_RETURN_DEFAULT = 0,

	//! закрыть обработку и не передавать в стандартную функцию обработки сообщений
	HANDLER_CODE_RETURN_SUPERCEDE = 1,
};

//! тип функции обработчика для специальных сообщений
typedef HANDLER_CODE_RETURN(*HandlerExCommon) (IComponent*);

//! тип функции обработчика для таймеров
typedef HANDLER_CODE_RETURN(*HandlerTimer) (IComponent*);

//**************************************************************************

//! состояние изменения размеров окна
enum WINDOW_SIZE_STATE
{
	//! состояние не изменилось
	WINDOW_SIZE_STATE_STABLE,

	//! было развернуто
	WINDOW_SIZE_STATE_MAXIMIZED,

	//! было свернуто
	WINDOW_SIZE_STATE_MINIMIZED,

	//! окно изменило размеры через взаимодействие с границами окна, или при переходе из режима развернуто/свернуто
	WINDOW_SIZE_STATE_RESTORED
};


//! структура с данными сообщения окна
struct CHandlerDataWindow
{
	CHandlerDataWindow(){ m_stateSize = WINDOW_SIZE_STATE_STABLE; m_oPosNew.x = m_oPosNew.y = m_oSizeNew.x = m_oSizeNew.y = m_oPosCMenu.x = m_oPosCMenu.y = -1; m_pTargetComponent4CMenu = 0; }
	
	//! состояние размера окна
	WINDOW_SIZE_STATE m_stateSize;

	//! позиция верхнего левого угла
	POINT m_oPosNew;

	//! размер окна
	POINT m_oSizeNew;

	//! позиция генерации контекстного меню
	POINT m_oPosCMenu;

	//! целевой компонент для контекстного меню
	IComponent *m_pTargetComponent4CMenu;
};

//! тип функции обработчика для специальных сообщений
typedef HANDLER_CODE_RETURN(*HandlerExWindow) (IComponent*, const CHandlerDataWindow *);

//**************************************************************************

//! специальные сообщения для некоторых элементов
enum CODE_MESSAGE_EX
{
	//! активации кнопки, отметка чекбокса, выбор радио
	CODE_MESSAGE_EX_BUTTON_CLICK,

	//! выбор в комбобоксе
	CODE_MESSAGE_EX_COMBOBOX_SELCHANGE,

	//! выбор в листбоксе
	CODE_MESSAGE_EX_LISTBOX_SELCHANGE,

	//! изменения в edit
	CODE_MESSAGE_EX_EDIT_CHANGE,

	//! клик по строке в listview
	CODE_MESSAGE_EX_LISTVIEW_CLICK,

	//! закрытие окна
	CODE_MESSAGE_EX_WINDOW_CLOSE,

	//! изменение размеров окна
	CODE_MESSAGE_EX_WINDOW_SIZE,

	//! перемещение окна
	CODE_MESSAGE_EX_WINDOW_MOVE,

	//! вызов контекстного меню
	CODE_MESSAGE_EX_WINDOW_CALLCMENU,
};

//**************************************************************************

//! коды сообщений мыши
enum CODE_MESSAGE_MOUSE
{
	CODE_MESSAGE_MOUSE_NONE,

	//! движение мыши
	CODE_MESSAGE_MOUSE_MOVE,

	//! ЛКМ отпущена
	CODE_MESSAGE_MOUSE_LUP,

	//! ЛКМ нажата
	CODE_MESSAGE_MOUSE_LDOWN,

	//! ЛКМ двойной клик
	CODE_MESSAGE_MOUSE_LDBL,

	//! ПКМ отпущена
	CODE_MESSAGE_MOUSE_RUP,

	//! ПКМ нажата
	CODE_MESSAGE_MOUSE_RDOWN,

	//! ПКМ двойной клик
	CODE_MESSAGE_MOUSE_RDBL,


	//! СКМ отпущена
	CODE_MESSAGE_MOUSE_MUP,

	//! СКМ нажата
	CODE_MESSAGE_MOUSE_MDOWN,

	//! СКМ двойной клик
	CODE_MESSAGE_MOUSE_MDBL,


	//! прокрутка колеслом мыши
	CODE_MESSAGE_MOUSE_SCROLL,
};

//! структура с данными для сообщения от мыши
struct CHandleMouseData
{
	//! локальная позиция курсора (относительно элемента)
	POINT m_oLocalPos;

	//! глобальная позиция элемента (относительно рабочего стола)
	POINT m_oGlobalPos;

	//! прокрутка скроллом, -1 - вниз, 1 - вверх, число зависит от оборота
	int m_iScroll;
};

//! тип функции обработчика
typedef HANDLER_CODE_RETURN(*HandlerMouse) (IComponent*, const CHandleMouseData *pMouseData);

//**************************************************************************

//! коды сообщений клавиатуры
enum CODE_MESSAGE_KEY
{
	CODE_MESSAGE_KEY_NONE,

	//! клавиша зажата
	CODE_MESSAGE_KEY_DOWN,

	//! клавиша отпущена
	CODE_MESSAGE_KEY_UP,
};

#include "vk.h"

//! структура с данными для сообщения от клавиатуры
struct CHandleKeyData
{
	CHandleKeyData(){ m_key = VKEY_NULL; m_isFirstDown = true; }

	//! код клавиши
	VKEY m_key;

	//! нажата ли клавиша впервые
	bool m_isFirstDown;
};

//! тип функции обработчика для сообщений от клавиатуры
typedef HANDLER_CODE_RETURN(*HandlerKey) (IComponent*, const CHandleKeyData *pKeyData);

//**************************************************************************

//! интерфейс для работы с обработчиками
struct IHandle : public virtual IControl
{
	virtual ~IHandle(){};

	//! добавить обработчик для сообщений мыши
	virtual void addHandlerMouse(CODE_MESSAGE_MOUSE codeMsgMouse, HandlerMouse fnHandler) = 0;

	//! добавить обработчик для сообщений клавиатуры
	virtual void addHandlerKey(CODE_MESSAGE_KEY codeMsgKey, HandlerKey fnHandler) = 0;

	/*! добавить обработчик таймера
	 \param uiMlsec время в милисекундах
	 \param fnHandler функция обработчик
	 \param idTimer числовой идентификатор таймера
	 \note Если идентификатор указан -1 значит будет сгенерирован свой уникальный идентификатор на момент генерации среди существующих таймеров для данного элемента,
	  не рекомендуется использовать если будет установлено несколько таймеров
	 \note Если таймер с таким идентификаторов существует, то функция старая функция-обработчик будет заменена
	 \note Если надо просто посылать сообщение в цикл сообщений то fnHandler можно не указывать
	*/
	virtual void addHandlerTimer(UINT uiMlsec, HandlerTimer fnHandler, ID idTimer=-1) = 0;
};

//#############################################################################

/*! \name Подгон объекта под стороны объекта (X - по ширине, Y - по высоте)
@{*/

//! к левому краю
#define ADJUSTPOS_X_LEFT	-1

//! по центру (по ширине)
#define ADJUSTPOS_X_CENTER	0

//! к правому краю
#define ADJUSTPOS_X_RIGHT	1


//! к верху
#define ADJUSTPOS_Y_TOP		-1

//! к центру (по высоте)
#define ADJUSTPOS_Y_CENTER	0

//! к низу
#define ADJUSTPOS_Y_BOTTOM	1

//!@}

/*! \name Дефайны курсоров
@{*/

//! удалить курсор
#define CURSOR_EMPTY	-2

//! стандартный курсор
#define CURSOR_NULL		-1

//! курсор со стрелкой
#define STD_CURSOR_ARROW	0

//! перекрестье
#define STD_CURSOR_CROSS	1

//! вставка текста
#define STD_CURSOR_IBEAM	2

//! стрелки (верхняя нижняя и нижняя левая)
#define STD_CURSOR_SIZENESW	3

//! стрелки (верхняя левая и правя нижняя)
#define STD_CURSOR_SIZENWSE	4

//! горизонтальные стрелки
#define STD_CURSOR_SIZEWE	5

//! вертикальные стрелки
#define STD_CURSOR_SIZENS	6

//! стрелки в 4 стороны
#define STD_CURSOR_SIZEALL	7

//! стрелка вверх
#define STD_CURSOR_UPARROW	8

//! песочные часы
#define STD_CURSOR_WAIT		9

//! рука
#define STD_CURSOR_HAND		10

//! стрелка с вопросом
#define STD_CURSOR_HELP		11

//!@}

/*! интерфейс component - расширенное управление (позиция, графика, габариты и прочее)
*/
struct IComponent : public virtual IHandle
{
	virtual ~IComponent(){};

	//! действителен ли элемент
	virtual bool getEnable() = 0;

	//! установка действительности элемента
	virtual void setEnable(bool isEnable) = 0;


	/*! устанавливает область окна RECT элемента в глобальных координатах
	 \param pRect устанавливаемый RECT
	 \param isBoundScreen использовать ли только рабочую область (рабочий стол кроме панели задач)
	*/
	virtual bool setWinRect(const RECT *pRect, bool isBoundScreen) = 0;

	//! возвращает область окна RECT элемента в глобальных координатах
	virtual void getWinRect(RECT *pRect) = 0;

	/*! устанавливает клиентскую область RECT элемента в глобальных координатах
	 \param pRect устанавливаемый RECT
	 \param isBoundScreen использовать ли только рабочую область (рабочий стол кроме панели задач)
	*/
	virtual bool setClientRect(const RECT *pRect, bool isBoundScreen) = 0;	

	//! возвращает клиентскую область RECT элемента в глобальных координатах
	virtual void getClientRect(RECT *pRect) = 0;

	//! в pPoint запишет позицию левого верхнего угла
	virtual void getPos(POINT *pPoint) = 0;

	//! в pSize запишет размеры (x - ширина, y - высота)
	virtual void getSize(POINT *pSize) = 0;

	//! устанавливает позицию левого верхнего угла
	virtual void setPos(const POINT *pPoint) = 0;

	//! устанавливает размеры (x - ширина, y - высота)
	virtual void setSize(const POINT *pSize) = 0;

	/*! установка позиции элемента относительно сторон своего родителя
	 \param iAdjustX - подгон по ширине (ADJUSTPOS_X_)
	 \param iAdjustY - подгон по высоте (ADJUSTPOS_Y_)
	*/
	virtual void adjustPos(int iAdjustX, int iAdjustY) = 0;


	/*! \name всплывающая подсказка
	 \note первая установка видимости #setShowHint(true) либо первая устновка текста #setHintText инициализируют объект подсказки, до того как подсказки инициализированы функция #getHintText записывают/возвращают 0
	@{*/

	//! установка состояния видимости подсказки
	virtual void setShowHint(bool isShowHint) = 0;

	//! возвращает: видима ли подсказка?
	virtual bool getShowHint() = 0;		


	//! установить текст подсказки
	virtual void setHintText(const char *szText) = 0;

	//! возвращает текст текущей подсказки
	virtual const char* getHintText() = 0;

	//!@}

	/*! установить курсор
	 \param idCursor идентификатор курсора, дефайны STD_CURSOR_ для установки стандартных курсоров, либо дефайны CURSOR_, либо идентификатор курсора из ресурсов
	*/
	virtual void setCursor(ID idCursor) = 0;

	//! возвращает идентификатор курсора
	virtual ID getCursor() = 0;

	
	/*! \name Методы для цветов элемента
	@{*/

	//! установка цвета фона
	virtual bool setColorBrush(UINT uColor) = 0;			

	//! возвращает текущее значение цвета фона
	virtual UINT getColorBrush() = 0;						

	//! возвращает нативный дескриптор "кисти" фона (HBRUSH)
	virtual NativeHandle getBrush() = 0;							

	//!@}


	/*! \name Позиция объекта относительно родителя
	 \тщеу По дефолту объектпривязывается к левому верхнему углу родителя
	@{*/

	/*! обновление координат и размеров элемента относительно его родителя
	 \note обычно вызывается установленными обработчиками, причем внутренними, напрямую пользователем не вызывается
	*/
	virtual void updateSize() = 0;

	/*! обновление внутрненних данных для #updateSize
	 \note напрямую пользователем не вызывается
	*/
	virtual void updateRect() = 0;


	//! закрепление сторон элемента за позициями его родителя, если сторона закреплена, то будет реагировать на изменения размеров родителя, по умолчанию все false
	virtual void setFollowParentSides(bool canTop, bool canBottom, bool canRight, bool canLeft) = 0;
	
	//! закрепление стороны элемента за позициями его родителя
	virtual void setFollowParentSide(SIDE side, bool can) = 0;

	//! закреплена ли сторона за родителем?
	virtual bool getFollowParentSide(SIDE side) = 0;

	//!@}


	/*! \name Данные регулирующие будет ли передвигаться определнная сторона при изменении размеров с этой стороны
	 \note true - можно тянуть за сторону изменяя размер, false - тянуть за сторону не получится
	@{*/

	//! установка возможности растягивать элемент за стороны, по умолчанию все true
	virtual void setStretchSides(bool canTop, bool canBottom, bool canRight, bool canLeft) = 0;

	//! установка возможности растягивать элемент за сторону
	virtual void setStretchSide(SIDE side, bool can) = 0;

	//! возвращает можно ли растягивать элемент за сторону
	virtual bool getStretchSide(SIDE side) = 0;

	//!@}


	//! установить минимальные размеры окна, установливать надо оба, один работать не будет, по умолчанию 0 - нет минмума
	virtual void setMinSize(UINT uMinWidth, UINT uMinHeght) = 0;

	//! возвращает минимальную ширину
	virtual UINT getMinWidth() = 0;

	//! возвращает минимальную высоту
	virtual UINT getMinHeight() = 0;
};

//##########################################################################

/*! \name Стили оформления текста
@{*/

//! без стилей
#define TEXTUAL_STYLE_NONE		0

//! курсив
#define TEXTUAL_STYLE_ITALIC	0x00000001

//! подчеркнутый
#define TEXTUAL_STYLE_UNDERLINE	0x00000008

//! зачеркнутый
#define TEXTUAL_STYLE_STRIKEOUT	0x00000010

//!@}


//!  нормальная толщина шрифта
#define TEXTUAL_BOLD_NORMAL	400

//! получжирный шрифт
#define TEXTUAL_BOLD_HALF	700

//! жирный шрифт
#define TEXTUAL_BOLD_HEAVY	900


/*! элемент содержащий текст, название, и его управление */
struct ITextual : public virtual IComponent
{
	virtual ~ITextual(){};

	//! установка текста
	virtual bool setText(const char *szStr) = 0;

	//! записывает в szBuf текущий текст элемента, не больше iSize
	virtual void getText(char *szBuf, int iSize) = 0;

	//! возвращает размер строки
	virtual int getTextLen() = 0;


	/*! установка шрифта (с указанием значений)
	 \param szName имя шрифта, если name == 0 то не изменияем название шрифта, если name[0] == 0 то дефолтный шрифт gui
	 \param iHeight высота, если -1 то не учитываются
	 \param iWidth ширина, если -1 то не учитываются
	 \param iWeight толщина от 1 до 1000 (400 - нормальный, 700 - полужирный), если -1 то не учитываются, 0 - толщина по умолчанию (TEXTUAL_BOLD_)
	 \param uStyle стиль оформления текста (TEXTUAL_STYLE_)
	*/
	virtual void setFont(const char *szName, int iHeight, int iWidth, int iWeight = TEXTUAL_BOLD_NORMAL, UINT uStyle = TEXTUAL_STYLE_NONE) = 0;

	//! наследуется ли шрифт родителя
	virtual bool hasParentFont() = 0;

	//! установка родительского шрифта
	virtual void setParentHFont() = 0;


	//! установка цвета текста
	virtual void setColorText(UINT uColor) = 0;

	//! возвращает текущее значение цвета текста
	virtual UINT getColorText() = 0;


	//! установка прозрачности заднего фона
	virtual void setTransparentTextBk(bool isTransparent) = 0;

	//! установлена ли прозрачность заднего фона?
	virtual bool getTransparentTextBk() = 0;


	//! установка цвета заднего фона текста
	virtual void setColorTextBk(UINT uColor) = 0;

	//! возвращает текущее значение цвета заднего фона текста
	virtual UINT getColorTextBk() = 0;
};

//#############################################################################

//! размер текста подсказки #IHint
#define HINT_COUNT_BUF_SIZE 1024

//! элемент "Hint" - всплывающая подсказка при наведении на элемент
struct IHint : public IBaseObject
{
	virtual ~IHint(){}

	/*! установка времени ожидания и показа (время в милисекундах)
	 \param uInit сколько ждать до появления подсказки после наведения курсора
	 \param uAutopop время показа
	*/
	virtual void setDelayTime(UINT uInit, UINT uAutopop) = 0;

	//! устанавливает родителя (при наведении на родителя всплывает эта подсказка)
	virtual bool setParent(IControl *pParent) = 0;

	//! возвращает родителя
	virtual IControl* getParent() = 0;

	//! возвращает нативный дескриптор
	virtual NativeHandle getNativeHandle() = 0;

	//! установка видимости
	virtual void setVisible(bool isVisible) = 0;		

	//! видно ли?
	virtual bool getVisible() = 0;				


	//! установка текста подсказки
	virtual void setText(const char *szStr) = 0;		

	//! возвращает указатель на текущий текст подсказки, очищается при вызове деструктора
	virtual const char* getText() = 0;				

	//! записывает в buf текущий текст подсказки
	virtual void getText(char *szBuf) = 0;			
};

//#############################################################################
//#############################################################################
//#############################################################################

//! внешний вид окна
enum WND_STYLE
{
	//! стиль обычного окна, имеющего название, кнопки свернуть/развернуть/закрыть и возможность растягивать
	WND_STYLE_DEFAULT = 0,

	//! стиль окна только с рабочей областью
	WND_STYLE_AREA,

	//! стиль окна с рабочей областью и рамкой
	WND_STYLE_AREA_BORDER,

	//! стиль окна с рабочей областью и впалой рамкой
	WND_STYLE_AREA_BORDER_SUNKEN,

	//! стиль диалогового окна, с названием и кнопкой закрыть
	WND_STYLE_DIALOG,

	//! стиль диалогового окна, с названием и кнопками свернуть/закрыть
	WND_STYLE_DIALOG_MINIMIZE,

	//! стиль диалогового окна с меньшим по высоте заголовоком, с названием и кнопкой закрыть
	WND_STYLE_MINDIALOG,

	WND_STYLE_COUNT
};

/*! элемент "Window" - окно
*/
struct IWindow : public virtual ITextual
{
	virtual ~IWindow(){};

	/*! \name Прозрачность окна
	 \note Коэфициент прозрачности лежит в пределах [0,1] где 0 - полностью прозрачное, 1 - полностью непрозрачное
	@{*/

	//! установить коэфициент прозрачности
	virtual bool setAlpha(float fAlpha) = 0;

	//! возвращает коэфициент прозрачности
	virtual float getAlpha() = 0;

	//! установка прозрачного стиля (true - использовать коэфициент прозрачности, false - не использовать)
	virtual bool setAlphaBlend(bool isBlend) = 0;

	//! установлен ли прозрачный стиль?
	virtual bool getAlphaBlend() = 0;
	
	//!@}


	//! установка/снятие окна поверх остальных
	virtual void setTopMost(bool isTopMost) = 0;

	//! возвращает установлено ли окно поверх остальных
	virtual bool getTopMost() = 0;

	//! установить стиль окна #WND_STYLE
	virtual void setStyle(WND_STYLE style) = 0;

	//! возвращает установленный стиль окна #WND_STYLE
	virtual WND_STYLE getStyle() = 0;

	//! установить главное меню
	virtual bool setMenu(IMenuWindow *pMenu) = 0;

	//! установить текущее контекстное меню
	virtual bool setCurrCMenu(IMenuPopup *pCMenu) = 0;

	//! получить текущее контекстное меню
	virtual IMenuPopup* getCurrCMenu() = 0;

	//! добавить обработчик изменения размеров окна
	virtual void addHandlerSize(HandlerExWindow fnHandler) = 0;

	//! обработчик взова контекстного меню (клик ПКМ в рабочей области окна)
	virtual void addHandlerCallCMenu(HandlerExWindow fnHandler) = 0;

	//! добавить обработчик закрытия окна
	virtual void addHandlerExit(HandlerExWindow fnHandler) = 0;
};

//#############################################################################

//! элемент "Static" простое текстовое поле без возможности пользовательского редактирования, также можно создать линию (горизонтальную/вертикальную)
struct IStatic : public virtual ITextual
{
	virtual ~IStatic(){}

	//! возвращает тип выравнивания текста #TEXT_ALIGN
	virtual TEXT_ALIGN getAlign() = 0;

	//! устанавливает выравнивание текста #TEXT_ALIGN
	virtual bool setAlign(TEXT_ALIGN align) = 0;


	//! установлен ли автоперенос строк
	virtual bool getWordWrap() = 0;

	//! манипуляция со свойством автоперенос строк
	virtual bool setWordWrap(bool isWordWrap) = 0;
};

//#############################################################################

//! Типы загружаемого фона элемента #ISXGUIButton
enum BUTTON_IMAGE
{
	//! не использовать загружаемый фон
	BUTTON_IMAGE_NONE = 0,

	//! загружать иконку (.ico)
	BUTTON_IMAGE_ICON = 1,

	//! загружать изображение (.bmp)
	BUTTON_IMAGE_BITMAT = 2,
};

//! элемент "button" - кнопка
struct IButton : public virtual ITextual
{
	virtual ~IButton(){}

	//! загрузка на фон иконки (.ico)
	virtual bool setIconFromFile(const char *szPath) = 0;	

	//! загрузка на фон изображения (.bmp)
	virtual bool setBmpFromFile(const char *szPath) = 0;

	//! подгрузка на фон иконки (.ico) из ресурсов
	virtual bool setIconFromResourse(UINT idRes) = 0;		

	//! подгрузка на фон изображения (.bmp) из ресурсов
	virtual bool setBmpFromResourse(UINT idRes) = 0;

	//! добавить обработчик при активации кнопки
	virtual void addHandlerActivated(HandlerExCommon fnHandler) = 0;
};

//#############################################################################

//! элемент "Edit" - текстовове поле с возможностью пользовательского редактирования
struct IEdit : public virtual ITextual
{
	virtual ~IEdit(){}

	//! установлено ли свойство "только для чтения"
	virtual bool getReadOnly() = 0;

	//! манипулирует свойством "только для чтения", возвращает результат действия
	virtual bool setReadOnly(bool isReadOnly) = 0;


	//! установлено ли свойств скрытия текста, текст заменяется на *
	virtual bool getStatePassword() = 0;

	//! манипулирует свойством скрытия текста, текст заменяется на *
	virtual bool setStatePassword(bool IsStatePassword) = 0;


	//! возвращает флаг выравнивания текста #TEXT_ALIGN
	virtual TEXT_ALIGN getAlign() = 0;

	//! устанавливает выравнивание #TEXT_ALIGN
	virtual bool setAlign(TEXT_ALIGN align) = 0;
};

//#############################################################################

//! элемент "UpDown" - кнопки увеличения/уменьшения, обычно используется совместно с элементом #IEdit
struct IUpDown : public virtual IComponent
{
	virtual ~IUpDown(){}

	//! установка минимального и максимального значений
	virtual void setMinMax(int iMin, int iMax) = 0;

	//! устанавливает текущую позицию (число)
	virtual int setPos(int iPos) = 0;


	//! возвращает минимальное число
	virtual int getMin() = 0;

	//! возвращает максимальное число
	virtual int getMax() = 0;

	//! возвращает текущую позицию (число)
	virtual int getPos() = 0;
};

//#############################################################################

//! элемент "Memo" - текстовое поле с возможностью создания новых строк
struct IMemo : public virtual IEdit
{
	virtual ~IMemo(){}

	//! установлен ли автоперенос слов
	virtual bool getWordWrap() = 0;

	//! установка свойства автопереноса слов
	virtual bool setWordWrap(bool isWordWrap) = 0;
};

//#############################################################################

//! элемент "ComboBox" - раскрывающийся список с возможностью едиинчного выбора
struct IComboBox : public virtual ITextual
{
	virtual ~IComboBox(){}

	//! вставка текста в строку
	virtual bool insertItem(ID idItem, const char *szStr) = 0;

	//! удаление строки
	virtual bool deleteItem(ID idItem) = 0;

	//! количество строк
	virtual int getCount() = 0;									


	//! выделяет определенную строку
	virtual bool setSel(ID idItem) = 0;

	//! номер выделенной строки
	virtual ID getSel() = 0;									


	//! установка для строки userdata
	virtual bool setItemData(ID idItem, LONG lData) = 0;

	//! получение userdata строки
	virtual LONG getItemData(ID idItem) = 0;


	//! удаляет все элементы
	virtual bool clear() = 0;									


	//! вставка текста в строку, подобие замены
	virtual bool setItemText(ID idItem, const char *szStr) = 0;

	//! получить текст из строки 
	virtual void getItemText(ID idItem, char *szBuf) = 0;

	//! получить длину текста из строки
	virtual int getItemTextLength(ID idItem) = 0;

	//! добавляет в конец новую строку
	virtual bool addItem(const char *szStr) = 0;					
};

//#############################################################################

//! элемент "ListBox" - список с возможностью выбора (как единичного так и множественного)
struct IListBox : public virtual ITextual
{
	virtual ~IListBox(){}

	//! установленно ли свойство множественного выделения строк
	virtual bool getStateMultiSel() = 0;
	
	/*! установка состояния мультивыделения
	 \todo протестировать изменение состояния мультивыделения
	*/
	virtual void setStateMultiSel(bool isMultiSel) = 0;


	//! вставить текст в строку с номером index
	virtual bool insertItem(ID idString, const char *szText) = 0;

	//! добавить строку в конец списка
	virtual bool addItem(const char *szText) = 0;

	//! возвращает количество строк
	virtual int getItemCount() = 0;


	//! удалить строку с номером idString
	virtual bool deleteItem(ID idString) = 0;


	//! выделить строку с номером idString
	virtual bool setSel(ID idString) = 0;
	
	//! возвращает индекс выделенной строки
	virtual int	getSel() = 0;


	//! установить userdata для строки с номером idString
	virtual bool setItemData(ID idString, LONG lData) = 0;

	//! возвращает userdata
	virtual LONG getItemData(ID idString) = 0;


	//! очистить 
	virtual bool clear() = 0;								


	//! установить текст в строке с номером idString
	virtual bool setItemText(ID idString, const char *szText) = 0;

	//! возвращает текст из строки idString
	virtual void getItemText(ID idString, char *szBuf) = 0;


	//! возвращает длину текста в строке
	virtual int getItemTextLength(ID idString) = 0;


	//! возвращает количество выделенных строк, если #getMultipleSel() == true
	virtual int	getMultiSelCount() = 0;					

	//! устанавливает выделена/не выделена строка
	virtual bool setMultiSel(ID idString, bool sel) = 0;

	//! возвращает выделена ли строка
	virtual bool getMultiSel(ID idString) = 0;

	/*! инициализирует ppArr и записывает массив с номерами выделенных строк, возвращает размер массива
	 \todo придумать как упростить, и желательно перевести на String
	*/
	virtual int getMultiSelArr(int **ppArr) = 0;			
};

//#############################################################################

//! элемент "ListView" - таблица с возможностью выбора
struct IListView : public virtual ITextual
{
	virtual ~IListView(){}

	/*! вставить столбец по индексу
	 \todo надо заюзать выделение на стеке через alloca или calloc, а сейчас new
	*/
	virtual int insertColumn(const char *szText, int iColumn, int iWidth) = 0;	

	//! добавить (последним) столбец
	virtual int addColumn(const char *szText, int iWidth) = 0;

	//! удалить столбец по индексу
	virtual void deleteColumn(int iColumn) = 0;

	//! количество столбцов
	virtual int getColumnsCount() = 0;


	//! добавить строку
	virtual int addString(LONG lData = -1) = 0;

	//! удалить строку
	virtual void deleteString(int iString) = 0;

	//! количество строк
	virtual int getStringCount() = 0;


	//! установить текст в ячейку
	virtual void setItemText(const char *szText, int iColumn, int iString) = 0;

	//! получить текст из ячейки
	virtual void getItemText(char *szText, int iColumn, int iString, int iSizeBuff) = 0;


	//! установить userdata на строку
	virtual void setItemData(int iString, LONG lData) = 0;

	//! возвращает userdata строки iString
	virtual LONG getItemData(int iString) = 0;


	//! возвращает индекс первого найденного выделения после iStart (-1 - значит сначала искать)
	virtual int getSelString(int iStart = -1) = 0;	

	//! выделение строки по индексу
	virtual void setSelString(int iString) = 0;

	//! возвращает индекс выделеного столбца
	virtual int getSelColumn() = 0;					

	//! выделение столбца по индексу
	virtual void setSelColumn(int iColumn) = 0;


	//! очистка всей таблицы
	virtual void clear() = 0;						

	//! очистка только строк
	virtual void clearStrings() = 0;				
};

//#############################################################################

//! элемент "GroupBox" - контейнер для других элементов, с рамкой и необязательным заголовком
struct IGroupBox : public virtual ITextual
{
	virtual ~IGroupBox(){}
};

//#############################################################################

//! элемент "ProgressBar" - полоса состояния/прогресса выполнения чего либо
struct IProgressBar : public virtual IComponent
{
	virtual ~IProgressBar(){}

	//! возвращает текущую позицию прогресса
	virtual int getPos() = 0;				

	//! устанавливает новую и возвращает старую позицию прогресса
	virtual int setPos(int iPos) = 0;		


	//! возвращает текущий размер шага
	virtual int getStep() = 0;				

	//! устанавливает новый и возвращает старый размер шага
	virtual int setStep(int iStep) = 0;		


	//! установить позицию по количеству шагов, возвращает предшествующую позицию
	virtual int setPosSteps(int iSteps) = 0;	

	//! увеличить позицию на один шаг, возвращает предшествующую позицию
	virtual int setOneStep() = 0;			


	/*! устанавливает позицию минимума и максимума прогресса
	 \return При удачном выполнении возвращает true, иначе false 
	 */
	virtual bool setMinMax(int iMin, int iMax) = 0;


	//! возвращают минимальную позицию прогресса
	virtual int getMin() = 0;	

	//! возвращают максимальную позицию прогресса
	virtual int getMax() = 0;	

	
	//! установить цвет полоски, при удачном выполнении возвращает true, иначе false
	virtual bool setColorBar(UINT uColor) = 0;

	//! получить цвет полоски
	virtual UINT getColorBar() = 0;


	//! установить цвет фона, при удачном выполнении возвращает true, иначе false
	virtual bool setColorBk(UINT uColor) = 0;

	//! возвращает цвет фона
	virtual UINT getColorBk() = 0;
};

//#############################################################################

//! элемент "RadioButton" - переключа́тель (с необязательной подписью), позволяет выбрать одну опцию  из предопределенного набора (таких же RadioButton'ов у одного родителя)
struct IRadioButton : public virtual IButton
{
	virtual ~IRadioButton(){}

	//! установка отметки
	virtual void setCheck(bool check) = 0;	

	//! возвращает отмечен ли
	virtual bool getCheck() = 0;			
};

//#############################################################################

//! Состояния выделения элемента #ICheckBox
enum CHECKBOX_STATE
{
	//! не отмечен
	CHECKBOX_STATE_UNCHECKED = BST_UNCHECKED,			

	//! отмечен
	CHECKBOX_STATE_CHECKED = BST_CHECKED,				

	//! неопределен
	CHECKBOX_STATE_INDETERMINATE = BST_INDETERMINATE,	
};


//! элемент "CheckBox" - "галочка" (с необязательной подписью) с возможностью выбора состояния отметки
struct ICheckBox : public virtual IButton
{
	virtual ~ICheckBox(){}

	//! установка состояния отметки #CHECKBOX_STATE
	virtual void setCheckEx(CHECKBOX_STATE check) = 0;

	//! установка состояния отметки
	virtual void setCheck(bool isCheck) = 0;

	//! возвращает состояние отметки CHECKBOX_STATE
	virtual CHECKBOX_STATE getCheck() = 0;
};

//#############################################################################

//! элемент "TrackBar" - ползунок
struct ITrackBar : public virtual IComponent
{
	virtual ~ITrackBar(){}

	//! устанавливает позицию
	virtual void setPos(int iPos) = 0;	

	//! возвращает текущую позицию
	virtual int getPos() = 0;			


	//! устанавливает минимальное (левое) и максимальное (правое) значения позиции
	virtual void setMinMax(int iMin, int iMax) = 0;	

	//! возвращает текущее минимальное (левое) значение позиции
	virtual int getMin() = 0;			

	//! возвращает текущее максимальное (правое) значение позиции
	virtual int getMax() = 0;			


	/*! установка риски в позиции (между минимумом и максимумом)
	 \note Элемент trackbar создает две крайние риски сам (если пределы от минуса (-100 к примеру) до плюса (100 к примеру) то тогда будет создана третья риска в нуле)
	*/
	virtual bool setTick(int iPos) = 0;	

	//! возвращает позициюю риски (между минимумом и максимумом) по индексу риски
	virtual int getTick(int iIndex) = 0;	

	//! установка промежутков между рисками, значения указываются в интервалах приращения (пунктах)
	virtual void setTickFrequency(int iFreq) = 0;	
};

//#############################################################################

//! Выравнивание составных частей внутри #IStatusBar при изменении размеров
enum STATUSBAR_ALIGN_RESIZE
{
	//! без изменений
	STATUSBAR_ALIGN_RESIZE_NONE = 0,

	//! в процентном соотношениям к текущему состоянию
	STATUSBAR_ALIGN_RESIZE_PERCENT = 1,

	//! равномерно одинаково
	STATUSBAR_ALIGN_RESIZE_EQUALLY = 2,	
};

/*! элемент "StatusBar" - горизонтальная полоса в нижней части родительского окна, в ней может отображать различные виды информации о состоянии
 \todo отрефакторить реализацию
*/
struct IStatusBar : public virtual ITextual
{
	virtual ~IStatusBar(){}

	/*! установка количества частей и их размеров
	 \param iCount количество частей, размер pArr
	 \param pArr массив с размерами в пикселях по ширине каждой части
	*/
	virtual bool setPartsCount(int iCount, int *pArr) = 0;

	//! инициализирует ppArr (если ppArr != 0) и записывает в него позиции (правая сторона клиентской области) каждой части, возвращает количество частей 
	virtual int getPartsCount(int **ppArr) = 0;
	
	/*! устанавливает в часть текст
	 \param iPos номер части
	 \param szText текст
	*/
	virtual bool setPartText(int iPos,const char *szText) = 0;

	//! в szBuf записывает текст части iPos, iLenBuf - размер szBuf
	virtual bool getPartText(int iPos, char *szBuf, int iLenBuf) = 0;

	//! обновление с учетом установленного выравнивания, вызывать при изменении размеров
	virtual void update() = 0;		

	//! аналогично #Update
	virtual void updateSize() = 0;	


	//! устанавливает выравнивание при изменении размеров #STATUSBAR_ALIGN_RESIZE
	virtual void setAlignReSize(STATUSBAR_ALIGN_RESIZE alignResize) = 0;

	//! возвращает выравнивание при изменении размеров #STATUSBAR_ALIGN_RESIZE
	virtual STATUSBAR_ALIGN_RESIZE getAlignReSize() = 0;
};

//#############################################################################

/*! элемент "ToolBar" - панель инструментов
 \warning Добавлен для полноты объектов, будет дорабьатываться, текущий функционал не прошел достаточное тестирование
 \todo Доделать #IToolBar
*/
struct IToolBar : public virtual IComponent
{
	virtual ~IToolBar(){}
};

//**************************************************************************

//! структура данных передаваемая в обработчик сообщений от меню
struct CHandlerMenuData
{
	CHandlerMenuData(){ m_idSelected = -1;}
	
	//! id выбранного элемента
	ID m_idSelected;
};

//! тип функции обработчика сообщения меню
typedef int(*HandlerMenu) (IMenuBase*, const CHandlerMenuData *);

//! коды сообщений меню
enum CODE_MSG_MENU
{
	//! перед показом меню, дана команда на открытие
	CODE_MSG_MENU_OPEN,

	//! выбран пункт меню
	CODE_MSG_MENU_SELECT,

	//! после закрытия меню, дана команда на закрытие
	CODE_MSG_MENU_CLOSE
};

//! базовый интерфейс меню
struct IMenuBase : public IBaseObject
{
	virtual ~IMenuBase(){}

	/*! вставить элемент меню
	 \param iIndex индекс позиции
	 \param szText текст элемента
	 \param idUnit идентификатор элемента меню
	 \param idSubUnit идентификатор подменю
	*/
	virtual bool insertItem(int iIndex, const char *szText, ID idUnit, ID idSubUnit=-1) = 0;

	/*! вставить элемент от которого пойдет контекстное меню
	 \param iIndex индекс позиции
	 \param szText текст элемента
	 \param idUnit идентификатор элемента меню
	 \param idSubUnit идентификатор подменю
	*/
	virtual bool insertPopupItem(int iIndex, const char *szText, ID idUnit, ID idSubUnit=-1) = 0;

	/*! вставить разделитель
	 \param iIndex индекс позиции
	 \param idUnit идентификатор элемента меню
	 \param idSubUnit идентификатор подменю
	*/
	virtual bool insertSeparator(int iIndex, ID idUnit, ID idSubUnit=-1) = 0;

	//! удалить элемент меню по его id
	virtual bool deleteItem(ID idUnit) = 0;

	//! возвращает нативный дескриптор подменю (HMENU) по его id
	virtual NativeHandle getSubMenu(ID idUnit) = 0;


	//! выделить элемент меню
	virtual bool setCheckItem(ID idUnit, bool isCheck) = 0;

	//! установить действительность элементу меню
	virtual bool setEnableItem(ID idUnit, bool isEnable) = 0;


	//! выделен ли элемент меню idUnit
	virtual bool getCheckedItem(ID idUnit) = 0;

	//! действителен ли элемент меню idUnit
	virtual bool getEnabledItem(ID idUnit) = 0;


	//! возвращает дескриптор меню
	virtual NativeHandle getNativeHandle() = 0;


	//! добавить обработчик
	virtual void addHandler(CODE_MSG_MENU codeMsg, HandlerMenu fnHandler) = 0;
};

//**************************************************************************

//! главное меню
struct IMenuWindow : public virtual IMenuBase
{
	virtual ~IMenuWindow(){}
};

//**************************************************************************

//! элемент "PopupMenu" - контекстное меню
struct IMenuPopup : public virtual IMenuBase
{
	virtual ~IMenuPopup(){}

	/*! показать меню
	 \param pWindow окно которое обрабатывает сообщения от этого меню
	 \param iX позиция по оси x (screen space)
	 \param iY	позиция по оси y (screen space)
	*/
	virtual bool track(IWindow *pWindow,int iX,	int iY) = 0;

	virtual void setTargetComponent(IComponent *pComponent) = 0;
	virtual IComponent* getTargetComponent() = 0;
};

//!@} sxguiwinapi_elements

//##########################################################################
//##########################################################################
//##########################################################################

//! типы диалогов выбора файлов
enum DIALOG_TYPE
{
	//! открыватие файла
	DIALOG_TYPE_OPEN = 0,

	//! сохранение файла 
	DIALOG_TYPE_SAVE = 1,
};

//**************************************************************************

//! менеджер управляющий созданием элементов
struct IManager
{
	/*! создает экземплляр объекта "Window", и возвращает указатель
	 \param style - стиль окна
	 \param pParent - родитель, если окно главное то родитель NULL
	 \param isTopMost - поверх всех окон
	*/
	virtual IWindow* newWnd(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, WND_STYLE style = WND_STYLE_DEFAULT, bool isTopMost=false) = 0;

	//**********************************************************************

	virtual IButton* newButton(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent, BUTTON_IMAGE typeImage = BUTTON_IMAGE_NONE) = 0;

	/*! создает экземплляр объекта "CheckBox", и возвращает указатель
	\param is3State - может ли элемент иметь третье состояние "неопределенный"?
	*/
	virtual ICheckBox* newCheckBox(const char *szCaption, int iPosX, int iPosY, int iWidth, int iHeight, IControl *pParent, bool is3State = false) = 0;

	//! создает экземплляр объекта "RadioButton", и возвращает указатель
	virtual IRadioButton* newRadioButton(const char *szCaption, int iPosX, int iPosY, int iWidth, int iHeight, IControl *pParent) = 0;

	//*************************************************************************

	//! создает экземплляр объекта "Static", и возвращает указатель
	virtual IStatic* newStatic(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent) = 0;

	/*! создает экземплляр объекта "Static" который представлен линией, и возвращает указатель
	\param isVertical - вертикальная линия (true), горизонтальная (false)
	*/
	virtual IStatic* newStaticLine(int iX, int iY, int iWidth, int iHeight, IControl *pParent = 0, bool isVertical = false) = 0;

	//! создает экземплляр объекта "Edit", и возвращает указатель
	virtual IEdit* newEdit(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent) = 0;

	//! создает экземплляр объекта "Memo", и возвращает указатель
	virtual IMemo* newMemo(const char *szCaption, int iX, int iY, int iWidth, int iHeight, IControl *pParent) = 0;

	//**********************************************************************

	/*! создает объект "ListBox"
	 \param isMultipleSel - разрешено ли мультивыделение
	*/
	virtual IListBox* newListBox(int iPosX, int iPosY, int iWidth, int iHeight, IControl *pParent, bool isMultipleSel = false) = 0;

	//! создание объекта "ListView" (таблица)
	virtual IListView* newListView(int iX, int iY, int iWidth, int iHeight, IControl *pParent) = 0;

	//! создание объекта "ComboBox" (выпадающий список)
	virtual IComboBox* newComboBox(int iX, int iY, int iWidth, int iHeight, IControl *pParent) = 0;

	//**********************************************************************

	//! создает экземплляр объекта "ToolBar", и возвращает указатель
	virtual IToolBar* newToolBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent, int iWidthElement, int iHeigthElement) = 0;

	//! создает экземплляр объекта "StatusBar", и возвращает указатель
	virtual IStatusBar* newStatusBar(const char *szCaption, IControl *pParent) = 0;

	//! создает экземплляр объекта "TrackBar", и возвращает указатель
	virtual ITrackBar* newTrackBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent) = 0;

	/*! создает экземплляр объекта "ProgressBar", и возвращает указатель
	\param isVertical true - вертикальное размещение, false - горизонтальное
	\param isSmooth true - сплошная заливка полосы, false - заливка полосы одинаковыми секциями/прямоугольниками
	*/
	virtual IProgressBar* newProgressBar(int iX, int iY, int iWidth, int iHeight, IControl *pParent, bool isVertical = false, bool isSmooth = true) = 0;

	//**********************************************************************

	/*! создает экземплляр объекта "Menu" из ресурсов по идентификатору uResMenu, и возвращает указатель
	 \param uIdRes - идентификатор ресурса, если указано -1 значит загрузки не будет
	*/
	virtual IMenuWindow* newMenuWindow(UINT uIdRes=-1) = 0;

	/*! создает экземплляр объекта "контекстное меню", и возвращает указатель
	 \param uIdRes - идентификатор ресурса, если указано -1 значит загрузки не будет
	 \param iIndex - индекс вложенного меню
	*/
	virtual IMenuPopup* newMenuContext(UINT uIdRes=-1, int iIndex = 0) = 0;

	//######################################################################

	/*! диалог выбора файла
	\note path или name должен быть не 0, иначе результат вызова диалога некуда будет записать и как следствие диалог не будет вызван
	\patam type тип диалога #DIALOG_TYPE
	\patam szPath если не 0 то запишется путь до файла
	\patam szName если не 0 то запишется имя файла
	\patam szStdPath путь относительно которого открывать диалог
	\patam szFilter фильтр расширений
	*/
	virtual void dialogSelectFile(DIALOG_TYPE type, char *szPath, char *szName, const char *szStdPath, const char *szFilter = 0) = 0;
};

//! инициализация менеджера
NATUI_API IManager* ManagerInit();

//! уничтожает менеджер
NATUI_API void ManagerDestroy();

#endif

//!@} natui
