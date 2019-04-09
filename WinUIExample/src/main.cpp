#include <WinUI>
#include <vector>
#include <string>

class EditWindow : public Window
{
public:
	EditWindow(Widget* parent = nullptr) : Window(parent), line_edit(this), btn_save(this) {
		line_edit.setGeometry(0, 0, 280, line_edit.height());

		btn_save.setText("Save");
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

class MyThread : public Thread
{
public:
	MyThread()
	{

	}
	virtual void run()
	{
		int x = 0;
		while (true)
		{
			Thread::currend_thread.sleep(1000);
			MessageBox(NULL, std::to_string(GetCurrentThreadId()).c_str(), "same", MB_OK);
			if (x == 5)
			{
				count = 10;
				return;
			}
			x++;
		}
	}
	int count;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn_add(this), line_edit(this), check(this) {

		Label *label = new Label("Edit text", this);
		label->setFont("Arial", 13);
		label->setGeometry(0, 20, 300, 20);
		label->setAlignment(WinUI::AlignmentCenter);

		line_edit.setGeometry(0, 50, 280, line_edit.height());
		line_edit.setText("Text...");

		check.setGeometry(90, 80, 120, btn_add.height());
		check.setText("Change");

		btn_add.setGeometry(80, 120, 140, btn_add.height());
		btn_add.setText("add");
		btn_add.connect([&]() { thread.start(); thread.wait(); setWindowTitle(std::to_string(thread.count)); /*add();*/ });
	}

	void add()
	{
		Note *new_note = new Note(this);
		new_note->setGeometry(90, 180 + (int(list.size()) * 40), 120, new_note->height());
		new_note->setText("Note" + std::to_string(list.size() + 1));
		new_note->is_edit = check.isChecked();
		new_note->window_text = line_edit.text();
		line_edit.clear();
		list.push_back(new_note);
	}

	void setTextLine(std::string text)
	{
		line_edit.setText(text);
	}

private:
	LineEdit line_edit;
	Button btn_add;
	CheckBox check;
	std::vector<Note*> list;
	MyThread thread;
};

int main()
{
	Application app;

	MainWindow wnd;
	wnd.setWindowTitle("Work");
	wnd.setWidth(300);
	//wnd.setFixedSize(300, 400);

	/*MyThread thread;
	thread.start();
	thread.wait();*/

	wnd.show();

	MessageBox(NULL, std::to_string(GetCurrentThreadId()).c_str(), "same", MB_OK);

	app.exec();
}