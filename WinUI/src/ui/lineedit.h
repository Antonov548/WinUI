#pragma once

#include <windows.h>
#include "widget.h"
#include "window.h"

class LineEdit : public Widget
{
public:
	LineEdit(Widget* parent = nullptr);
	~LineEdit();

	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void setText(const char* text);
	void setFont(const char* font_family, int font_size);

private:
	static WidgetStyle line_edit_style;
	std::string m_text;
};

