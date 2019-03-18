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
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	static int window_count;

protected:
	virtual void createWidget(const char* class_name) override;
	virtual void registerClass(const char* class_name) override;
};

