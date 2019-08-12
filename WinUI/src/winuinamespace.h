#pragma once

#include <winui_export.h>

namespace WinUI
{
	enum class Alignment
	{
		Right,
		Left,
		Center
	};

	enum class ThreadPriority
	{
		Idle,
		Lowest,
		Low,
		Normal,
		High,
		Highest,
		TimeCritical
	};

	struct EnumFlags
	{
		int flags;
		int operator+(EnumFlags& enum_flags)
		{
			return flags | enum_flags.flags;
		}
		int operator-(EnumFlags& enum_flags)
		{
			return flags & ~enum_flags.flags;
		}
	};

	struct WINUILIB_EXPORT FileSystemFilter : EnumFlags
	{
		enum
		{
			Dirs = 0x01,
			Files = 0x02,
			NotDotAndDotDot = 0x04,
			Hidden = 0x08,
			NoFilters = 0x10
		};

		FileSystemFilter(int filters)
		{
			flags = filters;
		}
	};

	struct WINUILIB_EXPORT FontStyle : EnumFlags
	{
		enum
		{
			Regular = 0x01,
			Bold = 0x02,
			Italic = 0x04,
			Underline = 0x08,
			Strikeout = 0x10
		};

		FontStyle(int filters)
		{
			flags = filters;
		}
	};

}