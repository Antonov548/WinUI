#pragma once

#include <string.h>
#include <functional>
#include "window.h"
#include "widget.h"

namespace WinUI
{

	class WINUI_DLL AbstractButton : public Widget
	{
	public:
		AbstractButton(WidgetStyle style, Widget* parent);
		~AbstractButton();
		void setText(string text);
		void setFont(string font_family, int font_size);
		void connect(std::function<void(void)> func);
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	protected:
		std::string m_text;

	private:
		std::function<void(void)> m_clickHandler;
	};

}