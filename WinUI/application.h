#pragma once

#include <windows.h>

class Application
{
public:
	Application();
	~Application();

	int exec();
	static HINSTANCE getInstance();

private:
	static HINSTANCE m_instance;
	MSG m_msg;
	HACCEL m_haccel;
};

