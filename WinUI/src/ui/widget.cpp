#include "widget.h"
#include <iostream>

using namespace WinUI;

std::map<HWND, Widget*> Widget::widget_map;

Widget::Widget(WidgetStyle style, Widget * parent) : m_style(style), m_parent(parent), m_hwnd(nullptr),
m_isMaxInstalled(false), m_isMinInstalled(false), m_size(style.widget_size)
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
	if (m_parent)
	{
		m_parent->m_child_widgets.erase(m_hwnd);
	}
	if (!m_child_widgets.empty())
	{
		for (auto& widget : m_child_widgets)
		{
			delete widget.second;
		}
	}
	removeWidget(m_hwnd);
	DestroyWindow(m_hwnd);
}

void Widget::setGeometry(int x, int y, int width, int height)
{
	m_size.x = x;
	m_size.y = y;
	m_size.width = width;
	m_size.height = height;
	SetWindowPos(m_hwnd, NULL, x, y, width, height, NULL);
}

void Widget::setWidth(int width)
{
	m_size.width = width;
	SetWindowPos(m_hwnd, NULL, x(), y(), width, height(), NULL);
}

void Widget::setHeight(int height)
{
	m_size.height = height;
	SetWindowPos(m_hwnd, NULL, x(), y(), width(), height, NULL);
}

void Widget::setFixedSize(int width, int height)
{
	m_isMaxInstalled = true;
	m_isMinInstalled = true;

	m_minimumSize.width = width;
	m_minimumSize.height = height;
	m_maximumSize.width = width;
	m_maximumSize.height = height;

	setWidth(width);
	setHeight(height);
}

void Widget::setParent(Widget * parent)
{
	if (parent)
	{
		DestroyWindow(m_hwnd);
		removeWidget(m_hwnd);

		m_parent = parent;
		parent->addChild(m_hwnd, this);

		recreateWidget();
		addWidget(m_hwnd, this);

		for (auto& child : m_child_widgets)
		{
			child.second->setParent(this);
		}
	}
}

void Widget::setVisible(bool visible)
{
	int show_comand = visible ? SW_SHOW : SW_HIDE;
	ShowWindow(m_hwnd, show_comand);
}

void Widget::addChild(HWND hwnd, Widget * widget)
{
	if (hwnd)
	{
		m_child_widgets.insert(std::make_pair(hwnd, widget));
	}
}

int Widget::x() const
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.left);
}

int Widget::y() const
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.top);
}

int Widget::width() const
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.right - rect.left);
}

int Widget::height() const
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	return int(rect.bottom - rect.top);
}

Rect Widget::size() const
{
	return m_size;
}

HWND Widget::getHWND() const
{
	return m_hwnd;
}

bool Widget::isVisible() const
{
	return bool(IsWindowVisible(m_hwnd));
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
	if (!GetClassInfoEx(Application::getInstance(), m_style.class_name.c_str(), &m_wndclass))
	{
		registerClass(m_style);
	}
	createWidget(m_style);
}

void Widget::recreateWidget()
{
	WidgetStyle style = {
			m_style.class_name,
			m_size,
			m_style.widget_style,
			m_style.class_style
	};
	char text[1024];
	GetWindowText(m_hwnd, text, 1024);
	createWidget(m_style, text);
}

void Widget::registerClass(WidgetStyle style)
{
	m_wndclass.cbSize = sizeof(WNDCLASSEX);
	m_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndclass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	m_wndclass.lpfnWndProc = GlobalWndProc;
	m_wndclass.lpszClassName = m_style.class_name.c_str();
	m_wndclass.style = m_style.class_style;
	m_wndclass.hIcon = NULL;
	m_wndclass.hIconSm = NULL;
	m_wndclass.lpszMenuName = NULL;
	m_wndclass.cbClsExtra = 0;
	m_wndclass.cbWndExtra = 0;

	RegisterClassEx(&m_wndclass);
}

void Widget::createWidget(WidgetStyle style, string text)
{
	m_hwnd = CreateWindowEx(
		m_style.widget_style.extended,
		m_style.class_name.c_str(),
		text.c_str(),
		m_style.widget_style.regular,
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

Style Widget::getStyle() const
{
	return m_style.widget_style;
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

void Widget::setStyle(Style style)
{
	SetWindowLongPtr(m_hwnd, GWL_STYLE, style.regular);
	SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, style.extended);
	m_style.widget_style = style;
}

void Widget::addStyle(Style style)
{
	setStyle(getStyle() + style);
}

void Widget::removeStyle(Style style)
{
	setStyle(getStyle() - style);
}

bool Widget::hasStyle(Style style)
{
	return m_style.widget_style.hasStyle(style);
}

string Widget::getClassName() const
{
	return m_style.class_name;
}

Widget* Widget::getWidgetPtr(HWND hwnd)
{
	auto wgt = Widget::widget_map.find(hwnd);
	return wgt != Widget::widget_map.end() ? wgt->second : nullptr;
}