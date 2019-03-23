#include "window.h"

WidgetStyle Window::window_style = {
	"Window",
	{CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT},
	WS_OVERLAPPEDWINDOW,
	WS_EX_OVERLAPPEDWINDOW,
	CS_HREDRAW | CS_VREDRAW
};

int Window::window_count = 0;

Window::Window(Window* parent) : Widget(window_style, parent), 
								 m_minimumSize({0, 0, int(GetSystemMetrics(SM_CXMINTRACK)), int(GetSystemMetrics(SM_CYMINTRACK))}),
								 m_maximumSize({0, 0, int(GetSystemMetrics(SM_CXMAXTRACK)), int(GetSystemMetrics(SM_CYMAXTRACK))})
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

// must check current size of widegt and resize
void Window::setMinimumSize(int min_width, int min_height)
{
	if (min_width > m_maximumSize.width || min_height > m_maximumSize.height)
		return;

	if (width() < min_width)
		setWidth(min_width);
	if (height() < min_height)
		setHeight(min_height);
	m_minimumSize.width = min_width;
	m_minimumSize.height = min_height;
}

void Window::setMaximumSize(int max_width, int max_height)
{
	if (max_width < m_minimumSize.width || max_height < m_minimumSize.height)
		return;

	if (width() > max_width)
		setWidth(max_width);
	if (height() > max_height)
		setHeight(max_height);
	m_maximumSize.width = max_width;
	m_maximumSize.height = max_height;
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
		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO min_max_info = (LPMINMAXINFO)lParam;
		min_max_info->ptMinTrackSize.x = m_minimumSize.width;
		min_max_info->ptMinTrackSize.y = m_minimumSize.height;
		min_max_info->ptMaxTrackSize.x = m_maximumSize.width;
		min_max_info->ptMaxTrackSize.y = m_maximumSize.height;

		break;
	}
	case WM_DESTROY:
	{
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
	}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}