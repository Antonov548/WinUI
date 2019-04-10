#include "filesystem.h"

using namespace WinUI;

FileSystem::FileSystem(string path, string filter) : m_path(path), m_filter(filter), m_handle(NULL)
{
}

FileSystem::~FileSystem()
{
	if (m_handle)
		FindClose(m_handle);
}

bool FileSystem::findNext()
{
	if (!m_handle)
	{
		m_handle = FindFirstFile(str_to_wstr(m_path + m_filter).c_str(), &m_data);
		return m_handle ?  true : false;
	}
	else
	{
		return bool(FindNextFile(m_handle, &m_data));
	}
}

string FileSystem::getName()
{
	if (m_handle)
	{
		return wstr_to_str(m_data.cFileName);
	}
	return "";
}
