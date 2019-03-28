
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_CONTROL_H
#define __BASE_CONTROL_H

#include "natUI.h"

/*!
первый базовый класс, единственным родителем не используется
определяет объект как контрол, то есть содержит в себе минимум данных для
управления объектом
*/
class CControl : public virtual IControl
{
public:

	CControl();
	//CControl(HWND hWindow, HWND hParent, WNDPROC lpfnHandler);
	~CControl();

	void Release(){ mem_del(this); }

	//! запоминаем дескрипторы, и устанавливаем новый обработчик
	void initControl(GUI_TYPE_ELEMENT typeElement, IControl *pParent, bool isContainer = false, ID idObj = -1);


	//! возвращает контрол родителя родителя
	IControl* getParent();

	//! устанавливает родителя
	bool setParent(IControl *pParent);

	//! возвращает HWND родителя
	HWND getParentHWND();


	//! возвращает нативный дескриптор объекта, в независимом типе
	NativeHandle getNativeHandle();

	//! возвращает HWND объекта (для использования внутри библиотеки)
	HWND getHWND();


	//! установка видимости контрола
	void setVisible(bool isVisible);

	//! видим ли контрол?
	bool getVisible();


	//! установить фокус на контрол
	void setFocus();

	//! установлен ли фокус на контроле?
	bool getFocus();


	//! получить пользовательские данные
	void* getUserPtr();

	//! установить пользовательские данные, возвращает предыдущее значение
	void* setUserPtr(void *ptr);

	void* getPrevWndProc();

	GUI_TYPE_ELEMENT getElementType();

private:

	//! указатель на пользовательские данные
	void *m_pUserPtr;

	//! пользовательский id объекта
	ID m_id;

protected:

	//! hwnd объекта
	HWND m_hParent;

	//! hwnd родителя
	HWND m_hWindow;

	bool m_isContainer;

	WNDPROC m_lpfnPrevProc;

	GUI_TYPE_ELEMENT m_typeElement;
};

#endif