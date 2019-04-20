#include "textarea.h"

using namespace WinUI;

WidgetStyle TextArea::text_area_style = {
	"Edit",
	{0, 0, 400, 100},
	Style(WS_CHILD | WS_BORDER | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_LEFT | ES_AUTOHSCROLL | ES_MULTILINE, NULL),
	NULL
};

TextArea::TextArea(Widget* parent) : TextControl(text_area_style, parent)
{
}

TextArea::~TextArea()
{
}