#include <WinUI>
#include <vector>
#include <string>

class MyThread : public Thread
{
public:
	MyThread()
	{

	}
	virtual void run()
	{
		if (filter.length() == 0)
		{
			filter = "*";
		}
		else
		{
			filter = "*" + filter;
		}

		FileSystem system(path, "", FileSystem::Filter::Hidden | FileSystem::Filter::Files);
		if (files.size() != 0)
		{
			files.clear();
		}
		if (system.isWrongPath())
		{
			MessageBox(NULL, "File/Folder not found", "ERROR", MB_OK);
			return;
		}
		else
		{
			files.push_back(system.getName());
		}
		while (system.next())
		{
			files.push_back(system.getName());
		}
	}
	int count;
	string path;
	string filter;
	std::vector<string> files;
};

class MainWindow : public Window
{
public:
	MainWindow() : Window(), btn_find(this), line_edit(this), line_edit_filter(this){

		Label *label = new Label("Find File", this);
		label->setFont("Arial", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(Alignment::Center);

		line_edit.setGeometry(0, 30, 280, line_edit.height());
		line_edit.setText("");

		line_edit_filter.setGeometry(0, 60, 280, line_edit.height());
		line_edit_filter.setText("");

		btn_find.setGeometry(80, 100, 140, btn_find.height());
		btn_find.setText("Find");
		btn_find.connect([&]() { MyThread thread; thread.path = line_edit.text(); thread.filter = line_edit_filter.text();  thread.start(); thread.wait(); showFiles(thread.files);});
	}

private:
	LineEdit line_edit;
	LineEdit line_edit_filter;
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