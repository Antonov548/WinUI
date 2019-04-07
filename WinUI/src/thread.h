#pragma once

#include <windows.h>

class Thread
{
public:
	Thread();
	~Thread();

	enum Priority
	{

	};

	virtual void run() = 0;
	void setPriority(Thread::Priority priority);
	void start();

private:
	HANDLE m_threadHandle;

	DWORD WINAPI threadFunction(LPVOID lpParam);
};

