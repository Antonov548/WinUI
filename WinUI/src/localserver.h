#pragma once

#include <map>
#include <functional>
#include <strsafe.h>
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

		struct ServerClient
		{
			Thread* thread;
			char* message;
		};

	public:
		LocalServer();
		~LocalServer();

		bool listen(const string name);
		bool isRun() const;
		void close();
		void report(string message);
		void onNewConnection(std::function<void(void)> func);
		void onDisconnect(std::function<void(void)> func);
		void onGetMessage(std::function<void(string)> func);

	private:
		LocalServerThread m_serverThread;
		HANDLE m_pipe;
		HANDLE m_heap;
		string m_name;
		bool m_isReady;
		std::map<HANDLE, ServerClient> m_clients;
		std::function<void(const string)> m_msgHandler;
		std::function<void(void)> m_connHandler;
		std::function<void(void)> m_discHandler;

		bool createPipe();
	};

}

