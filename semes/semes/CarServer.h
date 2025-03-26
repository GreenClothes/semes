#pragma once
#include <thread>
#include "UDP.h"
#include "car.h"

class CarServer :public UDP, public Car {
private:
	std::thread serverThread;
	bool serverFlag = 1;

public:
	CarServer();
	void StartServer();
	void EndServer();
	std::string GetCarInform();
	void ServerLogic();

};