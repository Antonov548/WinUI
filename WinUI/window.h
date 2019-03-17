#pragma once

#include "application.h"
#include "widget.h"
#include "registeredwidget.h"

class Window : public RegisteredWidget, public Widget
{
public:
	Window(Window* parent = nullptr);
	~Window();

	void setWindowTitle(const char* title);
	void show();
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	static int window_count;
};

