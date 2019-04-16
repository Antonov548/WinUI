#pragma once

#include "widget.h"
#include "../winuinamespace.h"

namespace WinUI
{

	class WINUI_DLL Label : public Widget
	{
	public:
		Label(string text, Widget* parent = nullptr);
		Label(Widget* parent = nullptr);
		~Label();
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void setText(string text);
		void setFont(string font_family, int font_size);
		void setAlignment(Alignment align);

	private:
		static WidgetStyle label_style;
		string m_text;
	};

}