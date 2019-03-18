#include "application.h"
#include "window.h"
#include "button.h"
#include "lineedit.h"

int main()
{
	Application app;

	Window wnd;
	wnd.show();

	app.exec();
}