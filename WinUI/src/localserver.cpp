#include "localserver.h"

using namespace WinUI;

LocalServer::LocalServer() : m_isServerRun(false)
{
	m_serverThread.setThreadFunction([this]() {  
	while (m_isServerRun)
	{
		bool connected = ConnectNamedPipe(m_pipe, NULL);
	}; });
}

LocalServer::~LocalServer()
{
	m_serverThread.exit();
	CloseHandle(m_pipe);
}

bool LocalServer::listen(const string name)
{
	m_name = name;
	m_pipe = CreateNamedPipe(
		str_to_wstr("\\\\.\\pipe\\" + name).c_str(),
		PIPE_ACCESS_DUPLEX, 
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT
		,PIPE_UNLIMITED_INSTANCES, 
		0,
		0, 
		0, 
		NULL);

	if (m_pipe == INVALID_HANDLE_VALUE)
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

