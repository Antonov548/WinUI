#include <WinUI>

class MainWindow : public Window
{
public:
	MainWindow(string client_name, string server_name) : _clientName(client_name), _clientMessage(this), _btnSend(this), _serverMessages(this)
	{
		setMinimumSize(300, 600);

		_socket.connectToServer(server_name);
		_socket.onGetReport([this](string msg) {addServerMessage(msg); });

		Label *label = new Label("Локальный клиент : " + server_name, this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(Alignment::Center);

		Label *label_client = new Label("Имя клиента : " + client_name, this);
		label_client->setFont("Times New Roman", 13);
		label_client->setGeometry(0, 20, 300, 20);
		label_client->setAlignment(Alignment::Center);

		_clientMessage.setGeometry(0, 50, 300, 25);
		_clientMessage.setText("");
		_clientMessage.setFont("Times New Roman", 13);

		_btnSend.setText("Отправить");
		_btnSend.setGeometry((300 - _btnSend.width())/2, 80, _btnSend.width(), _btnSend.height());
		_btnSend.connect([this]() {_socket.send(_clientName + "[клиент]:" + _clientMessage.text()); });

		Label *label_server = new Label("Сообщения свервера", this);
		label_server->setFont("Times New Roman", 13);
		label_server->setGeometry(0, 130, 300, 20);
		label_server->setAlignment(Alignment::Center);

		_serverMessages.setGeometry(0, 150, 280, _serverMessages.height() + 100);
		_serverMessages.setText("");
		_serverMessages.setFont("Times New Roman", 13);
		_serverMessages.setReadOnly(true);
	}
	~MainWindow()
	{

	}

private:
	Button _btnSend;
	TextArea _serverMessages;
	LineEdit _clientMessage;
	LocalSocket _socket;
	string _clientName;

	void addServerMessage(string msg)
	{
		string space = _serverMessages.isEmpty() ? "" : "\r\n";
		_serverMessages.setText(_serverMessages.text() + space + msg);
	}
};

class LoginWindow : public Window
{
public:
	LoginWindow() : _wnd(nullptr), _clientName(this), _serverName(this), _accept(this)
	{
		setFixedSize(320, 280);

		Label *label = new Label("Локальный клиент", this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(Alignment::Center);
	
		Label *label_server = new Label("Название сервера", this);
		label_server->setFont("Times New Roman", 13);
		label_server->setGeometry(0, 40, 300, 20);
		label_server->setAlignment(Alignment::Center);

		_serverName.setGeometry(0, 60, 300, 25);
		_serverName.setFont("Times New Roman", 13);

		Label *label_client = new Label("Имя клиента", this);
		label_client->setFont("Times New Roman", 13);
		label_client->setGeometry(0, 100, 300, 20);
		label_client->setAlignment(Alignment::Center);

		_clientName.setGeometry(0, 120, 300, 25);
		_clientName.setFont("Times New Roman", 13);

		_accept.setFont("Times New Roman", 13);
		_accept.setGeometry(110, 170, _accept.width(), _accept.height());
		_accept.setText("Войти");
		_accept.connect([this]() {
			if (_clientName.isEmpty() || _serverName.isEmpty())
			{
				MessageBox(NULL, "Введите данные", "Ошибка", MB_OK);
			}
			else
			{
				_wnd = new MainWindow(_clientName.text(), _serverName.text());
				_wnd->setWidth(300);
				_wnd->setHeight(500);
				_wnd->show();
				hide();
			}
		});
	}

	~LoginWindow()
	{
		delete _wnd;
	}

private:
	LineEdit _clientName;
	LineEdit _serverName;
	Button _accept;
	MainWindow* _wnd;
};


int main()
{
	Application app;

	LoginWindow login_window;
	login_window.show();

	app.exec();
}