#pragma once

#include <winui_export.h>
#include "textcontrol.h"

namespace WinUI
{

	class WINUILIB_EXPORT LineEdit : public TextControl
	{
	public:
		LineEdit(Widget* parent = nullptr);
		~LineEdit();

	private:
		static WidgetStyle line_edit_style;
	};

}