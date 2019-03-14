#include "widget.h"

WidgetMap Widget::widget_map;

Widget::Widget() : m_hwnd(nullptr)
{
}

void Widget::setGeometry(int x, int y, int width, int height)
{
	SetWindowPos(m_hwnd, NULL, x, y, width, height, NULL);
}

int Widget::x()
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.left);
}

int Widget::y()
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.top);
}

int Widget::width()
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.right - rect.left);
}

int Widget::height()
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.bottom - rect.top);
}

HWND Widget::getHWND()
{
	return m_hwnd;
}

LRESULT CALLBACK Widget::WndProcStatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Widget* widget = Widget::widget_map.getWidgetPtr(hwnd);
	if (widget)
	{
		return widget->WndProc(hwnd, message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}