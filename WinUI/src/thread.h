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
	public:
		Thread();
		~Thread();

		enum Priority
		{

		};

		struct CurrentThread
		{
			void sleep(int msecs);
			int getId();
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