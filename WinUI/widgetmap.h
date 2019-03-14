#pragma once

#include <map>
#include <windows.h>
#include "widget.h"

class Widget;

class WidgetMap
{
public:
	WidgetMap();
	~WidgetMap();

	Widget* getWidgetPtr(HWND hwnd) const;
	void addWidget(HWND hwnd, Widget* widget);
	void removeWidget(HWND hwnd);
	bool isEmpty();

private:
	std::map<HWND, Widget*> m_widget_map;
};