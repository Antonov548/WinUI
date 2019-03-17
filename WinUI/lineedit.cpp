#include "lineedit.h"

LineEdit::LineEdit(Window* parent) : Widget("Edit", parent)
{
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
		Widget::widget_map.removeWidget(hwnd);
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void LineEdit::setText(const char * text)
{
	m_text = text;
	SetWindowTextA(m_hwnd, m_text.c_str());
}

void LineEdit::setFont(const char* font_family, int font_size)
{
	const TCHAR* fontName = str_to_wstr(font_family).c_str();
	const long nFontSize = font_size;

	HDC hdc = GetDC(m_hwnd);

	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_EXTRABOLD;

	HFONT s_hFont = CreateFontIndirect(&logFont);

	ReleaseDC(m_hwnd, hdc);

	SendMessage(m_hwnd, WM_SETFONT, (WPARAM)s_hFont, TRUE);
}

//void LineEdit::createWidget()
//{
//	wchar_t CLASS_NAME[] = L"EDIT";
//
//	m_hwnd = CreateWindow(CLASS_NAME, L"", WS_BORDER | WS_CHILD | WS_VISIBLE, 
//		10, 10, 400, 20, 
//		m_parent->getHWND(),
//		nullptr, nullptr, nullptr);
//}
