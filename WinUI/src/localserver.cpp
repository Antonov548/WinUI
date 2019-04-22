#include "localserver.h"

using namespace WinUI;

LocalServer::LocalServer() : m_isServerRun(false)
{
	m_serverThread.setServer(this);
}

LocalServer::~LocalServer()
{
	for (auto thread : m_clientThreads)
	{
		thread->exit();
	}
	m_serverThread.exit();
	CloseHandle(m_pipe);
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
			MessageBox(NULL, str_to_wstr(std::to_string(connected)).c_str(), L"Work", MB_OK);
			if (!m_server->createPipe())
			{
				m_server->close();
				return;
			}

			/*Thread* thread = new Thread;
			thread->setThreadFunction([this]() {
				MessageBox(NULL, L"Work", L"Work", MB_OK);
			});
			m_server->m_clientThreads.push_back(thread);*/
			//m_server->m_clientThreads[m_server->m_clientThreads.size()]->run();
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
}

bool LocalServer::createPipe()
{
	m_pipe = CreateNamedPipe(
		str_to_wstr("\\\\.\\pipe\\" + m_name).c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_NOWAIT
		, PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		0,
		NULL);

	m_pipeHandles.push_back(m_pipe);
	return (m_pipe != INVALID_HANDLE_VALUE);
}

