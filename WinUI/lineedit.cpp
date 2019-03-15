#include "lineedit.h"

LineEdit::LineEdit(Window* parent) : Widget()
{
	m_parent = parent;
	createWidget();
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

void LineEdit::createWidget()
{
	wchar_t CLASS_NAME[] = L"EDIT";

	m_hwnd = CreateWindow(CLASS_NAME, L"", WS_BORDER | WS_CHILD | WS_VISIBLE, 
		10, 10, 400, 20, 
		m_parent->getHWND(),
		nullptr, nullptr, nullptr);
}
