#include "abstractbutton.h"

AbstractButton::AbstractButton(WidgetStyle style, Widget* parent) : Widget(style, parent)
{
	if (parent)
	{
		parent->addChild(m_hwnd, this);
	}
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
	if (m_clickHandler) 
	{
		m_clickHandler->handleEvent();
	}
}

LRESULT AbstractButton::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (HIWORD(wParam))
	{
	case BN_CLICKED:
		click();
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
