#pragma once

#include "winstring.h"

namespace WinUI
{

	class WINUI_DLL FileSystem
	{
	public:
		struct WINUI_DLL Filter
		{
			enum
			{
				Dirs = 0x01,
				Files = 0x02,
				NotDotAndDotDot = 0x04,
				Hidden = 0x08,
				NoFilters = 0x10
			};

			Filter(int filters);

			int flags;
		};

		FileSystem(string path, string patern, Filter filter = Filter::NoFilters);
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
		Filter m_filter;
		HANDLE m_handle;
		WIN32_FIND_DATA m_data;

		bool checkFilter();
		bool findNext();
	};

}