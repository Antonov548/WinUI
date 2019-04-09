#include "label.h"

using namespace WinUI;

WidgetStyle Label::label_style = {
	"Static",
	{0, 0, 80, 30},
	Style(WS_CHILD | WS_VISIBLE | SS_LEFT, NULL),
	NULL
};

Label::Label(Widget* parent) : Widget(label_style, parent)
{
	setText("");
}

Label::Label(string text, Widget* parent) : Widget(label_style, parent)
{
	setText(text);
}

Label::~Label()
{
}

LRESULT Label::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	break;
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

void Label::setText(string text)
{
	m_text = text;
	SetWindowTextA(m_hwnd, m_text.c_str());
}

void Label::setFont(string font_family, int font_size)
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

void Label::setAlignment(WinUI::Alignment align)
{
	DWORD style;
	switch (align)
	{
	case WinUI::AlignmentRight: style = SS_RIGHT; break;
	case WinUI::AlignmentLeft: style = SS_LEFT; break;
	case WinUI::AlignmentCenter: style = SS_CENTER; break;
	default:
	return;
	}
	removeStyle(Style(SS_LEFT | SS_RIGHT | SS_CENTER, NULL));
	addStyle(Style(style, NULL));
}
