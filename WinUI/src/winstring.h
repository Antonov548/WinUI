#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "winuidll.h"

namespace WinUI
{

	using std::string;
	using std::wstring;

	wstring str_to_wstr(const string& str, UINT code_page = CP_UTF8);
	string wstr_to_str(const wstring& str, UINT code_page = CP_UTF8);
	string to_str_code(const string& str, UINT code_page);

}