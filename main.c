#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectBreakSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);




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

int main() {
	char buf[100];
	int step = CarType_Q;

	while (1) {

		if (step == CarType_Q) {
			printf(CLEAR_SCREEN);


			printf("        ______________\n");
			printf("       /|            | \n");
			printf("  ____/_|_____________|____\n");
			printf(" |                      O  |\n");
			printf(" '-(@)----------------(@)--'\n");
			printf("===============================\n");
			printf("어떤 차량 타입을 선택할까요?\n");
			printf("1. Sedan\n");
			printf("2. SUV\n");
			printf("3. Truck\n");
		}
		else if (step == Engine_Q) {
			printf(CLEAR_SCREEN);
			printf("어떤 엔진을 탑재할까요?\n");
			printf("0. 뒤로가기\n");
			printf("1. GM\n");
			printf("2. TOYOTA\n");
			printf("3. WIA\n");
			printf("4. 고장난 엔진\n");
		}
		else if (step == BreakSystem_Q) {
			printf(CLEAR_SCREEN);
			printf("어떤 제동장치를 선택할까요?\n");
			printf("0. 뒤로가기\n");
			printf("1. MANDO\n");
			printf("2. CONTINENTAL\n");
			printf("3. BOSCH\n");
		}
		else if (step == SteeringSystem_Q) {
			printf(CLEAR_SCREEN);
			printf("어떤 조향장치를 선택할까요?\n");
			printf("0. 뒤로가기\n");
			printf("1. BOSCH\n");
			printf("2. MOBIS\n");
		}
		else if (step == Run_Test) {
			printf(CLEAR_SCREEN);
			printf("멋진 차량이 완성되었습니다.\n");
			printf("어떤 동작을 할까요?\n");
			printf("0. 처음 화면으로 돌아가기\n");
			printf("1. RUN\n");
			printf("2. Test\n");
		}
		printf("===============================\n");

		printf("INPUT > ");
		fgets(buf, sizeof(buf), stdin);

		//엔터 개행문자 제거
		strtok(buf, "\r");
		strtok(buf, "\n");
		

		if (!strcmp(buf, "exit")) {
			printf("바이바이\n");
			break;
		}

		//숫자로 된 대답인지 확인
		char* checkNumber;
		int answer = strtol(buf, &checkNumber, 10); //문자열을 10진수로 변환

		//입력받은 문자가 숫자가 아니라면
		if (*checkNumber != '\0') {
			printf("ERROR :: 숫자만 입력 가능\n");
			delay(800);
			continue;
		}

		if (step == CarType_Q && !(answer >= 1 && answer <= 3)) {
			printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
			delay(800);
			continue;
		}

		if (step == Engine_Q && !(answer >= 0 && answer <= 4)) {
			printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
			delay(800);
			continue;
		}

		if (step == BreakSystem_Q && !(answer >= 0 && answer <= 3)) {
			printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
			delay(800);
			continue;
		}

		if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) {
			printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
			delay(800);
			continue;
		}

		if (step == Run_Test && !(answer >= 0 && answer <= 2)) {
			printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
			delay(800);
			continue;
		}

		//처음으로 돌아가기
		if (answer == 0 && step == Run_Test) {
			step = CarType_Q;
			continue;
		}
		
		//이전으로 돌아가기
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
	if (answer == 1) printf("차량 타입으로 세단을 선택하셨습니다.\n");
	if (answer == 2) printf("차량 타입으로 SUV을 선택하셨습니다.\n");
	if (answer == 3) printf("차량 타입으로 TRUCK을 선택하셨습니다.\n");
}

void selectEngine(int answer) {
	stack[Engine_Q] = answer;
	if (answer == 1) printf("GM 엔진을 선택하셨습니다.\n");
	if (answer == 2) printf("TOYOTA 엔진을 선택하셨습니다.\n");
	if (answer == 3) printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectBreakSystem(int answer) {
	stack[BreakSystem_Q] = answer;
	if (answer == 1) printf("MANDO 제동장치를 선택하셨습니다.\n");
	if (answer == 2) printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
	if (answer == 3) printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer) {
	stack[SteeringSystem_Q] = answer;
	if (answer == 1) printf("BOSCH 제동장치를 선택하셨습니다.\n");
	if (answer == 2) printf("MOBIS 제동장치를 선택하셨습니다.\n");
}

void runProducedCar() {
	if (stack[Engine_Q] == 4) {
		printf("엔진이 고장났습니다.\n");
		printf("자동차가 움직이지 않습니다.\n");
	}
	else {
		printf("자동차가 동작됩니다.\n");
	}
}

void testProducedCar() {
	if (stack[CarType_Q] == SEDAN && stack[BreakSystem_Q] == CONTINENTAL) {
		printf("자동차 테스트 결과 : FAIL\n");
		printf("Sedan은 Continental 제동장치를 쓸 수 없습니다\n");
	}
	else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA) {
		printf("자동차 테스트 결과 : FAIL\n");
		printf("SUV는 도요타 엔진을 쓸 수 없습니다.\n");
	}
	else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA) {
		printf("자동차 테스트 결과 : FAIL\n");
		printf("Truck은 WIA 엔진을 쓸 수 없습니다.\n");
	}
	else if (stack[CarType_Q] == TRUCK && stack[BreakSystem_Q] == MANDO) {
		printf("자동차 테스트 결과 : FAIL\n");
		printf("Truck은 MANDO 제동장치를 쓸 수 없습니다.\n");
	}
	else if (stack[BreakSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S) {
		printf("자동차 테스트 결과 : FAIL\n");
		printf("제동장치에 Bosch 제품을 썼다면, 조향장치도 Bosch 제품을 써야합니다.\n");
	}
	else if (stack[BreakSystem_Q] != BOSCH_B && stack[SteeringSystem_Q] == BOSCH_S) {
		printf("자동차 테스트 결과 : FAIL\n");
		printf("조향장치에 Bosch 제품을 썼다면, 제동장치도 Bosch 제품을 써야합니다.\n");
	}
	else {
		printf("자동차 테스트 결과 : PASS\n");
	}
	
}
