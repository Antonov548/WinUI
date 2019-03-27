#include "winui.h"


class ButtonHandler : public Handler
{
	virtual void handleEvent() override {
		MessageBox(NULL, L"Event", L"Work", MB_OK);
	}
};

class MainWindow : public Window
{
public:
	MainWindow() {

	}

private:
	Window wnd_dialog;
	Button btn;
	LineEdit edit_title;
	ButtonHandler hdl_dialog;
};

int main()
{
	Application app;

	Window wnd;
	wnd.setWindowTitle("Work");
	wnd.setMinimumSize(800, 800);

	Button btn("Hello", &wnd);
	btn.setFont("Arial", 13);
	btn.setGeometry(0, 0, btn.width(), btn.height());

	ButtonHandler btn_handler;
	btn.setClickHandler(&btn_handler);

	LineEdit edit(&wnd);
	edit.setGeometry(20, 100, edit.width(), edit.height());
	edit.setText("Введите текст");
	edit.setFont("Arial", 13);

	wnd.show();

	app.exec();
}