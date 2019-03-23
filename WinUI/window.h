#pragma once

#include "application.h"
#include "widget.h"

class Window : public Widget
{
public:
	Window(Window* parent = nullptr);
	~Window();

	void setWindowTitle(const char* title);
	void show();
	void setMinimumSize(int min_width, int min_height);
	void setMaximumSize(int wax_width, int max_height);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	static int window_count;
	static WidgetStyle window_style;

	//rects for min/max size. x and y allways 0
	Rect m_minimumSize;
	Rect m_maximumSize;
};

