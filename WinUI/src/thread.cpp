#include "thread.h"

Thread::Thread()
{
	DWORD id;
	m_handle = CreateThread(NULL, NULL, Thread::threadFunction, this, NULL, &id);
	m_id = int(id);
}

Thread::~Thread()
{
}

void Thread::setPriority(Thread::Priority priority)
{
}

void Thread::start()
{
	ResumeThread(m_handle);
}

void Thread::wait(const int milliseconds)
{
	if (milliseconds == -1)
	{
		WaitForSingleObject(m_handle, INFINITE);
	}
	else
	{
		WaitForSingleObject(m_handle, milliseconds);
	}
}

HANDLE Thread::getHandle() const
{
	return m_handle;
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
