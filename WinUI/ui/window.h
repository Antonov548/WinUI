#pragma once

#include <map>
#include "widget.h"

class Window : public Widget
{
public:
	Window(Window* parent = nullptr);
	~Window();

	void setWindowTitle(const char* title);
	void show();
	void addChild(Widget* widget);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	static int window_count;
	static WidgetStyle window_style;

	std::map<int, Widget*> m_child_widgets;
};

