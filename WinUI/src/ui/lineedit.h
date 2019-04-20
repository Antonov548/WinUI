#pragma once

#include "textcontrol.h"

namespace WinUI
{

	class WINUI_DLL LineEdit : public TextControl
	{
	public:
		LineEdit(Widget* parent = nullptr);
		~LineEdit();

	private:
		static WidgetStyle line_edit_style;
	};

}