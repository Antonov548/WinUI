#pragma once

#include "abstractbutton.h"

namespace WinUI
{

	class WINUI_DLL CheckBox : public AbstractButton
	{
	public:
		CheckBox(Widget* parent = nullptr);
		~CheckBox();
		bool isChecked() const;

	private:
		static WidgetStyle check_style;
	};

}