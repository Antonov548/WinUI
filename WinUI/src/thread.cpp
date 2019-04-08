#include "thread.h"

Thread::Thread()
{
	DWORD id;
	m_threadHandle = CreateThread(NULL, NULL, Thread::threadFunction, this, CREATE_SUSPENDED, &id);
	m_threadId = int(id);
}

Thread::~Thread()
{
}

void Thread::setPriority(Thread::Priority priority)
{
}

void Thread::start()
{
	ResumeThread(m_threadHandle);
	WaitForSingleObject(m_threadHandle, INFINITY);
}

HANDLE Thread::getHandle() const
{
	return m_threadHandle;
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
