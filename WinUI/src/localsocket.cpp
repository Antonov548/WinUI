#include "localsocket.h"

using namespace WinUI;

LocalSocket::LocalSocket() : m_message(nullptr), m_isSending(false), m_pipe(nullptr)
{
	m_heap = GetProcessHeap();

	m_socketThread.setThreadFunction([this]() {
		DWORD bytes_read = 0;
		bool get_report;
		while (true)
		{
			HeapFree(m_heap, NULL, m_message);
			m_message = (char*)HeapAlloc(m_heap, NULL, LocalSocket::BufferSize * sizeof(char));

			if (m_isSending)
			{
				continue;
			}
			get_report = ReadFile(m_pipe, m_message, LocalSocket::BufferSize * sizeof(char), &bytes_read, NULL);
			if (GetLastError() == ERROR_BROKEN_PIPE || !get_report)
			{
				if (GetLastError() == ERROR_OPERATION_ABORTED && m_isSending)
				{
					continue;
				}
				else
				{
					if (bool(m_discHandler) && !m_isSending)
					{
						m_discHandler();
					}
					return;
				}
			}

			if (get_report)
			{
				if (bool(m_reportHandler))
				{
					m_reportHandler(m_message);
				}
			}
		}
	});
}

LocalSocket::~LocalSocket()
{
	disconnect();
}

bool LocalSocket::send(string message)
{
	if (isConnected())
	{
		m_isSending = true;
		int message_size = (message.length() + 1) * sizeof(char);
		DWORD bytes_write = 0;

		CancelIoEx(m_pipe, NULL);

		bool message_send = WriteFile(
			m_pipe,
			message.c_str(),
			message_size,
			&bytes_write,
			NULL);

		if (!message_send || bytes_write != message_size)
		{
			disconnect();
			return false;
		}
		m_isSending = false;
		return true;
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
			DWORD mode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
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
	m_isSending = false;
	if (isConnected())
	{
		CancelIoEx(m_pipe, NULL);
	}
	HeapFree(m_heap, NULL, m_message);
	if (m_pipe)
	{
		CloseHandle(m_pipe);
	}
}

void LocalSocket::onDisconnect(std::function<void(void)> func)
{
	m_discHandler = func;
}

void LocalSocket::onGetReport(std::function<void(string)> func)
{
	m_reportHandler = func;
}
