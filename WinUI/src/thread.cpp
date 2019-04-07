#include "thread.h"

Thread::Thread()
{
	//m_threadHandle = CreateThread();
}

Thread::~Thread()
{
}

void Thread::setPriority(Thread::Priority priority)
{
}

void Thread::start()
{
}

DWORD __stdcall Thread::threadFunction(LPVOID lpParam)
{
	run();
}
