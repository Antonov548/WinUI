#include "localserver.h"

using namespace WinUI;

LocalServer::LocalServer() : m_isServerRun(false), m_serverThread(this)
{
}

LocalServer::~LocalServer()
{
}

LocalServer::LocalServerThread::LocalServerThread(LocalServer* server) : m_server(server)
{
}

LocalServer::LocalServerThread::~LocalServerThread()
{
}

void LocalServer::LocalServerThread::run()
{
	while (m_server->m_isServerRun)
	{
		bool connected = ConnectNamedPipe(m_server->m_pipe, NULL);
		if (connected)
		{
		}
	}
}

bool LocalServer::listen(const string name)
{
	m_name = name;
	m_pipe = CreateNamedPipe(
		str_to_wstr("\\\\.\\pipe\\" + name).c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		0, 
		NULL);

	if (m_pipe || m_pipe == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	m_isServerRun = true;
	m_serverThread.start();

	return true;
}

void LocalServer::close()
{
	m_isServerRun = false;
}

