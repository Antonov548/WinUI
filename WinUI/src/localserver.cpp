#include "localserver.h"

using namespace WinUI;

LocalServer::LocalServer() : m_isServerRun(false)
{
	m_serverThread.setServer(this);
}

LocalServer::~LocalServer()
{
	close();
}

LocalServer::LocalServerThread::LocalServerThread()
{
}

LocalServer::LocalServerThread::~LocalServerThread()
{
}

void LocalServer::LocalServerThread::setServer(LocalServer* server)
{
	m_server = server;
}

void LocalServer::LocalServerThread::run()
{
	while (m_server->m_isServerRun)
	{
		bool connected = ConnectNamedPipe(m_server->m_pipe, NULL);
		if (!connected && GetLastError() == ERROR_PIPE_CONNECTED)
		{
			connected = true;
		}

		if (connected)
		{
			Thread* thread = new Thread;

			//thread function for handle client messages
			thread->setThreadFunction([this]() {
				HANDLE pipe = m_server->m_pipe;
				
				HANDLE heap = GetProcessHeap();
				wchar_t* client_message = (wchar_t*)HeapAlloc(heap, 0, LocalServer::BufferSize * sizeof(wchar_t));

				DWORD bytes_read = 0;
				bool message_read;

				while (m_server->m_isServerRun)
				{
					message_read = ReadFile(pipe, client_message, LocalServer::BufferSize * sizeof(wchar_t), &bytes_read, NULL);
					
					if (!message_read && GetLastError() == ERROR_BROKEN_PIPE)
					{

						return;
					}

					if (message_read)
					{
						MessageBox(NULL, client_message, client_message, MB_OK);
					}
				}
			});
			m_server->m_clientThreads.push_back(thread);
			m_server->m_clientThreads[m_server->m_clientThreads.size()-1]->run();

			if (!m_server->createPipe())
			{
				m_server->close();
				return;
			}
		}
	};
}

bool LocalServer::listen(const string name)
{
	if (m_pipeHandles.size() == 0)
	{
		m_name = name;

		if (!createPipe())
		{
			return false;
		}

		m_isServerRun = true;
		m_serverThread.start();

		return true;
	}
	return false;
}

void LocalServer::close()
{
	m_isServerRun = false;

	for (auto thread : m_clientThreads)
	{
		delete thread;
	}
	m_clientThreads.clear();

	for (auto& pipe : m_pipeHandles)
	{
		DisconnectNamedPipe(pipe);
		CloseHandle(pipe);
	}
	m_pipeHandles.clear();
}

bool LocalServer::isRun() const
{
	return m_isServerRun;
}

bool LocalServer::createPipe()
{
	m_pipe = CreateNamedPipe(
		str_to_wstr("\\\\.\\pipe\\" + m_name).c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_NOWAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		0,
		NULL);

	m_pipeHandles.push_back(m_pipe);
	return (m_pipe != INVALID_HANDLE_VALUE);
}

