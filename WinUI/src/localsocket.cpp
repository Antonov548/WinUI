#include "localsocket.h"

using namespace WinUI;

LocalSocket::LocalSocket()
{
	m_heap = GetProcessHeap();

	m_socketThread.setThreadFunction([this]() {
		while (true)
		{

		}
	});
}

LocalSocket::~LocalSocket()
{
	m_socketThread.exit();
}

bool LocalSocket::send(string message)
{
	if (isConnected())
	{
		DWORD bytes_write = 0;
		bool message_send = WriteFile(
			m_pipe,
			message.c_str(),
			(message.length() + 1) * sizeof(char),
			&bytes_write,
			NULL);

		if (message_send && bytes_write == message.size())
		{
			return true;
		}
	}
	return false;
}

bool LocalSocket::isConnected() const
{
	return m_socketThread.isRun();
}

bool LocalSocket::connectToServer(string name)
{
	if (!m_socketThread.isRun())
	{
		m_name = name;
		m_pipe = CreateFile(
			str_to_wstr("\\\\.\\pipe\\" + m_name).c_str(),
			GENERIC_READ |
			GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (m_pipe != INVALID_HANDLE_VALUE)
		{
			DWORD mode = PIPE_READMODE_MESSAGE;
			bool pipe_state = SetNamedPipeHandleState(
				m_pipe,
				&mode,
				NULL,
				NULL);

			if (pipe_state)
			{
				m_socketThread.start();
				return true;
			}
		}
	}
	return false;
}

void LocalSocket::disconnect()
{

}
