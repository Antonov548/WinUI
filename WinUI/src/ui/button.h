#pragma once

#include <windows.h>
#include "abstractbutton.h"
#include "window.h"

class Button : public AbstractButton
{
public:
	Button(string text, Widget* parent = nullptr);
	Button(Window* parent = nullptr);
	~Button();

private:
	static WidgetStyle button_style;
};

