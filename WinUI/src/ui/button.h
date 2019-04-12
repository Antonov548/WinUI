#pragma once

#include <windows.h>
#include "abstractbutton.h"
#include "window.h"

namespace WinUI
{

	class WINUI_DLL Button : public AbstractButton
	{
	public:
		Button(string text, Widget* parent = nullptr);
		Button(Widget* parent = nullptr);
		~Button();

	private:
		static WidgetStyle button_style;
	};

}