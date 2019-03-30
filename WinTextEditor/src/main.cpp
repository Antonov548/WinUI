#include <WinUI>

class DialogWindow : public Window
{
public:
	DialogWindow(Widget* parent = nullptr) : Window(parent), btn(this), edit_title(this), wnd_parent((Window*)(parent)) {
		btn.setText("Сохранить");
		btn.connect([&]() {wnd_parent->setWindowTitle(std::to_string(btn.isChecked())); });
		edit_title.setGeometry(0, 40, edit_title.width(), edit_title.height());
		edit_title.setText("Введите текст");
	}

private:
	CheckBox btn;
	LineEdit edit_title;
	Window* wnd_parent;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn(this), wnd_dialog(this) {
		btn.setGeometry(20, 20, btn.width(), btn.height());
		btn.setText("Открыть");
		btn.connect([&]() {wnd_dialog.show(); });
		wnd_dialog.setFixedSize(300, 200);
	}

	void openDialog()
	{
		wnd_dialog.show();
	}

private:
	DialogWindow wnd_dialog;
	Button btn;
};

int main()
{
	Application app;

	MainWindow wnd;
	wnd.setWindowTitle("Lab 1");
	wnd.setMinimumSize(800, 800);

	wnd.show();

	app.exec();
}