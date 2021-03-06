#include "winstring.h"

using namespace WinUI;

wstring WinUI::str_to_wstr(const string& str, UINT code_page) {
	if (!str.empty()) {
		int length = MultiByteToWideChar(code_page, 0, str.c_str(), -1, nullptr, 0);
		if (length > 0) {
			std::vector<wchar_t> output(length);
			MultiByteToWideChar(code_page, 0, str.c_str(), -1, &output[0], length);
			return &output[0];
		}
	}

	return wstring();
}

string WinUI::wstr_to_str(const wstring& str, UINT code_page) {
	if (!str.empty()) {
		int length = WideCharToMultiByte(code_page, 0, str.c_str(), -1, nullptr, 0,
			nullptr, nullptr);
		if (length > 0) {
			std::vector<char> output(length);
			WideCharToMultiByte(code_page, 0, str.c_str(), -1, &output[0], length,
				nullptr, nullptr);
			return &output[0];
		}
	}

	return string();
}

string WinUI::to_str_code(const string & str, UINT code_page)
{
	if (!str.empty()) {
		wstring w_str = str_to_wstr(str);
		int length = WideCharToMultiByte(code_page, 0, w_str.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (length > 0) {
			std::vector<char> output(length);
			WideCharToMultiByte(code_page, 0, w_str.c_str(), -1, &output[0], length, nullptr, nullptr);
			return &output[0];
		}
	}

	return string();
}

void WinUI::copy_wstr(const wstring & str, wchar_t * wcopy, int size)
{
	std::wcsncpy(wcopy, str.c_str(), size);
	wcopy[size - 1] = L'\0';
}
