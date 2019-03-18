#include "window.h"

int Window::window_count = 0;

Window::Window(Window* parent) : Widget("WinUI.Window", parent)
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

void Window::registerClass(const char * class_name)
{
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
		wndclass.lpfnWndProc = GlobalWndProc;
		wndclass.lpszClassName = str_to_wstr(class_name).c_str();
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.hIcon = NULL;
		wndclass.hIconSm = NULL;
		wndclass.lpszMenuName = NULL;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
	
		RegisterClassEx(&wndclass);
}

void Window::createWidget(const char* class_name)
{
	m_hwnd = CreateWindowEx(
		WS_OVERLAPPEDWINDOW,
		str_to_wstr(class_name).c_str(),
		L"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_parent ? m_parent->getHWND() : nullptr,
		nullptr,
		Application::getInstance(),
		nullptr
	); 
}
