#include "winui.h"


class ButtonHandler : public Handler
{
public:
	virtual void handleEvent() override {
		_wnd->show();
	}

	Window* _wnd;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn(this), wnd_dialog(this) {
		btn.setGeometry(20, 20, btn.width(), btn.height());
		btn.setText("Открыть");
		wnd_dialog.setMaximumSize(300, 200);
		hdl_dialog._wnd = &wnd_dialog;
		btn.setClickHandler(&hdl_dialog);
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

	MainWindow wnd;
	wnd.setWindowTitle("Lab 1");
	wnd.setMinimumSize(800, 800);

	/*Button btn("Hello", &wnd);
	btn.setFont("Arial", 13);
	btn.setGeometry(0, 0, 100, 100);

	ButtonHandler btn_handler;
	btn.setClickHandler(&btn_handler);

	LineEdit edit(&wnd);
	edit.setGeometry(20, 100, edit.width(), edit.height());
	edit.setText("Введите текст");
	edit.setFont("Arial", 13);*/

	wnd.show();

	app.exec();
}