#include "thread.h"

using namespace WinUI;

Thread::CurrentThread Thread::currend_thread;

Thread::Thread()
{
	DWORD id;
	m_handle = CreateThread(NULL, NULL, Thread::threadFunction, LPVOID(this), CREATE_SUSPENDED, &id);
	m_id = int(id);
}

Thread::~Thread()
{
	clearThread();
}

void Thread::run()
{
	m_threadFunc();
}

void Thread::setPriority(ThreadPriority priority)
{
	if (!m_handle)
		return;

	int new_priority;
	switch (priority) {
	case ThreadPriority::Idle: new_priority = THREAD_PRIORITY_IDLE; break;
	case ThreadPriority::Lowest: new_priority = THREAD_PRIORITY_LOWEST; break;
	case ThreadPriority::Low: new_priority = THREAD_PRIORITY_BELOW_NORMAL; break;
	case ThreadPriority::Normal: new_priority = THREAD_PRIORITY_NORMAL; break;
	case ThreadPriority::High: new_priority = THREAD_PRIORITY_ABOVE_NORMAL; break;
	case ThreadPriority::Highest: new_priority = THREAD_PRIORITY_HIGHEST; break;
	case ThreadPriority::TimeCritical: new_priority = THREAD_PRIORITY_TIME_CRITICAL; break;
	}

	SetThreadPriority(m_handle, new_priority);
}

void Thread::start()
{
	ResumeThread(m_handle);
}

void Thread::exit(int exitcode)
{
	TerminateThread(m_handle, exitcode);
	clearThread();
}

void Thread::wait()
{
	WaitForSingleObject(m_handle, INFINITE);
	CloseHandle(m_handle);
	m_handle = NULL;
}

int Thread::getId() const
{
	return m_id;
}

void Thread::setThreadFunction(std::function<void(void)> func)
{
	m_threadFunc = func;
}

DWORD __stdcall Thread::threadFunction(LPVOID lpParam)
{
	auto thread = (Thread*)(lpParam);
	if (thread)
	{
		thread->run();
		return 0;
	}
	return -1;
}

void Thread::clearThread()
{
	if (!m_handle)
	{
		CloseHandle(m_handle);
		m_handle = NULL;
	}
}

void Thread::CurrentThread::sleep(int msecs)
{
	Sleep(msecs);
}

int Thread::CurrentThread::getId()
{
	return int(GetCurrentThreadId());
}