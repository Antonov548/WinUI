#pragma once

#ifdef WINUI_EXPORTS
#define WINUI_DLL __declspec(dllexport)
#else
#define WINUI_DLL __declspec(dllimport)
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4355)
#pragma warning(disable: 4996)
#endif