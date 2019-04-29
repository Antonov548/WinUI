#include <WinUI>

class MainWindow : public Window
{
public:
	MainWindow(Widget* parent = nullptr);
	~MainWindow();

private:
	Button _btnConnect;
	Button _btnSend;
	LocalSocket _socket;
};

MainWindow::MainWindow(Widget* parent) : Window(parent), _btnConnect(this), _btnSend(this)
{
	setWidth(300);
	setHeight(450);

	_btnConnect.setText("Connect");
	_btnConnect.connect([this]() {_socket.connectToServer("fortune"); });

	_btnSend.setText("Текст");
	_btnSend.setGeometry(0, 50, _btnSend.width(), _btnSend.height());
	_btnSend.connect([this]() {_socket.send("2"); });
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