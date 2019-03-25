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
	btn.setFont("Arial", 13);
	btn.setGeometry(0, 0, btn.width(), btn.height());

	LineEdit edit(&wnd);
	edit.setGeometry(20, 100, edit.width(), edit.height());
	edit.setText("Введите текст");
	edit.setFont("Arial", 13);

	wnd.show();

	app.exec();
}