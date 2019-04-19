#pragma once

#include "widget.h"

namespace WinUI
{

	class WINUI_DLL TextEdit : public Widget
	{
	public:
		TextEdit(WidgetStyle style, Widget* parent);
		~TextEdit();

		void setText(string text);
		void setFont(string font_family, int font_size);
		string text() const;
		void setReadOnly(bool readonly);
		void clear();
	};

}