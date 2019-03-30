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
	void setText(string text);
	void setFont(string font_family, int font_size);
	string text() const;

private:
	static WidgetStyle line_edit_style;
	std::string m_text;
};

