#include <WinUI>

class DialogWindow : public Window
{
public:
	DialogWindow(Widget* parent = nullptr) : Window(parent), btn(this), edit_title(this), wnd_parent((Window*)(parent)) {
		btn.setText("Сохранить");
		btn.connect([&]() {wnd_parent->setWindowTitle(std::to_string(btn.isChecked())); }, Button::Clicked);
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
	MainWindow() : Window(), btn_open(this), btn_new(this), wnd_dialog(this) {

		Label *label = new Label("WinUI Редактор Текста", this);
		label->setFont("Arial", 15);
		label->setGeometry(0, 20, 300, 30);

		btn_open.setGeometry(90, 100, 120, btn_open.height());
		btn_open.setText("Открыть файл");
		btn_open.connect([&]() {wnd_dialog.show(); }, Button::Clicked);

		btn_new.setGeometry(90, 150, 120, btn_open.height());
		btn_new.setText("Новый файл");
		btn_new.connect([&]() {wnd_dialog.show(); }, Button::Clicked);
	}

	void openDialog()
	{
		wnd_dialog.show();
	}

private:
	DialogWindow wnd_dialog;
	Button btn_open;
	Button  btn_new;
};

int main()
{
	Application app;

	MainWindow wnd;
	wnd.setWindowTitle("Редактор текста");
	wnd.setFixedSize(300, 400);

	wnd.show();

	app.exec();
}