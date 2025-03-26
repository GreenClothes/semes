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
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", carTypeNames[answer].c_str());
}

void Car::selectEngine(int answer) {
    stack[Engine_Q] = answer;
    printf("�������� %s�� �����ϼ̽��ϴ�.\n", engineTypeNames[answer].c_str());
}

void Car::selectBreakSystem(int answer) {
    stack[BreakSystem_Q] = answer;
    printf("������ġ�� %s�� �����ϼ̽��ϴ�.\n", breakSystemNames[answer].c_str());
}

void Car::selectSteeringSystem(int answer) {
    stack[SteeringSystem_Q] = answer;
    printf("������ġ�� %s�� �����ϼ̽��ϴ�.\n", steeringSystemNames[answer].c_str());
}

void Car::runProducedCar() {
    if (stack[Engine_Q] == 4) {
        printf("������ ���峵���ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
    }
    else {
        printf("�ڵ����� ���۵˴ϴ�.\n");
    }
}

void Car::testProducedCar() {
    if (stack[CarType_Q] == SEDAN && stack[BreakSystem_Q] == CONTINENTAL) {
        printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan�� Continental ������ġ�� �� �� �����ϴ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA) {
        printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
        printf("SUV�� ����Ÿ ������ �� �� �����ϴ�.\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA) {
        printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
        printf("Truck�� WIA ������ �� �� �����ϴ�.\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[BreakSystem_Q] == MANDO) {
        printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
        printf("Truck�� MANDO ������ġ�� �� �� �����ϴ�.\n");
    }
    else if (stack[BreakSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S) {
        printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
        printf("������ġ�� Bosch ��ǰ�� ��ٸ�, ������ġ�� Bosch ��ǰ�� ����մϴ�.\n");
    }
    else if (stack[BreakSystem_Q] != BOSCH_B && stack[SteeringSystem_Q] == BOSCH_S) {
        printf("�ڵ��� �׽�Ʈ ��� : FAIL\n");
        printf("������ġ�� Bosch ��ǰ�� ��ٸ�, ������ġ�� Bosch ��ǰ�� ����մϴ�.\n");
    }
    else {
        printf("�ڵ��� �׽�Ʈ ��� : PASS\n");
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