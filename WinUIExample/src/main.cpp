#include <WinUI.>
#include <vector>
#include <string>

class WindowFind : public Window
{
public:
	WindowFind(Widget* parent = nullptr) : Window(parent), line_edit(this), btn_stop(this) {
		setGeometry(x(), y(), 300, 200);

		line_edit.setGeometry(0, 0, 280, line_edit.height());
		line_edit.setReadOnly(true);

		btn_stop.setText("Stop");
		btn_stop.setGeometry(90, 40, 120, btn_stop.height());
	}
	LineEdit line_edit;
	Button btn_stop;
	void setFoundText(string text)
	{
		line_edit.setText(text);
	}
};

class MyThread : public Thread
{
public:
	MyThread()
	{

	}
	virtual void run()
	{

		FileSystem system(path, "*");
		if (files.size() != 0)
		{
			files.clear();
		}
		if (!system.findNext())
		{
			MessageBox(NULL, "File/Folder not found", "ERROR", MB_OK);
			return;
		}
		else
		{
			files.push_back(system.getName());
		}
		while (system.findNext())
		{
			files.push_back(system.getName());
		}
	}
	int count;
	string path;
	std::vector<string> files;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn_find(this), line_edit(this) {

		Label *label = new Label("Find File", this);
		label->setFont("Arial", 13);
		label->setGeometry(0, 20, 300, 20);
		label->setAlignment(WinUI::AlignmentCenter);

		line_edit.setGeometry(0, 50, 280, line_edit.height());
		line_edit.setText("Path...");

		btn_find.setGeometry(80, 120, 140, btn_find.height());
		btn_find.setText("Find");
		btn_find.connect([&]() { MyThread* thread = new MyThread; thread->path = line_edit.text(); thread->start(); thread->wait(); showFiles(thread->files); delete thread; });
	}

private:
	LineEdit line_edit;
	Button btn_find;
	std::vector<Label*> vector_files;

	void showFiles(std::vector<string> files)
	{
		if (vector_files.size() != 0)
		{
			for (auto val : vector_files)
			{
				delete val;
				vector_files.clear();
			}
		}

		int count = 0;
		for (auto& val : files)
		{
			Label *file = new Label(this);
			file->setGeometry(90, 180 + (count * 40), 120, file->height());
			file->setText(val);
			vector_files.push_back(file);
			count++;
		}
	}
};

int main()
{
	Application app;

	MainWindow wnd;
	wnd.setWindowTitle("Find file");
	wnd.setWidth(300);

	wnd.show();

	app.exec();
}