#include <iostream>
#include <WinUICore>
#include <WinUIWidgets>

class MainWindow : public WinUI::Window
{
public:
	MainWindow(std::string server_name) : Window(), _client_messages(this), _server_message(this), _send(this)
	{
		setMinimumSize(300, 600);

		_server.listen(server_name);
		_server.onGetMessage([this](std::string message) {addMessage(message); });
		_server.onNewConnection([this]() {addMessage("New client connected"); });
		_server.onDisconnect([this]() {addMessage("Client disconnected"); });

		WinUI::Label* label = new WinUI::Label("Server name : " + server_name, this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(WinUI::Alignment::Center);

		_client_messages.setReadOnly(true);
		_client_messages.setGeometry(0, 30, 280, _client_messages.height() + 100);
		_client_messages.setText("");
		_client_messages.setFont("Times New Roman", 13);

		_server_message.setGeometry(0, 270, 280, _server_message.height());
		_server_message.setText("Message...");

		_send.setGeometry(80, 300, 140, _send.height());
		_send.setText("Send");
		_send.connect([this]() {_server.report(_server_message.text()); });
	}

	void addMessage(std::string mess)
	{
		std::string space = _client_messages.isEmpty() ? "" : "\r\n";
		_client_messages.setText(_client_messages.text() + space + mess);
	}

private:
	WinUI::TextArea _client_messages;
	WinUI::LineEdit _server_message;
	WinUI::LocalServer _server;

	WinUI::Button _send;
};

class ServerNameWindow : public WinUI::Window
{
public:
	ServerNameWindow() : _wnd(nullptr), _server_name(this), _accept(this)
	{
		setFixedSize(300, 200);

		WinUI::Label* label = new WinUI::Label("Enter server name", this);
		label->setFont("Times New Roman", 13);
		label->setGeometry(0, 0, 300, 20);
		label->setAlignment(WinUI::Alignment::Center);

		_server_name.setGeometry(0, 40, 300, 25);
		_server_name.setFont("Times New Roman", 13);

		_accept.setGeometry(105, 80, _accept.width(), _accept.height());
		_accept.setText("Okey");
		_accept.setFont("Times New Roman", 13);
		_accept.connect([this]()
			{
				if (_server_name.isEmpty())
				{
					MessageBox(NULL, "Invalid server name", "Error", MB_OK);
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
	WinUI::LineEdit _server_name;
	WinUI::Button _accept;
	MainWindow* _wnd;
};

int main()
{
	WinUI::Application app;

	ServerNameWindow name_window;
	name_window.show();

	app.exec();
}