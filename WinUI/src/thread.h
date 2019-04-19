#pragma once

#include <windows.h>
#include <map>
#include <string>
#include "winstring.h"
#include "winuidll.h"

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

		enum Priority
		{
			Idle,
			Lowest,
			Low,
			Normal,
			High,
			Highest,
			TimeCritical
		};

		static CurrentThread currend_thread;

		virtual void run() = 0;
		void setPriority(Thread::Priority priority);
		void start();
		void wait();
		int getId() const;

	private:
		HANDLE m_handle;
		int m_id;

		static DWORD WINAPI threadFunction(LPVOID lpParam);
	};

}