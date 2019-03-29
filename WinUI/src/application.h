#pragma once

#include <Windows.h>

class Application
{
public:
	Application();
	~Application();

	int exec();
	static void quit();
	static HINSTANCE getInstance();

private:
	static HINSTANCE instance;
	MSG m_msg;
	HACCEL m_haccel;
};

