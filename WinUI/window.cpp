#include "window.h"

int Window::window_count = 0;

Window::Window(Window* parent) : Widget(parent)
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

//void Window::createWidget()
//{
//	wchar_t CLASS_NAME[] = L"Window";
//
//	WNDCLASSEX windowClass;
//	windowClass.cbSize = sizeof(WNDCLASSEX);
//	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	windowClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
//	windowClass.lpfnWndProc = GlobalWndProc;
//	windowClass.lpszClassName = CLASS_NAME;
//	windowClass.style = CS_HREDRAW | CS_VREDRAW;
//	windowClass.hIcon = NULL;
//	windowClass.hIconSm = NULL;
//	windowClass.lpszMenuName = NULL;
//	windowClass.cbClsExtra = 0;
//	windowClass.cbWndExtra = 0;
//
//	RegisterClassEx(&windowClass);
//
//	m_hwnd = CreateWindow(CLASS_NAME, L"", WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_parent ? m_parent->getHWND() : nullptr, nullptr, Application::getInstance(), nullptr);
//
//	UnregisterClass(CLASS_NAME, (HINSTANCE)GetModuleHandle(NULL));
//}
