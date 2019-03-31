#include "window.h"

WidgetStyle Window::window_style = {
	"Window",
	{CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT},
	WS_OVERLAPPEDWINDOW,
	WS_EX_OVERLAPPEDWINDOW,
	CS_HREDRAW | CS_VREDRAW
};

int Window::window_count = 0;

Window::Window(Widget* parent) : Widget(window_style, parent)
{
}

Window::~Window()
{
}

void Window::setWindowTitle(string title)
{
	SetWindowTextA(m_hwnd, title.c_str());
}

void Window::show()
{
	ShowWindow(m_hwnd, SW_SHOW);
}

void Window::hide()
{
	ShowWindow(m_hwnd, SW_HIDE);
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
			if ((GetWindowLongPtr(m_hwnd, GWL_STYLE) & WS_MAXIMIZEBOX))
				SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX);
			min_max_info->ptMaxTrackSize.x = m_maximumSize.width;
			min_max_info->ptMaxTrackSize.y = m_maximumSize.height;
		}
		if (m_isMinInstalled)
		{
			min_max_info->ptMinTrackSize.x = m_minimumSize.width;
			min_max_info->ptMinTrackSize.y = m_minimumSize.height;
		}
	}
	break;
	case WM_COMMAND:
	{
		auto child = getWidgetPtr(HWND(lParam));
		if (child)
		{
			child->WndProc(hwnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SHOWWINDOW:
	{
		if (bool(wParam))
		{
			Window::window_count++;
		}
		else
		{
			Window::window_count--;
		}
	}
		break;
	case WM_CLOSE:
	{
		hide();
		if (Window::window_count == 0)
		{
			PostQuitMessage(0);
		}
		else
		{
			for (auto& child : m_child_widgets)
			{
				if(child.second->getClassName() == Window::window_style.class_name)
					PostMessage(child.first, WM_CLOSE, NULL, NULL);
			}
		}
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