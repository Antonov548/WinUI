#pragma once

#include <windows.h>
#include "widgetmap.h"
#include "application.h"
#include "string.h"
#include "registeredwidget.h"

class WidgetMap;

class Widget : public RegisteredWidget
{
public:
	Widget(const char* class_name, Widget* parent = nullptr);

	void setGeometry(int x, int y, int width, int height);
	int x();
	int y();
	int width();
	int height();
	HWND getHWND();
	// static wndproc wich call procedure for each widget
	static LRESULT CALLBACK GlobalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	static WidgetMap widget_map;

protected:
	HWND m_hwnd; 
	Widget* m_parent;
	void createWidget(const char* class_name);
};

