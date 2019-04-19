#pragma once

#include "textcontrol.h"

namespace WinUI
{

	class WINUI_DLL TextArea : public TextControl
	{
	public:
		TextArea(Widget* parent = nullptr);
		~TextArea();
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		static WidgetStyle text_area_style;
	};

}