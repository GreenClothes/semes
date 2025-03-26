#include "CarServer.h"

CarServer::CarServer()
{
}

void CarServer::StartServer() {
	serverThread = std::thread([=]() { ServerLogic(); });
}

void CarServer::EndServer() {
	serverFlag = 0;
	if(serverThread.joinable()) serverThread.join();
}

void CarServer::ServerLogic() {
	std::string msg;

	while (serverFlag) {
		udp::endpoint sender_endpoint = Receive(&msg);
		if (msg == "init") {
			// ���� �����ִ� ����
			Send("Type qaz wsx edc Engine qwe jms xxx wsww Steer ioio oiui ujjj jkjk lmlm hj Break popo", sender_endpoint);
		}
		else {
			// ���� �������� Ȯ���ϴ� ����
			Send("It is good", sender_endpoint);
		}
	}
}

int main() {
	CarServer* cs = new CarServer();
	cs->StartServer();
	while (1) {
		std::string a;
		std::cin >> a;
		if (a == "bye") break;
	}
	cs->EndServer();
	delete cs;
}