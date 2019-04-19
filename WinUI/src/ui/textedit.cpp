#include "textedit.h"

using namespace WinUI;

TextEdit::TextEdit(WidgetStyle style, Widget* parent) : Widget(style, parent)
{

}

TextEdit::~TextEdit()
{
}

void TextEdit::setText(string text)
{
	SetWindowTextA(m_hwnd, text.c_str());
}

string TextEdit::text() const
{
	wchar_t text[1024];
	GetWindowText(m_hwnd, text, 1024);
	return to_str_code(wstr_to_str(text), CP_ACP);
}

void TextEdit::setFont(string font_family, int font_size)
{
	const TCHAR* fontName = str_to_wstr(font_family).c_str();
	const long nFontSize = font_size;

	HDC hdc = GetDC(m_hwnd);

	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_NORMAL;

	HFONT s_hFont = CreateFontIndirect(&logFont);
	ReleaseDC(m_hwnd, hdc);
	SendMessage(m_hwnd, WM_SETFONT, (WPARAM)s_hFont, TRUE);
}

void TextEdit::setReadOnly(bool readonly)
{
	SendMessage(m_hwnd, EM_SETREADONLY, readonly, NULL);
}

void TextEdit::clear()
{
	setText("");
}