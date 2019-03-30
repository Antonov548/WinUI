#pragma once

#include "abstractbutton.h"

class CheckBox : public AbstractButton
{
public:
	CheckBox(Widget* parent = nullptr);
	~CheckBox();

	bool isChecked() const;

private:
	static WidgetStyle check_style;
};

