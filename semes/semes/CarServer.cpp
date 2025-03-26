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
			// 정보 보내주는 로직
			Send("Type qaz wsx edc Engine qwe jms xxx wsww Steer ioio oiui ujjj jkjk lmlm hj Break popo", sender_endpoint);
		}
		else {
			// 차량 괜찮은지 확인하는 로직
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