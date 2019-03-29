#pragma once

#include <string>
#include <vector>
#include <windows.h>

std::wstring str_to_wstr(const std::string& str, UINT code_page = CP_UTF8);
std::string wstr_to_str(const std::wstring& str, UINT code_page = CP_UTF8);