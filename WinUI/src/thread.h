#pragma once

#include <windows.h>
#include <map>
#include <functional>
#include "winstring.h"
#include "winuinamespace.h"

namespace WinUI
{

	class WINUI_DLL Thread
	{

		struct WINUI_DLL CurrentThread
		{
			void sleep(int msecs);
			int getId();
		};

	public:
		Thread();
		~Thread();

		static CurrentThread currend_thread;

		virtual void run() = 0;
		void setPriority(ThreadPriority priority);
		void start();
		void wait();
		int getId() const;
		void setThreadFunction(std::function<void(void)> func);

	private:
		HANDLE m_handle;
		int m_id;
		std::function<void(void)> m_threadFunc;

		static DWORD WINAPI threadFunction(LPVOID lpParam);
	};

}