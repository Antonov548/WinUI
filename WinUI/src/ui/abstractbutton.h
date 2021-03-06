#pragma once

#include <winui_export.h>
#include <string.h>
#include <functional>
#include "window.h"
#include "widget.h"

namespace WinUI
{

	class WINUILIB_EXPORT AbstractButton : public Widget
	{
	public:
		AbstractButton(WidgetStyle style, Widget* parent);
		~AbstractButton();
		void setText(string text);
		void setFont(string font_family, int font_size);
		void connect(std::function<void(void)> func);
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		std::function<void(void)> m_clickHandler;
	};

}