#pragma once

#include <windows.h>
#include "widget.h"
#include "window.h"
#include "string.h"

class Button : public Widget
{
public:
	Button(Window* parent,const char* text);
	~Button();

	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void setText(const char* text);

protected:
	virtual void createWidget();

private:
	Window* m_parent;
	std::string m_text;
};

