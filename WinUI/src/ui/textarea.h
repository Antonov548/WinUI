#pragma once

#include "textcontrol.h"

namespace WinUI
{

	class WINUI_DLL TextArea : public TextControl
	{
	public:
		TextArea(Widget* parent = nullptr);
		~TextArea();

	private:
		static WidgetStyle text_area_style;
	};

}