#include "localserver.h"

using namespace WinUI;

LocalServer::LocalServer() : m_isReady(true), m_isSending(false), m_pipe(nullptr), m_count(0)
{
	m_heap = GetProcessHeap();
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
			if (bool(m_server->m_connHandler))
			{
				m_server->m_connHandler();
			}

			Thread* thread = new Thread;

			//thread function for handle client messages
			thread->setThreadFunction([this]() {
				HANDLE pipe = m_server->m_pipe;
				ServerClient client = m_server->m_clients[pipe];

				DWORD bytes_read = 0;
				bool message_read;

				m_server->m_isReady = true;

				while (true)
				{
					HeapFree(m_server->m_heap, NULL, client.message);
					client.message = (char*)HeapAlloc(m_server->m_heap, NULL, LocalServer::BufferSize * sizeof(char));

					if (m_server->m_isSending)
					{
						continue;
					}
					message_read = ReadFile(pipe, client.message, LocalServer::BufferSize * sizeof(char), &bytes_read, NULL);
				
					if (GetLastError() == ERROR_BROKEN_PIPE || !message_read)
					{
						if (GetLastError() == ERROR_OPERATION_ABORTED && m_server->m_isSending)
						{
							continue;
						}
						else
						{
							m_server->m_count--;
							if (bool(m_server->m_discHandler) && !m_server->m_isSending)
							{
								m_server->m_discHandler();
							}
							return;
						}
					}

					if (message_read)
					{
						if (bool(m_server->m_msgHandler))
						{
							m_server->m_msgHandler(client.message);
						}
					}
				}
			});

			m_server->m_isReady = false;

			ServerClient client = {thread, nullptr};
			m_server->m_clients.insert(std::make_pair(m_server->m_pipe, client));
			m_server->m_count++;
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
	m_isSending = false;

	for (auto& client : m_clients)
	{
		CancelIoEx(client.first, NULL);
		FlushFileBuffers(client.first);
		DisconnectNamedPipe(client.first);

		HeapFree(m_heap, NULL, client.second.message);

		CloseHandle(client.first);
		delete client.second.thread;
	}
	m_clients.clear();
}

bool LocalServer::report(string message)
{
	if (isRun())
	{
		m_isSending = true;
		int message_size = (message.length() + 1) * sizeof(char);

		for (auto& client : m_clients)
		{
			CancelIoEx(client.first, NULL);
			DWORD bytes_write = 0;
			bool report_send = WriteFile(
				client.first,
				message.c_str(),
				message_size,
				&bytes_write,
				NULL);

			if (!report_send || bytes_write != message_size)
			{
				close();
				return false;
			}
		}
		m_isSending = false;
		return true;
	}
	return false;
}

int LocalServer::connectsCount() const
{
	return m_count;
}

void LocalServer::onNewConnection(std::function<void(void)> func)
{
	m_connHandler = func;
}

void LocalServer::onDisconnect(std::function<void(void)> func)
{
	m_discHandler = func;
}

void LocalServer::onGetMessage(std::function<void(string)> func)
{
	m_msgHandler = func;
}

bool LocalServer::isRun() const
{
	return m_serverThread.isRun() || m_isSending;
}

bool LocalServer::createPipe()
{
	m_pipe = CreateNamedPipe(
		(string("\\\\.\\pipe\\") + m_name).c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		0,
		NULL);

	return (m_pipe != INVALID_HANDLE_VALUE);
}

