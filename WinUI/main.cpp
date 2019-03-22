#include "application.h"
#include "window.h"
#include "button.h"

int main()
{
	Application app;

	Window wnd;
	wnd.setWindowTitle("Work");

	Button btn(&wnd, "Hello");
	btn.setGeometry(200, 200, btn.width(), btn.height());

	wnd.show();

	app.exec();
}