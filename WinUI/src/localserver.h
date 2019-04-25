#pragma once

#include <vector>
#include <map>
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
		bool isRun() const;
		void close();

	private:
		enum
		{
			BufferSize = 512
		};

		class LocalServerThread : public Thread
		{
			friend class LocalServer;
		public:
			LocalServerThread();
			~LocalServerThread();

			void run() override;
			void setServer(LocalServer* server);

		private:
			LocalServer* m_server;
		};

		LocalServerThread m_serverThread;
		HANDLE m_pipe;
		string m_name;
		bool m_isServerRun;
		std::map<HANDLE, Thread*> m_clients;

		bool createPipe();
	};

}

