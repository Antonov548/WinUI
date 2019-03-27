#pragma once

#include <windows.h>
#include "abstractbutton.h"
#include "window.h"

class Button : public AbstractButton
{
public:
	Button(Window* parent, const char* text);
	~Button();

	void setText(const char* text);
	void setFont(const char* font_family, int font_size);

private:
	static WidgetStyle button_style;
};

