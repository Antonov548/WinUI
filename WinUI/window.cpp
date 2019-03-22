#include "window.h"

WidgetStyle Window::window_style = {
	"Window",
	{CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT},
	WS_OVERLAPPEDWINDOW,
	WS_EX_OVERLAPPEDWINDOW,
	CS_HREDRAW | CS_VREDRAW
};

int Window::window_count = 0;

Window::Window(Window* parent) : Widget(window_style, parent)
{
	Window::window_count++;
}

Window::~Window()
{
}

void Window::setWindowTitle(const char * title)
{
	SetWindowTextA(m_hwnd, title);
}

void Window::show()
{
	ShowWindow(m_hwnd, SW_RESTORE);
}

LRESULT Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		Window::window_count--;
		if (Window::window_count == 0)
		{
			PostQuitMessage(0);
		}
		else
		{
			DestroyWindow(hwnd);
		}
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}