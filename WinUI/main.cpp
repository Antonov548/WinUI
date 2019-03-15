#include "application.h"
#include "window.h"
#include "button.h"
#include "lineedit.h"

int main()
{
	Application app;

	Window wnd;
	wnd.show();

	Window wnd_2;
	wnd_2.setWindowTitle("Hello world");

	LineEdit lineedit(&wnd_2);
	lineedit.setText("Hello nothing");
	lineedit.setFont("Calibri", 8);

	wnd_2.show();

	app.exec();
}