#include "filesystem.h"

using namespace WinUI;

FileSystem::FileSystem(string path, string patern, Filter filter) : m_path(path), m_filter(filter), m_handle(NULL)
{
	m_handle = FindFirstFile(str_to_wstr(m_path + patern).c_str(), &m_data);
	m_isFindError = false;
	if (int(m_handle) == -1)
	{
		m_handle = NULL;
		m_isFindError = true;
	}
	else
	{
		if (!checkFilter())
		{
			m_isFindError = !next();
		}
	}
}

FileSystem::~FileSystem()
{
	if (m_handle)
		FindClose(m_handle);
}

bool FileSystem::next()
{
	if (!m_isFindError)
	{
		do
		{
			if (!findNext())
			{
				m_isFindError = true;
				return false;
			}
		} while (!checkFilter());
		return true;
	}
	return false;
}

bool FileSystem::findNext()
{
	bool isFound = false;
	if (m_handle)
		isFound = FindNextFile(m_handle, &m_data);
	return isFound;
}

bool FileSystem::isWrongPath() const
{
	return m_isFindError;
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

bool FileSystem::checkFilter()
{
	if (m_filter.flags & Filter::NoFilters)
	{
		return true;
	}

	if (m_filter.flags & Filter::NotDotAndDotDot)
	{
		string name = getName();
		if (name == "." || name == "..")
		{
			return false;
		}
	}

	if (m_filter.flags & Filter::Dirs)
	{
		if (isDirectory() && getName()[0] != '.')
		{
			return true;
		}
	}

	if (m_filter.flags & Filter::Files)
	{
		if (isFile() && getName()[0] != '.')
		{
			return true;
		}
	}

	if (m_filter.flags & Filter::Hidden)
	{
		string name = getName();
		if (name[0] == '.' && (name != "." && name != ".."))
		{
			return true;
		}
	}

	return false;
}

FileSystem::Filter::Filter(int filters)
{
	flags = filters;
}
