#pragma once

#include "widget.h"

namespace WinUI
{

	class WINUI_DLL TextControl
	{
	public:
		TextControl(HWND hwnd);
		~TextControl();

		void setText(string text);
		void setFont(string font_family, int font_size);
		string text() const;
		void setReadOnly(bool readonly);
		void clear();

	private:
		HWND m_container;
	};

}