#include "string.h"

std::wstring str_to_wstr(const std::string& str, UINT code_page) {
	if (!str.empty()) {
		int length = MultiByteToWideChar(code_page, 0, str.c_str(), -1, nullptr, 0);
		if (length > 0) {
			std::vector<wchar_t> output(length);
			MultiByteToWideChar(code_page, 0, str.c_str(), -1, &output[0], length);
			return &output[0];
		}
	}

	return std::wstring();
}

std::string wstr_to_str(const std::wstring& str, UINT code_page) {
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

	return std::string();
}