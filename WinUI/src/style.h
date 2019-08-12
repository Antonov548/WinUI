#pragma once

#include <windows.h>

namespace WinUI
{

	struct Style
	{
		Style(DWORD style, DWORD ex_style);
		Style(const Style& style);

		DWORD regular;
		DWORD extended;

		Style operator+(const Style& style) const;
		Style operator-(const Style& style) const;
		Style operator&(const Style& style) const;

		bool hasStyle(const Style& style) const;

		bool operator==(const Style& style) const;
		bool operator!=(const Style& style) const;
	};

}