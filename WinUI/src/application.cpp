#include "Application.h"

using namespace WinUI;

HINSTANCE Application::instance = (HINSTANCE)GetModuleHandle(NULL);

Application::Application() : m_haccel(LoadAccelerators(instance, "WINAPPLICATION"))
{
}

Application::~Application()
{
}

int Application::exec()
{
	while (GetMessage(&m_msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(m_msg.hwnd, m_haccel, &m_msg))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
	}
	return (int)m_msg.wParam;
}

void Application::quit()
{
	PostQuitMessage(0);
}

HINSTANCE Application::getInstance()
{
	return instance;
}
