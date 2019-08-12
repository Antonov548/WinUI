#pragma once

#include <winui_export.h>
#include "textcontrol.h"

namespace WinUI
{

	class WINUILIB_EXPORT TextArea : public TextControl
	{
	public:
		TextArea(Widget* parent = nullptr);
		~TextArea();

	private:
		static WidgetStyle text_area_style;
	};

}