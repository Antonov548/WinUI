#include "textcontrol.h"

using namespace WinUI;

TextControl::TextControl(HWND hwnd) : m_container(hwnd)
{
}

TextControl::~TextControl()
{
}

void TextControl::setText(string text)
{
	SetWindowTextA(m_container, text.c_str());
}

string TextControl::text() const
{
	wchar_t text[1024];
	GetWindowText(m_container, text, 1024);
	return to_str_code(wstr_to_str(text), CP_ACP);
}

void TextControl::setFont(string font_family, int font_size)
{
	const long nFontSize = font_size;
	HDC hdc = GetDC(m_container);

	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_NORMAL;

	copy_wstr(str_to_wstr(font_family), logFont.lfFaceName, LF_FACESIZE);

	HFONT s_hFont = CreateFontIndirect(&logFont);
	ReleaseDC(m_container, hdc);
	SendMessage(m_container, WM_SETFONT, (WPARAM)s_hFont, TRUE);
}

void TextControl::setReadOnly(bool readonly)
{
	SendMessage(m_container, EM_SETREADONLY, readonly, NULL);
}

void TextControl::clear()
{
	setText("");
}