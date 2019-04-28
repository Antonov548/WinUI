#include <WinUI>

class MainWindow : public Window
{
public:
	MainWindow(Widget* parent = nullptr);
	~MainWindow();

private:
	Button _btnConnect;
	LocalSocket _socket;
};

MainWindow::MainWindow(Widget* parent) : Window(parent), _btnConnect(this)
{
	setWidth(300);
	setHeight(450);

	_btnConnect.setText("Connect");
	_btnConnect.connect([this]() {_socket.connectToServer("fortune"); });
}

MainWindow::~MainWindow()
{
}

int main()
{
	Application app;

	MainWindow wnd;
	wnd.show();

	app.exec();
}