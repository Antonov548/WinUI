#pragma once

#include "winstring.h"
#include "thread.h"

namespace WinUI
{

	class WINUI_DLL LocalServer
	{
	public:
		LocalServer();
		~LocalServer();

		bool listen(const string name);
		void close();

	private:
		Thread m_serverThread;
		HANDLE m_pipe;
		string m_name;
		bool m_isServerRun;
	};

}

