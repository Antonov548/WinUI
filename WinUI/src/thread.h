#pragma once

#include <winui_export.h>
#include <windows.h>
#include <map>
#include <functional>
#include "winstring.h"
#include "winuinamespace.h"

namespace WinUI
{

	class WINUILIB_EXPORT Thread
	{

		struct WINUILIB_EXPORT CurrentThread
		{
			void sleep(int msecs);
			int getId();
		};

	public:
		Thread();
		~Thread();

		static CurrentThread currend_thread;

		virtual void run();
		void setPriority(ThreadPriority priority);
		void start();
		void exit(int exitcode = 0);
		void wait();
		int getId() const;
		bool isRun() const;
		void setThreadFunction(std::function<void(void)> func);

	private:
		HANDLE m_handle;
		int m_id;
		bool m_isRun;
		std::function<void(void)> m_threadFunc;

		static DWORD WINAPI threadFunction(LPVOID lpParam);
		void clearThread();
	};

}