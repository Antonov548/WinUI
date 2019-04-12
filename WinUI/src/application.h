#pragma once

#include <windows.h>
#include "winuidll.h"

namespace WinUI
{

	class WINUI_DLL Application
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

