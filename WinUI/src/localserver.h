#pragma once

#include "winstring.h"
#include "thread.h"

namespace WinUI
{

	class LocalServer
	{
	public:
		LocalServer();
		~LocalServer();

		bool listen(const string name);
		void close();

	private:

		class LocalServerThread : public Thread
		{
			friend class LocalServer;
		public:
			LocalServerThread(LocalServer* server);
			~LocalServerThread();

			virtual void run();
		private:
			LocalServer* m_server;
		};

		LocalServerThread m_serverThread;
		HANDLE m_pipe;
		string m_name;
		bool m_isServerRun;
	};

}

