#include "style.h"

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

bool Style::operator==(const Style& style) const
{
	return regular == style.regular && extended == style.extended;
}

bool Style::operator!=(const Style& style) const
{
	return regular != style.regular || extended != style.extended;
}