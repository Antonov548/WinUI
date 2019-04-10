#pragma once

#include "winstring.h"

namespace WinUI
{

	class FileSystem
	{
	public:
		FileSystem(string path, string filter);
		~FileSystem();

		bool findNext();
		bool isFile() const;
		bool isDirectory() const;
		string getFullName();
		string getName();

	private:
		string m_path;
		string m_filter;
		HANDLE m_handle;
		WIN32_FIND_DATA m_data;
	};

}