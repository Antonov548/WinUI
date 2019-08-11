#include "abstractbutton.h"

using namespace WinUI;

AbstractButton::AbstractButton(WidgetStyle style, Widget* parent) : Widget(style, parent)
{
}

AbstractButton::~AbstractButton()
{
}

LRESULT AbstractButton::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
  case WM_COMMAND:
  {
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
    {
      if (bool(m_clickHandler))
      {
        m_clickHandler();
      }
    }
    break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
    }
  }
  break;
	case WM_DESTROY:
	{
		removeWidget(hwnd);
		DestroyWindow(hwnd);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void AbstractButton::setText(string text)
{
	SetWindowTextA(m_hwnd, text.c_str());
}

void AbstractButton::setFont(string font_family, int font_size)
{
	const long nFontSize = font_size;
	HDC hdc = GetDC(m_hwnd);

	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_NORMAL;

	strcpy(logFont.lfFaceName, font_family.c_str());

	HFONT s_hFont = CreateFontIndirect(&logFont);
	ReleaseDC(m_hwnd, hdc);
	SendMessage(m_hwnd, WM_SETFONT, (WPARAM)s_hFont, TRUE);
}

void AbstractButton::connect(std::function<void(void)> func)
{
	m_clickHandler = func;
}
