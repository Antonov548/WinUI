#pragma once

#include <map>
#include "widget.h"

class Window : public Widget
{
public:
	Window(Widget* parent = nullptr);
	~Window();

	void setWindowTitle(const char* title);
	void setWindowTitle(std::string title);
	void show();
	void close();
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	static int window_count;
	static WidgetStyle window_style;
};

