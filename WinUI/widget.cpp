#include "widget.h"

WidgetMap Widget::widget_map;

Widget::Widget(const char* class_name, Widget * parent) : m_parent(parent), m_hwnd(nullptr)
{
	createWidget(class_name);
	Widget::widget_map.addWidget(m_hwnd, this);
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

LRESULT CALLBACK Widget::GlobalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void Widget::createWidget(const char* class_name)
{
	m_hwnd = CreateWindowEx(
		WS_OVERLAPPEDWINDOW,
		str_to_wstr(class_name).c_str(),
		L"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_parent ? m_parent->getHWND() : nullptr,
		nullptr,
		Application::getInstance(),
		nullptr
	);
}
