#include "button.h"

using namespace WinUI;

WidgetStyle Button::button_style = {
	"Button",
	{0, 0, 80, 30},
	Style(WS_TABSTOP | WS_VISIBLE | WS_CHILD, NULL),
	NULL
};

Button::Button(string text, Widget* parent) : AbstractButton(button_style, parent)
{
	setText(text);
}

Button::Button(Widget* parent) : AbstractButton(button_style, parent)
{
}

Button::~Button()
{
}
