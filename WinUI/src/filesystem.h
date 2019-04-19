#pragma once

#include "winstring.h"
#include "winuinamespace.h"

namespace WinUI
{

	class WINUI_DLL FileSystem
	{
	public:
		FileSystem(string path, string patern, FileSystemFilter filter = FileSystemFilter::NoFilters);
		~FileSystem();

		bool next();
		bool isFile() const;
		bool isDirectory() const;
		string getFullName();
		string getName();
		bool isWrongPath() const;

	private:
		bool m_isFindError;
		string m_path;
		FileSystemFilter m_filter;
		HANDLE m_handle;
		WIN32_FIND_DATA m_data;

		bool checkFilter();
		bool findNext();
	};

}