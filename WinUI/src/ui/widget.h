#pragma once

#include <windows.h>
#include <map>
#include "../application.h"
#include "../winstring.h"
#include "../style.h"

namespace WinUI
{

	struct Rect
	{
		int x;
		int y;
		int width;
		int height;
	};

	struct WidgetStyle
	{
		string class_name;
		Rect widget_size;
		Style widget_style;
		UINT class_style;
	};

	class Widget
	{
	public:
		Widget(WidgetStyle style, Widget* parent);
		virtual ~Widget();
		void setGeometry(int x, int y, int width, int height);
		void setWidth(int width);
		void setHeight(int height);
		void setFixedSize(int width, int height);
		void setParent(Widget* parent);
		void setVisible(bool visible);
		void addChild(HWND hwnd, Widget* widget);
		int x() const;
		int y() const;
		int width() const;
		int height() const;
		Rect size() const;
		HWND getHWND() const;
		bool isVisible() const;
		// static wndproc wich call procedure for each widget
		static LRESULT CALLBACK GlobalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		string getClassName() const;
		virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
		void setMinimumSize(int min_width, int min_height);
		void setMaximumSize(int wax_width, int max_height);

	protected:
		HWND m_hwnd;
		Widget* m_parent;
		//map for child widgets of window
		std::map<HWND, Widget*> m_child_widgets;

		bool m_isMaxInstalled;
		bool m_isMinInstalled;

		Rect m_minimumSize;
		Rect m_maximumSize;
		Rect m_size;

		static Widget* getWidgetPtr(HWND hwnd);
		static void addWidget(HWND hwnd, Widget* widget);
		static void removeWidget(HWND hwnd);

		void setStyle(Style style);
		void addStyle(Style style);
		void removeStyle(Style style);
		bool hasStyle(Style style);
		Style getStyle() const;

	private:
		WidgetStyle m_style;
		WNDCLASSEX m_wndclass;
		static std::map<HWND, Widget*> widget_map;

		void create();
		void recreateWidget();
		void createWidget(WidgetStyle style, string text = "");
		void registerClass(WidgetStyle style);
	};

}