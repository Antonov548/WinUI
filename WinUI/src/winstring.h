#pragma once

#include <string>
#include <vector>
#include <windows.h>

using std::string;
using std::wstring;

wstring str_to_wstr(const string& str, UINT code_page = CP_UTF8);
string wstr_to_str(const wstring& str, UINT code_page = CP_UTF8);