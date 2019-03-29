#include "lineedit.h"

WidgetStyle LineEdit::line_edit_style = {
	"Edit",
	{0, 0, 400, 20},
	WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
	NULL,
	NULL
};

LineEdit::LineEdit(Widget* parent) : Widget(line_edit_style, parent)
{
	ShowScrollBar(m_hwnd, SB_BOTH, FALSE);
}

LineEdit::~LineEdit()
{
}

LRESULT LineEdit::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void LineEdit::setText(string text)
{
	m_text = text;
	SetWindowTextA(m_hwnd, m_text.c_str());
}

std::string LineEdit::text() const
{
	wchar_t text[1024];
	GetWindowText(m_hwnd, text, 1024);
	return wstr_to_str(text);
}

void LineEdit::setFont(string font_family, int font_size)
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