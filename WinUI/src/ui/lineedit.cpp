#include "lineedit.h"

using namespace WinUI;

WidgetStyle LineEdit::line_edit_style = {
	"Edit",
	{0, 0, 400, 20},
	Style(WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, NULL),
	NULL
};

LineEdit::LineEdit(Widget* parent) : TextControl(line_edit_style, parent)
{
	ShowScrollBar(m_hwnd, SB_BOTH, FALSE);
}

LineEdit::~LineEdit()
{
}
