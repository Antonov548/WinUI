#include "widget.h"

WidgetMap Widget::widget_map;

Widget::Widget(WidgetStyle style, Widget * parent) : m_style(style), m_parent(parent), m_hwnd(nullptr)
{
	create();
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

void Widget::create()
{
	if (!GetClassInfoEx(Application::getInstance(), str_to_wstr(m_style.class_name).c_str(), &m_wndclass))
	{
		registerClass();
	}
	createWidget();
}

void Widget::registerClass()
{
	m_wndclass.cbSize = sizeof(WNDCLASSEX);
	m_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndclass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	m_wndclass.lpfnWndProc = GlobalWndProc;
	m_wndclass.lpszClassName = str_to_wstr(m_style.class_name).c_str();
	m_wndclass.style = m_style.class_style;
	m_wndclass.hIcon = NULL;
	m_wndclass.hIconSm = NULL;
	m_wndclass.lpszMenuName = NULL;
	m_wndclass.cbClsExtra = 0;
	m_wndclass.cbWndExtra = 0;

	RegisterClassEx(&m_wndclass);
}

void Widget::createWidget()
{
	m_hwnd = CreateWindowEx(
		m_style.widget_ex_style,
		str_to_wstr(m_style.class_name).c_str(),
		L"",
		m_style.widget_style,
		m_style.widget_size.x,
		m_style.widget_size.y,
		m_style.widget_size.width,
		m_style.widget_size.height,
		m_parent ? m_parent->getHWND() : nullptr,
		nullptr,
		Application::getInstance(),
		nullptr
	);
}
