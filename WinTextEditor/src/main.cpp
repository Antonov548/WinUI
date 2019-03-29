#include <WinUI>

class ButtonHandlerMainWindow : public Handler
{
public:
	virtual void handleEvent() override {
		_wnd->show();
	}

	Window* _wnd;
};

class ButtonHandlerDialogWindow : public Handler
{
public:
	virtual void handleEvent() override {
		_wnd->setWindowTitle(_title.c_str());
		_dialog->close();
	}

	std::string _title;
	Window* _dialog;
	Window* _wnd;
};

class DialogWindow : public Window
{
public:
	DialogWindow(Widget* parent = nullptr) : Window(parent), btn(this) {
		btn.setText("Сохранить");
		hdl_dialog._wnd = (Window*)(parent);
		hdl_dialog._dialog = this;
		hdl_dialog._title = "new text";
		btn.setClickHandler(&hdl_dialog);
	}

private:
	Button btn;
	LineEdit edit_title;
	ButtonHandlerDialogWindow hdl_dialog;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn(this), wnd_dialog(this) {
		btn.setGeometry(20, 20, btn.width(), btn.height());
		btn.setText("Открыть");
		wnd_dialog.setFixedSize(300, 200);
		hdl_dialog._wnd = &wnd_dialog;
		btn.setClickHandler(&hdl_dialog);
	}

private:
	DialogWindow wnd_dialog;
	Button btn;
	ButtonHandlerMainWindow hdl_dialog;
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