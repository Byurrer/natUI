
#include "base_control.h"

#include "base.h"

CControl::CControl()
{
	m_hWindow = 0;
	m_hParent = 0;
	m_id = -1;
	m_lpfnPrevProc = 0;
	m_isContainer = false;
}

CControl::~CControl()
{
	::DestroyWindow(m_hWindow);
}

void CControl::initControl(GUI_TYPE_ELEMENT typeElement, IControl *pParent, bool isContainer, ID idObj)
{
	m_typeElement = typeElement;

	if (pParent)
		m_hParent = (HWND)(pParent->getNativeHandle());

	UINT uPtrFn = SetWindowLong(m_hWindow, GWL_WNDPROC, (LONG)WndProcAllDefault);
	m_lpfnPrevProc = (WNDPROC)uPtrFn;

	m_isContainer = isContainer;
	m_id = idObj;
}

IControl* CControl::getParent()
{
	IControl *pControl = (IControl*)GetWindowLong(m_hParent, GWL_USERDATA);

	return pControl;
}

bool CControl::setParent(IControl *pParent)
{
	HWND hOldParent = m_hParent;// GetParent(m_hWindow);
	HWND hInitHWND = (HWND)pParent->getNativeHandle();

	//если новый родитель утсановлен, то будет возврашен старый
	if (SetParent(m_hWindow, hInitHWND) == hOldParent)
	{
		m_hParent = hInitHWND;
		return true;
	}

	return false;
}

HWND CControl::getParentHWND()
{
	return m_hParent;
}

SXWINDOW CControl::getNativeHandle()
{
	return m_hWindow;
}

HWND CControl::getHWND()
{
	return m_hWindow;
}

void CControl::setFocus()
{
	::SetFocus(m_hWindow);
}

bool CControl::getFocus()
{
	return GetFocus() == m_hWindow ? true : false;
}

void CControl::setVisible(bool bf)
{
	ShowWindow(m_hWindow, bf ? SW_SHOW : SW_HIDE);
}

bool CControl::getVisible()
{
	return IsWindowVisible(m_hWindow);
}

/*WNDPROC CControl::getPrevWndProc()
{
return m_lpfnPrevProc;
}*/

void* CControl::getUserPtr()
{
	return(m_pUserPtr);
}
void* CControl::setUserPtr(void *ptr)
{
	void * oldPtr = m_pUserPtr;
	m_pUserPtr = ptr;
	return(oldPtr);
}

void* CControl::getPrevWndProc()
{ 
	return m_lpfnPrevProc; 
}

GUI_TYPE_ELEMENT CControl::getElementType()
{
	return m_typeElement;
}