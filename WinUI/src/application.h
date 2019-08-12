#pragma once

#include <winui_export.h>
#include <windows.h>

namespace WinUI
{

	class WINUILIB_EXPORT Application
	{
	public:
		Application();
		~Application();

		int exec();
		static void quit();
		static HINSTANCE getInstance();

	private:
		static HINSTANCE instance;
		MSG m_msg;
		HACCEL m_haccel;
	};

}

