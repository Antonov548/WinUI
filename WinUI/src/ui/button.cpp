#include "button.h"

WidgetStyle Button::button_style = {
	"Button",
	{0, 0, 80, 30},
	WS_TABSTOP | WS_VISIBLE | WS_CHILD ,
	NULL,
	NULL
};

Button::Button(const char* text, Widget* parent) : AbstractButton(button_style, parent)
{
	setText(text);
}

Button::Button(Window* parent) : AbstractButton(button_style, parent)
{
	setText("");
}

Button::~Button()
{
}

void Button::setText(const char * text)
{
	m_text = text;
	SetWindowTextA(m_hwnd, m_text.c_str());
}

void Button::setFont(const char * font_family, int font_size)
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
