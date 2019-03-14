#pragma once

#include <windows.h>
#include "widgetmap.h"

class WidgetMap;

class Widget
{
public:
	Widget();

	void setGeometry(int x, int y, int width, int height);
	int x();
	int y();
	int width();
	int height();
	HWND getHWND();
	static LRESULT CALLBACK WndProcStatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

	static WidgetMap widget_map;

protected:
	HWND m_hwnd; 
	virtual void createWidget() = 0;
};

