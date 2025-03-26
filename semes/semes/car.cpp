#include "car.h"

int stack[10];

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

void Car::selectCarType(int answer) {
    stack[CarType_Q] = answer;
    printf("차량 타입으로 %s을 선택하셨습니다.\n", carTypeNames[answer].c_str());
}

void Car::selectEngine(int answer) {
    stack[Engine_Q] = answer;
    printf("엔진으로 %s을 선택하셨습니다.\n", engineTypeNames[answer].c_str());
}

void Car::selectBreakSystem(int answer) {
    stack[BreakSystem_Q] = answer;
    printf("제동장치로 %s을 선택하셨습니다.\n", breakSystemNames[answer].c_str());
}

void Car::selectSteeringSystem(int answer) {
    stack[SteeringSystem_Q] = answer;
    printf("조향장치로 %s을 선택하셨습니다.\n", steeringSystemNames[answer].c_str());
}

void Car::runProducedCar() {
    if (stack[Engine_Q] == 4) {
        printf("엔진이 고장났습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
    }
    else {
        printf("자동차가 동작됩니다.\n");
    }
}

void Car::testProducedCar() {
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

std::map<int, std::string> Car::getCarTypeNames() const {
    return carTypeNames;
}

std::map<int, std::string> Car::getEngineTypeNames() const {
    return engineTypeNames;
}

std::map<int, std::string> Car::getBreakSystemNames() const {
    return breakSystemNames;
}

std::map<int, std::string> Car::getSteeringSystemNames() const {
    return steeringSystemNames;
}