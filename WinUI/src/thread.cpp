#include "thread.h"

CurrentThread Thread::currend_thread;

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

void CurrentThread::sleep(int msecs)
{
	Sleep(msecs);
}

int CurrentThread::getId()
{
	return int(GetCurrentThreadId());
}

//void Thread::addThread(int id, Thread * thread)
//{
//	Thread::thread_map.insert(std::make_pair(id, thread));
//}
//
//Thread* Thread::getThreadPtrById(int id)
//{
//	auto thread = Thread::thread_map.find(id);
//	return thread != Thread::thread_map.end() ? thread->second : nullptr;
//}
