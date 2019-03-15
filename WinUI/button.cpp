#include "button.h"

Button::Button(Window * parent,const char * text) : Widget(parent), m_text(text)
{
	createWidget();
}

Button::~Button()
{
}

void Button::createWidget()
{
	wchar_t CLASS_NAME[] = L"Button";

	m_hwnd = CreateWindow(
		CLASS_NAME,
		str_to_wstr(m_text).c_str(),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,
		0,
		0,
		80,
		30,
		m_parent->getHWND(),
		NULL,
		(HINSTANCE)GetModuleHandle(NULL),
		NULL);
}

LRESULT Button::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		Widget::widget_map.removeWidget(hwnd);
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void Button::setText(const char * text)
{
	m_text = text;
	SetWindowTextA(m_hwnd, m_text.c_str());
}
