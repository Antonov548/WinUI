#pragma once

#include <winui_export.h>
#include <functional>
#include "thread.h"
#include "winstring.h"

namespace WinUI
{

	class WINUILIB_EXPORT LocalSocket
	{
		enum
		{
			BufferSize = 512
		};

	public:
		LocalSocket();
		~LocalSocket();

		bool connectToServer(string name);
		bool send(string message);
		bool isConnected() const;
		void disconnect();
		void onDisconnect(std::function<void(void)> func);
		void onGetReport(std::function<void(string)> func);

	private:
		string m_name;
		HANDLE m_pipe;
		HANDLE m_heap;
		Thread m_socketThread;
		char* m_message;
		bool m_isSending;
		std::function<void(const string)> m_reportHandler;
		std::function<void(void)> m_discHandler;
	};

}

