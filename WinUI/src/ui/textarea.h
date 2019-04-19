#pragma once

#include "textedit.h"

namespace WinUI
{

	class WINUI_DLL TextArea : public TextEdit
	{
	public:
		TextArea(Widget* parent = nullptr);
		~TextArea();
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		static WidgetStyle text_area_style;
	};

}