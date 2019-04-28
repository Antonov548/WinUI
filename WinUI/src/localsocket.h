#pragma once

#include "thread.h"
#include "winstring.h"

namespace WinUI
{

	class WINUI_DLL LocalSocket
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

	private:
		string m_name;
		HANDLE m_pipe;
		HANDLE m_heap;
		Thread m_socketThread;
	};

}

