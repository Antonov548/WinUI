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
	if (m_handle != NULL)
	{
		CloseHandle(m_handle);
		m_handle = NULL;
	}
}

void Thread::setPriority(Thread::Priority priority)
{
	if (!m_handle)
		return;

	int new_priority;
	switch (priority) {
	case Thread::Priority::Idle: new_priority = THREAD_PRIORITY_IDLE; break;
	case Thread::Priority::Lowest: new_priority = THREAD_PRIORITY_LOWEST; break;
	case Thread::Priority::Low: new_priority = THREAD_PRIORITY_BELOW_NORMAL; break;
	case Thread::Priority::Normal: new_priority = THREAD_PRIORITY_NORMAL; break;
	case Thread::Priority::High: new_priority = THREAD_PRIORITY_ABOVE_NORMAL; break;
	case Thread::Priority::Highest: new_priority = THREAD_PRIORITY_HIGHEST; break;
	case Thread::Priority::TimeCritical: new_priority = THREAD_PRIORITY_TIME_CRITICAL; break;
	}

	SetThreadPriority(m_handle, new_priority);
}

void Thread::start()
{
	ResumeThread(m_handle);
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

void Thread::CurrentThread::sleep(int msecs)
{
	Sleep(msecs);
}

int Thread::CurrentThread::getId()
{
	return int(GetCurrentThreadId());
}