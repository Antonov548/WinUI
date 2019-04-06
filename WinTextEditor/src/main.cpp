#include <WinUI>
#include <vector>

class EditWindow : public Window
{
public:
	EditWindow(Widget* parent = nullptr) : Window(parent), line_edit(this), btn_save(this) {
		line_edit.setGeometry(0, 0, 280, line_edit.height());
		
		btn_save.setText("Сохранить");
		btn_save.setGeometry(90, 40, 120, btn_save.height());
	}

	void openWindow(bool isEdit, string text)
	{
		line_edit.setReadOnly(!isEdit);
		line_edit.setText(text);
		show();
	}
	LineEdit line_edit;
	Button btn_save;
};

class Note : public Button
{
public:
	Note(Widget* parent = nullptr) : Button(parent) {
		window.setFixedSize(300, 150);
		connect([&]() {window.openWindow(is_edit, window_text); });
		window.btn_save.connect([&]() { window_text = window.line_edit.text(); window.hide(); });
	}

	bool is_edit;
	string window_text;
	EditWindow window;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn_add(this), line_edit(this), check(this) {

		Label *label = new Label("Список записей", this);
		label->setFont("Arial", 13);
		label->setGeometry(0, 20, 300, 20);
		label->setAlignment(WinUI::AlignmentCenter);

		line_edit.setGeometry(0, 50, 280, line_edit.height());
		line_edit.setText("Ввод...");

		check.setGeometry(90, 80, 120, btn_add.height());
		check.setText("Изменять");

		btn_add.setGeometry(80, 120, 140, btn_add.height());
		btn_add.setText("Добавить запись");
		btn_add.connect([&]() { add(); });
	}

	void add()
	{
		Note *new_note = new Note(this);
		new_note->setGeometry(90, 180 + (list.size() * 40), 120, new_note->height());
		new_note->setText("Запись №" + std::to_string(list.size()+1));
		new_note->is_edit = check.isChecked();
		new_note->window_text = line_edit.text();
		list.push_back(new_note);
	}

private:
	LineEdit line_edit;
	Button btn_add;
	CheckBox check;
	std::vector<Note*> list;
};


int main()
{
	Application app;

	MainWindow wnd;
	wnd.setWindowTitle("Редактор списка записей");
	wnd.setWidth(300);
	//wnd.setFixedSize(300, 400);

	wnd.show();

	app.exec();
}