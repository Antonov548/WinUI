#pragma once

#include <windows.h>
#include <string.h>
#include "string.h"
#include "widget.h"
#include "window.h"

class LineEdit : public Widget
{
public:
	LineEdit(Window* parent);
	~LineEdit();

	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void setText(const char* text);
	void setFont(const char* font_family, int font_size);

private:
	std::string m_text;

protected:
	virtual void createWidget() override;
};

