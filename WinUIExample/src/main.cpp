#include <WinUI>

class MainWindow : public Window
{
public:
	MainWindow(string server_name) : Window(), _client_messages(this), _server_message(this), _send(this)
	{
		setMinimumSize(300, 600);

		_server.listen(server_name);
		_server.onGetMessage([this](string message) {addMessage(message); });
		_server.onNewConnection([this]() {addMessage("Новый клиент"); });
		_server.onDisconnect([this]() {addMessage("Клиент отключился"); });


		Label *label = new Label("Локальный сервер : " + server_name, this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(Alignment::Center);

		_client_messages.setReadOnly(true);
		_client_messages.setGeometry(0, 30, 280, _client_messages.height() + 100);
		_client_messages.setText("");
		_client_messages.setFont("Times New Roman", 13);

		_server_message.setGeometry(0, 270, 280, _server_message.height());
		_server_message.setText("Сообщение...");

		_send.setGeometry(80, 300, 140, _send.height());
		_send.setText("Отправить");
		_send.connect([this]() {_server.report(_server_message.text()); });
	}

	void addMessage(string mess)
	{
		string space = _client_messages.isEmpty() ? "" : "\r\n";
		_client_messages.setText(_client_messages.text() + space + mess);
	}

private:
	TextArea _client_messages;
	LineEdit _server_message;
	LocalServer _server;

	Button _send;
};

class ServerNameWindow : public Window
{
public:
	ServerNameWindow() : _wnd(nullptr),  _server_name(this), _accept(this)
	{
		setFixedSize(300, 200);

		Label *label = new Label("Введите название сервера", this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(Alignment::Center);

		_server_name.setGeometry(0, 40, 300, 25);
		_server_name.setFont("Times New Roman", 13);

		_accept.setGeometry(105, 80, _accept.width(), _accept.height());
		_accept.setText("Создать");
		_accept.setFont("Times New Roman", 13);
		_accept.connect([this]() 
		{
			if (_server_name.isEmpty())
			{
				MessageBox(NULL, "Введите название сервера", "Ошибка", MB_OK);
			}
			else
			{
				_wnd = new MainWindow(_server_name.text());
				_wnd->setWidth(300);
				_wnd->setHeight(500);
				_wnd->setMinimumSize(300, 500);
				_wnd->show();

				hide();
			}
		});
	}
	~ServerNameWindow()
	{
		delete _wnd;
	}

private:
	LineEdit _server_name;
	Button _accept;
	MainWindow* _wnd;
};

int main()
{
	Application app;

	ServerNameWindow name_window;
	name_window.show();

	app.exec();
}