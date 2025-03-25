#pragma once

enum class QuesionType {
	CarType_Q,
	Engine_Q,
	BreakSystem_Q,
	SteeringSystem_Q,
	Run_Test,
};

enum class CarType {
	SEDAN = 1,
	SUV,
	TRUCK
};

enum class Engine {
	GM = 1,
	TOYOTA,
	WIA
};

enum class BreakSystem {
	MANDO = 1,
	CONTINENTAL,
	BOSCH
};

enum class SteeringSystem {
	BOSCH = 1,
	MOBIS
};