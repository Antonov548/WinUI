#include "checkbox.h"

WidgetStyle CheckBox::check_style = {
	"Button",
	{0, 0, 80, 30},
	Style(WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, NULL),
	NULL
};

CheckBox::CheckBox(Widget* parent) : AbstractButton(check_style, parent)
{
}

CheckBox::~CheckBox()
{
}

bool CheckBox::isChecked() const
{
	return bool(SendMessage(m_hwnd, BM_GETCHECK, NULL, NULL));
}
