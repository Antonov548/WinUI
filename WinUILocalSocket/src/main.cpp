#include <WinUICore>
#include <WinUIWidgets>

class MainWindow : public WinUI::Window
{
public:
	MainWindow(std::string client_name, std::string server_name) : _clientName(client_name), _clientMessage(this), _btnSend(this), _serverMessages(this)
	{
		setMinimumSize(300, 600);

		_socket.connectToServer(server_name);
		_socket.onGetReport([this](std::string msg) {addServerMessage(msg); });
		_socket.onDisconnect([this]() {std::string space = _serverMessages.isEmpty() ? "" : "\r\n"; _serverMessages.setText(_serverMessages.text() + space + "Ñåðâåð îòêëþ÷åí"); });

		WinUI::Label *label = new WinUI::Label("Local server : " + server_name, this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(WinUI::Alignment::Center);

		WinUI::Label *label_client = new WinUI::Label("Client name : " + client_name, this);
		label_client->setFont("Times New Roman", 13);
		label_client->setGeometry(0, 20, 300, 20);
		label_client->setAlignment(WinUI::Alignment::Center);

		_clientMessage.setGeometry(0, 50, 300, 25);
		_clientMessage.setText("");
		_clientMessage.setFont("Times New Roman", 13);

		_btnSend.setText("Send");
		_btnSend.setGeometry((300 - _btnSend.width()) / 2, 80, _btnSend.width(), _btnSend.height());
		_btnSend.connect([this]() {_socket.send(_clientName + "[client]:" + _clientMessage.text()); });

		WinUI::Label *label_server = new WinUI::Label("Message :", this);
		label_server->setFont("Times New Roman", 13);
		label_server->setGeometry(0, 130, 300, 20);
		label_server->setAlignment(WinUI::Alignment::Center);

		_serverMessages.setGeometry(0, 150, 280, _serverMessages.height() + 100);
		_serverMessages.setText("");
		_serverMessages.setFont("Times New Roman", 13);
		_serverMessages.setReadOnly(true);
	}
	~MainWindow()
	{

	}

private:
	WinUI::Button _btnSend;
	WinUI::TextArea _serverMessages;
	WinUI::LineEdit _clientMessage;
	WinUI::LocalSocket _socket;
	std::string _clientName;

	void addServerMessage(std::string msg)
	{
		std::string space = _serverMessages.isEmpty() ? "" : "\r\n";
		_serverMessages.setText(_serverMessages.text() + space + msg);
	}
};

class LoginWindow : public WinUI::Window
{
public:
	LoginWindow() : _wnd(nullptr), _clientName(this), _serverName(this), _accept(this)
	{
		setFixedSize(320, 280);

		WinUI::Label *label = new WinUI::Label("Local client", this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(WinUI::Alignment::Center);

		WinUI::Label *label_server = new WinUI::Label("Server name :", this);
		label_server->setFont("Times New Roman", 13);
		label_server->setGeometry(0, 40, 300, 20);
		label_server->setAlignment(WinUI::Alignment::Center);

		_serverName.setGeometry(0, 60, 300, 25);
		_serverName.setFont("Times New Roman", 13);

		WinUI::Label *label_client = new WinUI::Label("Client name :", this);
		label_client->setFont("Times New Roman", 13);
		label_client->setGeometry(0, 100, 300, 20);
		label_client->setAlignment(WinUI::Alignment::Center);

		_clientName.setGeometry(0, 120, 300, 25);
		_clientName.setFont("Times New Roman", 13);

		_accept.setFont("Times New Roman", 13);
		_accept.setGeometry(110, 170, _accept.width(), _accept.height());
		_accept.setText("Login");
		_accept.connect([this]() {
			if (_clientName.isEmpty() || _serverName.isEmpty())
			{
				MessageBox(NULL, "Invalid client name or server name", "Error", MB_OK);
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
	WinUI::LineEdit _clientName;
	WinUI::LineEdit _serverName;
	WinUI::Button _accept;
	MainWindow* _wnd;
};


int main()
{
	WinUI::Application app;

	LoginWindow login_window;
	login_window.show();

	app.exec();
}