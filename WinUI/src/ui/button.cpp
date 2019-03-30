#include "button.h"

WidgetStyle Button::button_style = {
	"Button",
	{0, 0, 80, 30},
	WS_TABSTOP | WS_VISIBLE | WS_CHILD,
	NULL,
	NULL
};

Button::Button(string text, Widget* parent) : AbstractButton(button_style, parent)
{
	setText(text);
}

Button::Button(Window* parent) : AbstractButton(button_style, parent)
{
	setText("");
}

Button::~Button()
{
}
