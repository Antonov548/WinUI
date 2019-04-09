#include "style.h"

using namespace WinUI;

Style::Style(DWORD style, DWORD ex_style)
	: regular(style), extended(ex_style)
{
}

Style::Style(const Style& style)
	: regular(style.regular), extended(style.extended)
{
}

Style Style::operator+(const Style& style) const
{
	return Style(regular | style.regular,
		extended | style.extended);
}

Style Style::operator-(const Style& style) const
{
	return Style(regular & ~style.regular,
		extended & ~style.extended);
}

Style Style::operator&(const Style & style) const
{
	return Style(regular & style.regular, extended & style.extended);
}

bool Style::hasStyle(const Style & style) const
{
	bool is_style = style.regular != NULL ? (regular & style.regular) : false;
	bool is_ex_style = style.extended !=NULL ? (extended & style.extended) : false;

	return is_style || is_ex_style;
}

bool Style::operator==(const Style& style) const
{
	return regular == style.regular && extended == style.extended;
}

bool Style::operator!=(const Style& style) const
{
	return regular != style.regular || extended != style.extended;
}