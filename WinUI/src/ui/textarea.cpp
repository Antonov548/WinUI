#include "textarea.h"

using namespace WinUI;

WidgetStyle TextArea::text_area_style = {
	"Edit",
	{0, 0, 400, 100},
	Style(WS_CHILD | WS_BORDER | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_LEFT | ES_AUTOHSCROLL | ES_MULTILINE, NULL),
	NULL
};

TextArea::TextArea(Widget* parent) : TextEdit(text_area_style, parent)
{
}

TextArea::~TextArea()
{
}

LRESULT TextArea::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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