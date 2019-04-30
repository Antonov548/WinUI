#include "textcontrol.h"

using namespace WinUI;

TextControl::TextControl(WidgetStyle style, Widget* parent) : Widget(style, parent)
{

}

TextControl::~TextControl()
{
}

LRESULT TextControl::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		removeWidget(hwnd);
		DestroyWindow(hwnd);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void TextControl::setText(string text)
{
	SetWindowTextA(m_hwnd, text.c_str());
}

string TextControl::text() const
{
	wchar_t text[1024];
	GetWindowText(m_hwnd, text, 1024);
	return to_str_code(wstr_to_str(text), CP_ACP);
}

bool TextControl::isEmpty() const
{
	wchar_t text[1024];
	GetWindowText(m_hwnd, text, 1024);
	string std_text = to_str_code(wstr_to_str(text), CP_ACP);
	return std_text.empty();
}

void TextControl::setFont(string font_family, int font_size)
{
	const long nFontSize = font_size;
	HDC hdc = GetDC(m_hwnd);

	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_NORMAL;

	copy_wstr(str_to_wstr(font_family), logFont.lfFaceName, LF_FACESIZE);

	HFONT s_hFont = CreateFontIndirect(&logFont);
	ReleaseDC(m_hwnd, hdc);
	SendMessage(m_hwnd, WM_SETFONT, (WPARAM)s_hFont, TRUE);
}

void TextControl::setReadOnly(bool readonly)
{
	SendMessage(m_hwnd, EM_SETREADONLY, readonly, NULL);
}

void TextControl::clear()
{
	setText("");
}