#pragma once

#include <windows.h>
#include "widgetmap.h"
#include "application.h"
#include "string.h"

class WidgetMap;

struct Rect
{
	int x;
	int y;
	int width;
	int height;
};

struct WidgetStyle
{
	std::string class_name;
	Rect widget_size;
	DWORD widget_style;
	DWORD widget_ex_style;
	UINT class_style;
};

class Widget
{
public:
	Widget(WidgetStyle style, Widget* parent = nullptr);

	static WidgetMap widget_map;

	void setGeometry(int x, int y, int width, int height);
	int x();
	int y();
	int width();
	int height();
	HWND getHWND();
	// static wndproc wich call procedure for each widget
	static LRESULT CALLBACK GlobalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

protected:
	HWND m_hwnd; 
	Widget* m_parent;

private:
	WidgetStyle m_style;
	WNDCLASSEX m_wndclass;

	void create();
	void createWidget();
	void registerClass();
};

