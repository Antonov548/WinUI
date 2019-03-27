#pragma once

#include <string.h>
#include "window.h"
#include "widget.h"
#include "../handler.h"

class AbstractButton : public Widget
{
public:
	AbstractButton(WidgetStyle style, Window* parent);
	~AbstractButton();
	void setClickHandler(Handler* event);
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	std::string m_text;
	virtual void click();

private:
	Handler* m_clickHandler;
};

