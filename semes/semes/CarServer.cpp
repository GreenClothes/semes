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

std::string CarServer::GetCarInform() {

	std::string carData = "";
	carData += "Type ";
	for (const auto& carTypeName : carTypeNames) {
		carData += carTypeName.second;
		carData += " ";
	}
	carData += "Engine ";
	for (const auto& engineTypeName : engineTypeNames) {
		carData += engineTypeName.second;
		carData += " ";
	}
	carData += "Break ";
	for (const auto& breakSystemName : breakSystemNames) {
		carData += breakSystemName.second;
		carData += " ";
	}
	carData += "Steer ";
	for (const auto& steeringSystemName : steeringSystemNames) {
		carData += steeringSystemName.second;
		carData += " ";
	}

	return carData;
}

void CarServer::ServerLogic() {
	std::string msg;

	while (serverFlag) {
		udp::endpoint sender_endpoint = Receive(&msg);
		if (msg == "init") {
			std::string carData = GetCarInform();
			Send(carData, sender_endpoint);
		}
		else {
			// 차량 괜찮은지 확인하는 로직
			Send("It is good", sender_endpoint);
		}
	}
}
