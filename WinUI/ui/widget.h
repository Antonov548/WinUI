#pragma once

#include <windows.h>
#include <map>
#include "../application.h"
#include "../string.h"

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
	Widget(WidgetStyle style, Widget* parent);
	virtual ~Widget();

	void setGeometry(int x, int y, int width, int height);
	void setWidth(int width);
	void setHeight(int height);
	void setParent(Widget* parent);
	void addChild(HWND hwnd, Widget* widget);
	int x();
	int y();
	int width();
	int height();
	HWND getHWND();
	// static wndproc wich call procedure for each widget
	static LRESULT CALLBACK GlobalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	void setMinimumSize(int min_width, int min_height);
	void setMaximumSize(int wax_width, int max_height);

protected:
	HWND m_hwnd; 
	Widget* m_parent;
	//map for child widgets of window
	std::map<HWND, Widget*> m_child_widgets;

	bool m_isMaxInstalled;
	bool m_isMinInstalled;

	Rect m_minimumSize;
	Rect m_maximumSize;

	static Widget* getWidgetPtr(HWND hwnd);
	static void addWidget(HWND hwnd, Widget* widget);
	static void removeWidget(HWND hwnd);

private:
	WidgetStyle m_style;
	WNDCLASSEX m_wndclass;
	static std::map<HWND, Widget*> widget_map;

	void create();
	void createWidget();
	void registerClass();
};

