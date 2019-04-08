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
	HANDLE getHandle() const;

private:
	HANDLE m_threadHandle;
	int m_threadId;

	static DWORD WINAPI threadFunction(LPVOID lpParam);
	void addThread(int id, Thread* thread);
};