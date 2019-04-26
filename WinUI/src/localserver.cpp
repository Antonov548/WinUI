#include "localserver.h"

using namespace WinUI;

LocalServer::LocalServer() : m_isReady(true)
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
	while (true)
	{
		bool connected = false;
		if (m_server->m_isReady)
		{
			if (!m_server->createPipe())
			{
				m_server->close();
				return;
			}

			connected = ConnectNamedPipe(m_server->m_pipe, NULL);
			if (!connected && GetLastError() == ERROR_PIPE_CONNECTED)
			{
				connected = true;
			}
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
				m_server->m_isReady = true;

				while (true)
				{
					message_read = ReadFile(pipe, client_message, LocalServer::BufferSize * sizeof(wchar_t), &bytes_read, NULL);

					if (GetLastError() == ERROR_BROKEN_PIPE)
					{
						return;
					}

					if (message_read)
					{
						MessageBox(NULL, client_message, client_message, MB_OK);
					}
				}
			});

			m_server->m_isReady = false;
			m_server->m_clients[m_server->m_pipe] = thread;
			thread->start();
		}
	};
}

bool LocalServer::listen(const string name)
{
	if (m_clients.size() == 0)
	{
		m_name = name;
		m_serverThread.start();
		return true;
	}
	return false;
}

void LocalServer::close()
{
	m_serverThread.exit();

	for (auto& client : m_clients)
	{
		CloseHandle(client.first);
		if (client.second != nullptr)
		{
			client.second->exit();
			delete client.second;
		}
	}
	m_clients.clear();
}

bool LocalServer::isRun() const
{
	return m_serverThread.isRun();
}

bool LocalServer::createPipe()
{
	m_pipe = CreateNamedPipe(
		str_to_wstr("\\\\.\\pipe\\" + m_name).c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		0,
		NULL);

	m_clients.insert(std::make_pair(m_pipe, nullptr));
	return (m_pipe != INVALID_HANDLE_VALUE);
}

