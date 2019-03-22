#include "button.h"

WidgetStyle Button::button_style = {
	"Button",
	{0, 0, 80, 30},
	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	NULL,
	NULL
};

Button::Button(Window * parent,const char * text) : Widget(button_style, parent), m_text(text)
{
	setText(text);
}

Button::~Button()
{
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
