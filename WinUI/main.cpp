#include "application.h"
#include "window.h"
#include "button.h"
#include "lineedit.h"

int main()
{
	Application app;

	Window wnd;
	wnd.setWindowTitle("Work");
	//wnd.setMinimumSize(800, 800);
	//wnd.setMaximumSize(500, 200);

	Button btn(&wnd, "Hello");
	btn.setGeometry(0, 0, btn.width(), btn.height());

	LineEdit edit(&wnd);
	edit.setGeometry(20, 20, edit.width(), edit.height());

	wnd.show();

	app.exec();
}