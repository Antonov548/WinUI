#pragma once

#include <string.h>
#include <functional>
#include "window.h"
#include "widget.h"

class AbstractButton : public Widget
{
public:
	enum ConnectType {
		Clicked,
		DoubleClicked,
		Pressed
	};

	AbstractButton(WidgetStyle style, Widget* parent);
	~AbstractButton();
	void setText(string text);
	void setFont(string font_family, int font_size);
	void connect(std::function<void(void)> func, AbstractButton::ConnectType type);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	std::string m_text;

private:
	std::function<void(void)> m_clickHandler;
};

