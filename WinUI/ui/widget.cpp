#include "widget.h"

std::map<HWND, Widget*> Widget::widget_map;

Widget::Widget(WidgetStyle style, Widget * parent) : m_style(style), m_parent(parent), m_hwnd(nullptr),
m_isMaxInstalled(false), m_isMinInstalled(false)
{
	create();
	addWidget(m_hwnd, this);
	if (m_parent)
	{
		m_parent->addChild(m_hwnd, this);
	}
}

Widget::~Widget()
{
	removeWidget(m_hwnd);
	DestroyWindow(m_hwnd);
}

void Widget::setGeometry(int x, int y, int width, int height)
{
	SetWindowPos(m_hwnd, NULL, x, y, width, height, NULL);
}

void Widget::setWidth(int width)
{
	SetWindowPos(m_hwnd, NULL, x(), y(), width, height(), NULL);
}

void Widget::setHeight(int height)
{
	SetWindowPos(m_hwnd, NULL, x(), y(), width(), height, NULL);
}

void Widget::setParent(Widget * parent)
{
	if (parent)
	{
		SetParent(m_hwnd, parent->getHWND());
		parent->addChild(m_hwnd, this);
		UpdateWindow(parent->getHWND());
	}
}

void Widget::addChild(HWND hwnd, Widget * widget)
{
	if (hwnd)
	{
		m_child_widgets.insert(std::make_pair(hwnd, widget));
	}
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
	auto widget = getWidgetPtr(hwnd);
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

void Widget::setMinimumSize(int min_width, int min_height)
{
	if (m_isMaxInstalled && (min_width > m_maximumSize.width || min_height > m_maximumSize.height))
		return;

	m_isMinInstalled = true;
	m_minimumSize.width = min_width;
	m_minimumSize.height = min_height;

	if (width() < min_width)
		setWidth(min_width);
	if (height() < min_height)
		setHeight(min_height);
}

void Widget::setMaximumSize(int max_width, int max_height)
{
	if (m_isMinInstalled && (max_width < m_minimumSize.width || max_height < m_minimumSize.height))
		return;

	m_isMaxInstalled = true;
	m_maximumSize.width = max_width;
	m_maximumSize.height = max_height;

	if (width() > max_width)
		setWidth(max_width);
	if (height() > max_height)
		setHeight(max_height);
}

void Widget::addWidget(HWND hwnd, Widget * widget)
{
	if (hwnd)
	{
		Widget::widget_map.insert(std::make_pair(hwnd, widget));
	}
}

void Widget::removeWidget(HWND hwnd)
{
	Widget::widget_map.erase(hwnd);
}

Widget* Widget::getWidgetPtr(HWND hwnd)
{
	auto wgt = Widget::widget_map.find(hwnd);
	return wgt != Widget::widget_map.end() ? wgt->second : nullptr;
}