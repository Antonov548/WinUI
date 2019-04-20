#include "lineedit.h"

using namespace WinUI;

WidgetStyle LineEdit::line_edit_style = {
	"Edit",
	{0, 0, 400, 20},
	Style(WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, NULL),
	NULL
};

LineEdit::LineEdit(Widget* parent) : Widget(line_edit_style, parent), TextControl(m_hwnd)
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
	{
		removeWidget(hwnd);
		DestroyWindow(hwnd);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
