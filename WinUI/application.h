#pragma once

#include <windows.h>

class Application
{
public:
	Application();
	~Application();

	int exec();

private:
	HINSTANCE m_instance;
	MSG m_msg;
	HACCEL m_haccel;
};

