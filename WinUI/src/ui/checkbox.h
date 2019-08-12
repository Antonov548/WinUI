#pragma once

#include <winui_export.h>
#include "abstractbutton.h"

namespace WinUI
{

	class WINUILIB_EXPORT CheckBox : public AbstractButton
	{
	public:
		CheckBox(Widget* parent = nullptr);
		~CheckBox();
		bool isChecked() const;

	private:
		static WidgetStyle check_style;
	};

}