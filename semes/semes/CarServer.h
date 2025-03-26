#pragma once
#include <thread>
#include "UDP.h"

class CarServer :public UDP {
private:
	std::thread serverThread;
	bool serverFlag = 1;

public:
	CarServer();
	void StartServer();
	void EndServer();
	void ServerLogic();

};