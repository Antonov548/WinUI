#pragma once

#include <winui_export.h>
#include "widget.h"

namespace WinUI
{

	class WINUILIB_EXPORT TextControl : public Widget
	{
	public:
		TextControl(WidgetStyle style, Widget* parent);
		~TextControl();

		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void setText(string text);
		void setFont(string font_family, int font_size);
		string text() const;
		bool isEmpty() const;
		void setReadOnly(bool readonly);
		void clear();
	};

}