#include "Application.h"

Application::Application() : m_instance((HINSTANCE)GetModuleHandle(NULL)),
							 m_haccel(LoadAccelerators(m_instance, L"WINAPPLICATION"))
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
