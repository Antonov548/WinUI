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
		break;
	}
	/*case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_MAXIMIZE:
		{
			if(m_is_max_installed)
			break;
		}
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
			break;
		}
		break;
	}*/
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO min_max_info = (LPMINMAXINFO)lParam;
		if (m_isMaxInstalled)
		{
			min_max_info->ptMaxTrackSize.x = m_maximumSize.width;
			min_max_info->ptMaxTrackSize.y = m_maximumSize.height;
		}
		if (m_isMinInstalled)
		{
			min_max_info->ptMinTrackSize.x = m_minimumSize.width;
			min_max_info->ptMinTrackSize.y = m_minimumSize.height;
		}
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