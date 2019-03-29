#include "widgetmap.h"

WidgetMap::WidgetMap()
{
}

WidgetMap::~WidgetMap()
{
}

Widget* WidgetMap::getWidgetPtr(HWND hwnd) const
{
	auto wgt = m_widget_map.find(hwnd);
	return wgt != m_widget_map.end() ? wgt->second : nullptr;
}

void WidgetMap::addWidget(HWND hwnd, Widget * widget)
{
	if (hwnd)
	{
		m_widget_map.insert(std::make_pair(hwnd, widget));
	}
}

void WidgetMap::removeWidget(HWND hwnd)
{
	m_widget_map.erase(hwnd);
}

bool WidgetMap::isEmpty()
{
	return int(m_widget_map.size()) == 0;
}
