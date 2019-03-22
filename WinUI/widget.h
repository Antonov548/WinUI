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
};

class Widget
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
	WNDCLASSEX wndclass;
	Widget* m_parent;

	virtual void createWidget(const char* class_name);
	virtual void registerClass(const char* class_name);

private:
	void create();

	std::string m_class_name;
};

