#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carInfo.h"
#include "compatibility_.h"

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectBreakSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

//enum QuesionType {
//	CarType_Q,
//	Engine_Q,
//	BreakSystem_Q,
//	SteeringSystem_Q,
//	Run_Test,
//};
//
//enum CarType {
//	SEDAN = 1,
//	SUV,
//	TRUCK
//};
//
//enum Engine {
//	GM = 1,
//	TOYOTA,
//	WIA
//};
//
//enum BreakSystem {
//	MANDO = 1,
//	CONTINENTAL,
//	BOSCH_B
//};
//
//enum SteeringSystem {
//	BOSCH_S = 1,
//	MOBIS
//};

void delay(int ms) {
	volatile int sum = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			for (int t = 0; t < ms; t++) {
				sum++;
			}
		}
	}
}

Compatibility_ compatibility_;

int main() {
	char buf[100];
	int step = CarType_Q;

	compatibility_.add_incompatible_part("break", CarType::SEDAN, BreakSystem::CONTINENTAL);
	compatibility_.add_incompatible_part("engine", CarType::SUV, Engine::TOYOTA);
	compatibility_.add_incompatible_part("engine", CarType::TRUCK, Engine::WIA);
	compatibility_.add_incompatible_part("break", CarType::TRUCK, BreakSystem::MANDO);

	compatibility_.add_compatible_part("break", BreakSystem::BOSCH_B, "steering", SteeringSystem::BOSCH_S);
	compatibility_.add_compatible_part("steering", SteeringSystem::BOSCH_S, "break", BreakSystem::BOSCH_B);

	while (1) {

		if (step == CarType_Q) {
			printf(CLEAR_SCREEN);


			printf("        ______________\n");
			printf("       /|            | \n");
			printf("  ____/_|_____________|____\n");
			printf(" |                      O  |\n");
			printf(" '-(@)----------------(@)--'\n");
			printf("===============================\n");
			printf("� ���� Ÿ���� �����ұ��?\n");
			printf("1. Sedan\n");
			printf("2. SUV\n");
			printf("3. Truck\n");
		}
		else if (step == Engine_Q) {
			printf(CLEAR_SCREEN);
			printf("� ������ ž���ұ��?\n");
			printf("0. �ڷΰ���\n");
			printf("1. GM\n");
			printf("2. TOYOTA\n");
			printf("3. WIA\n");
			printf("4. ���峭 ����\n");
		}
		else if (step == BreakSystem_Q) {
			printf(CLEAR_SCREEN);
			printf("� ������ġ�� �����ұ��?\n");
			printf("0. �ڷΰ���\n");
			printf("1. MANDO\n");
			printf("2. CONTINENTAL\n");
			printf("3. BOSCH\n");
		}
		else if (step == SteeringSystem_Q) {
			printf(CLEAR_SCREEN);
			printf("� ������ġ�� �����ұ��?\n");
			printf("0. �ڷΰ���\n");
			printf("1. BOSCH\n");
			printf("2. MOBIS\n");
		}
		else if (step == Run_Test) {
			printf(CLEAR_SCREEN);
			printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
			printf("� ������ �ұ��?\n");
			printf("0. ó�� ȭ������ ���ư���\n");
			printf("1. RUN\n");
			printf("2. Test\n");
		}
		printf("===============================\n");

		printf("INPUT > ");
		fgets(buf, sizeof(buf), stdin);

		//���� ���๮�� ����
		strtok(buf, "\r");
		strtok(buf, "\n");


		if (!strcmp(buf, "exit")) {
			printf("���̹���\n");
			break;
		}

		//���ڷ� �� ������� Ȯ��
		char* checkNumber;
		int answer = strtol(buf, &checkNumber, 10); //���ڿ��� 10������ ��ȯ

		//�Է¹��� ���ڰ� ���ڰ� �ƴ϶��
		if (*checkNumber != '\0') {
			printf("ERROR :: ���ڸ� �Է� ����\n");
			delay(800);
			continue;
		}

		if (step == CarType_Q && !(answer >= 1 && answer <= 3)) {
			printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
			delay(800);
			continue;
		}

		if (step == Engine_Q && !(answer >= 0 && answer <= 4)) {
			printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
			delay(800);
			continue;
		}

		if (step == BreakSystem_Q && !(answer >= 0 && answer <= 3)) {
			printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
			delay(800);
			continue;
		}

		if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) {
			printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
			delay(800);
			continue;
		}

		if (step == Run_Test && !(answer >= 0 && answer <= 2)) {
			printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
			delay(800);
			continue;
		}

		//ó������ ���ư���
		if (answer == 0 && step == Run_Test) {
			step = CarType_Q;
			continue;
		}

		//�������� ���ư���
		if (answer == 0 && step >= 1) {
			step -= 1;
			continue;
		}

		if (step == CarType_Q) {
			selectCarType(answer);
			delay(800);
			step = Engine_Q;
		}
		else if (step == Engine_Q) {
			selectEngine(answer);
			delay(800);
			step = BreakSystem_Q;
		}
		else if (step == BreakSystem_Q) {
			selectBreakSystem(answer);
			delay(800);
			step = SteeringSystem_Q;
		}
		else if (step == SteeringSystem_Q) {
			selectSteeringSystem(answer);
			delay(800);
			step = Run_Test;
		}
		else if (step == Run_Test && answer == 1) {
			runProducedCar();
			delay(800);
		}
		else if (step == Run_Test && answer == 2) {
			testProducedCar();
			delay(800);
		}
	}

}

void selectCarType(int answer) {
	stack[CarType_Q] = answer;
	if (answer == 1) printf("���� Ÿ������ ������ �����ϼ̽��ϴ�.\n");
	if (answer == 2) printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
	if (answer == 3) printf("���� Ÿ������ TRUCK�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer) {
	stack[Engine_Q] = answer;
	if (answer == 1) printf("GM ������ �����ϼ̽��ϴ�.\n");
	if (answer == 2) printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
	if (answer == 3) printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectBreakSystem(int answer) {
	stack[BreakSystem_Q] = answer;
	if (answer == 1) printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
	if (answer == 2) printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
	if (answer == 3) printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer) {
	stack[SteeringSystem_Q] = answer;
	if (answer == 1) printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
	if (answer == 2) printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

void runProducedCar() {
	if (stack[Engine_Q] == 4) {
		printf("������ ���峵���ϴ�.\n");
		printf("�ڵ����� �������� �ʽ��ϴ�.\n");
	}
	else {
		printf("�ڵ����� ���۵˴ϴ�.\n");
	}
}

void testProducedCar() {
	std::unordered_map<std::string, Part> parts;
	parts.insert({ "car", CarType(stack[CarType_Q])});
	parts.insert({ "engine", Engine(stack[Engine_Q])});
	parts.insert({ "break", BreakSystem(stack[BreakSystem_Q])});
	parts.insert({ "steering", SteeringSystem(stack[SteeringSystem_Q])});
	
	if (compatibility_.is_compatible_all(parts)) {
		printf("�ڵ��� �׽�Ʈ ��� : PASS\n");
	}
	else {
		printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
	}
}