#pragma once

#include <string>
#include <vector>
#include <windows.h>

namespace WinUI
{

	using std::string;
	using std::wstring;

	wstring str_to_wstr(const string& str, UINT code_page = CP_UTF8);
	string wstr_to_str(const wstring& str, UINT code_page = CP_UTF8);
	string to_str_code(const string& str, UINT code_page);
	void copy_wstr(const wstring& str, wchar_t* wcopy, int size);

}