
/***********************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017 - 2019
See the license in LICENSE
***********************************************************/

#ifndef __BASE_H
#define __BASE_H

#include <stdio.h>
#include "hint.h"
#include "natUI.h"
#include <common/array.h>

#include "base_control.h"
#include "base_handle.h"
#include "base_component.h"
#include "base_textual.h"

#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))


//##########################################################################

//! обработчик всех сообщений для всех элементов
LRESULT CALLBACK WndProcAllDefault(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! является ли элемент эдитом?
BOOL IsEdit(HWND hWnd);

//##########################################################################

//! установка юзердаты в меню
bool SetUserData4Menu(HMENU hMenu, LONG lUserData);

//! получение юзердаты из меню
LONG GetUserData4Menu(HMENU hMenu);

//##########################################################################

//! установка текста контролу
bool SetText(IControl*const Control, const char* text);

//! в buf записывает текст контрола, count - длина buf
void GetText(IControl *Control, char* buf, int count);

//! возвращает длину текста контрола
int GetTextLen(IControl *Control);

//##########################################################################

//! событие WM_SIZE
BOOL CALLBACK EnumChildProcUpdateSize(HWND hWnd, LPARAM lParam);

//! событие WM_MOVE
BOOL CALLBACK EnumChildProcUpdateRect(HWND hWnd, LPARAM lParam);

//! событие WM_MOUSEMOVE
BOOL CALLBACK EnumChildProcMouseMove(HWND hWnd, LPARAM lParam);

//**************************************************************************

/*! установка основных обработчиков, без которых система будет работать не стабильно, а возможно и не будет работать,
если возвращает 0 значит все в норме, иначе возвращает номер того обработчика который не удалось установить,
данная функция вызывается только если не требуется каких либо дополнительных действий при обработке зарезервированных сообщений
*/
void StdHandlerInitMsg(IComponent *pComponent);


//! структура отправляемая в #EnumChildProcSendMouseMsg2Children в lParam
struct CMsg2EnumChild
{
	UINT m_uMsg;
	WPARAM m_wParam;
	LPARAM m_lParam;
	bool m_isProc;
};

//! функция обработчик передачи сообщения от мыши всем дочерним элементам
BOOL CALLBACK EnumChildProcSendMouseMsg2Children(HWND hWnd, LPARAM lParam);

//! отправка сообщения мыши всем дочерним элементам, возвращает true если кто-то обрабатывает
bool SendMouseMsg2Children(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//! обработчик события WM_SIZE
LRESULT StdHandlerSizeChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*! обработчик событий WM_CTLCOLORSTATIC WM_CTLCOLOREDIT WM_CTLCOLORBTN WM_CTLCOLORLISTBOX,
то есть обработка цветов дочерних элементов окна (static, edit,button, listbox)
*/
LRESULT StdHandlerCtlColorChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! обработчик события WM_SIZING
LRESULT StdHandlerSizingChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! обработчик события WM_MOVE
LRESULT StdHandlerMoveChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! обработчик события WM_MOUSEMOVE
LRESULT StdHandlerMouseMoveChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! обработчик события WM_SETCURSOR
LRESULT StdHandlerSetCursorChange(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! обработчик события WM_COMMAND SC_MAXIMIZE
//LRESULT StdHandlerMaximuzeWinChange(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! обработчик события WM_DESTROY
LRESULT StdHandlerWinDestroy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//##########################################################################

#endif