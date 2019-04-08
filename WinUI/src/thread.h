#pragma once

#include <windows.h>
#include <map>
#include <string>
#include "winstring.h"

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
	void wait(int milliseconds = -1);
	HANDLE getHandle() const;

private:
	HANDLE m_handle;
	int m_id;

	static DWORD WINAPI threadFunction(LPVOID lpParam);
};