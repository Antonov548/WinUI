#pragma once

#include "textedit.h"

namespace WinUI
{

	class WINUI_DLL LineEdit : public TextEdit
	{
	public:
		LineEdit(Widget* parent = nullptr);
		~LineEdit();
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		static WidgetStyle line_edit_style;
	};

}