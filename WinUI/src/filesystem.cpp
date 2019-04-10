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
		bool isFound = FindNextFile(m_handle, &m_data);
		return isFound;
	}
}

bool FileSystem::isFile() const
{
	return m_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? false : true;
}

bool FileSystem::isDirectory() const
{
	return m_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? true : false;
}

string FileSystem::getFullName()
{
	return m_path + getName();
}

string FileSystem::getName()
{
	if (m_handle)
	{
		return wstr_to_str(m_data.cFileName);
	}
	return "";
}
