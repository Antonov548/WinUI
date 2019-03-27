#include "abstractbutton.h"

AbstractButton::AbstractButton(WidgetStyle style, Window* parent) : Widget(style, parent)
{
	parent->addChild(this);
}

AbstractButton::~AbstractButton()
{
}

void AbstractButton::setClickHandler(Handler * event)
{
	m_clickHandler = event;
}

void AbstractButton::click()
{
	m_clickHandler->handleEvent();
}

LRESULT AbstractButton::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MessageBox(NULL, L"Work", L"Hello", MB_OK);
	return DefWindowProc(hwnd, message, wParam, lParam);
}
