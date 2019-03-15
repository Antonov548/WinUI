#pragma once

#include "widget.h"

class Window : public Widget
{
public:
	Window(Window* parent = nullptr);
	~Window();

	void setWindowTitle(const char* title);
	void show();
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	static int window_count;

protected:
	virtual void createWidget() override;
};

