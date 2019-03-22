#include "application.h"
#include "window.h"

int main()
{
	Application app;

	Window wnd;
	wnd.setWindowTitle("Work");
	wnd.show();

	app.exec();
}