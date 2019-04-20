#pragma once

#include "widget.h"

namespace WinUI
{

	class WINUI_DLL TextControl : public Widget
	{
	public:
		TextControl(WidgetStyle style, Widget* parent);
		~TextControl();

		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void setText(string text);
		void setFont(string font_family, int font_size);
		string text() const;
		void setReadOnly(bool readonly);
		void clear();
	};

}