#pragma once

enum QuesionType {
	CarType_Q,
	Engine_Q,
	BreakSystem_Q,
	SteeringSystem_Q,
	Run_Test,
};

enum CarType {
	SEDAN = 1,
	SUV,
	TRUCK
};

enum Engine {
	GM = 1,
	TOYOTA,
	WIA
};

enum BreakSystem {
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B
};

enum SteeringSystem {
	BOSCH_S = 1,
	MOBIS
};