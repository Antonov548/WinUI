#pragma once

#include <map>
#include <functional>
#include "winstring.h"
#include "thread.h"

namespace WinUI
{

	class WINUI_DLL LocalServer
	{
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

		struct Client
		{
			Thread* thread;
			char* buffer;
		};

	public:
		LocalServer();
		~LocalServer();

		bool listen(const string name);
		bool isRun() const;
		void close();
		void onNewConnection(std::function<void(void)> func);
		void onGetMessage(std::function<void(string)> func);

	private:
		LocalServerThread m_serverThread;
		HANDLE m_pipe;
		string m_name;
		bool m_isReady;
		std::map<HANDLE, Thread*> m_clients;
		std::function<void(const string)> m_msgHandler;
		std::function<void(void)> m_connHandler;

		bool createPipe();
	};

}

