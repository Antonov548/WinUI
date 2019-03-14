#include "application.h"
#include "window.h"
#include "button.h"

int main()
{
	Application app;

	Window wnd;
	wnd.show();

	Window wnd_2;
	wnd_2.setWindowTitle("Hello world");

	Button btn(&wnd_2, "Ok");
	btn.setText("Not okey");

	wnd_2.show();

	app.exec();
}