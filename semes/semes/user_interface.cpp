#include "user_interface.h"

UserInterface::UserInterface(Car& carRef)
    : car(carRef), currentStep(CarType_Q), isRunning(true) {
}

void UserInterface::run() {
    while (isRunning) {
        // ���� �ܰ� ȭ�� ���
        printCurrentStep();

        printf("===============================\n");
        printf("INPUT > ");

        // ����� �Է� ó��
        processInput();
    }
}

bool UserInterface::shouldExit() const {
    return !isRunning;
}

void UserInterface::printCurrentStep() {
    switch (currentStep) {
    case CarType_Q:
        printCarType_Q();
        break;
    case Engine_Q:
        printEngine_Q();
        break;
    case BreakSystem_Q:
        printBreakSystem_Q();
        break;
    case SteeringSystem_Q:
        printSteeringSystem_Q();
        break;
    case Run_Test:
        printRun_Test();
        break;
    default:
        printf("����: �� �� ���� �ܰ��Դϴ�.\n");
        break;
    }
}

void UserInterface::processInput() {
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    // ���� ���๮�� ����
    strtok(inputBuffer, "\r");
    strtok(inputBuffer, "\n");

    // ���� ��� Ȯ��
    if (!strcmp(inputBuffer, "exit")) {
        printf("���̹���\n");
        isRunning = false;
        return;
    }

    // �Է� ����
    int answer = validateAnswer(inputBuffer, currentStep);
    if (answer == -1) {
        return;
    }

    // �ڷΰ��� ó��
    if (answer == 0) {
        if (currentStep == Run_Test) {
            currentStep = CarType_Q;
        }
        else if (currentStep >= 1) {
            currentStep--;
        }
        return;
    }

    // �������� �亯 ó��
    processAnswer(answer);
}

int UserInterface::validateAnswer(const char* input, int step) {
    // ���ڷ� �� ������� Ȯ��
    char* checkNumber;
    int answer = strtol(input, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0') {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return -1;
    }

    // �ܰ躰 ��� ���� ����
    bool isValid = true;

    switch (step) {
    case CarType_Q:
        if (!(answer >= 1 && answer <= 3)) {
            printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
            isValid = false;
        }
        break;
    case Engine_Q:
        if (!(answer >= 0 && answer <= 4)) {
            printf("ERROR :: ������ 0 ~ 4 ������ ���� ����\n");
            isValid = false;
        }
        break;
    case BreakSystem_Q:
        if (!(answer >= 0 && answer <= 3)) {
            printf("ERROR :: ������ġ�� 0 ~ 3 ������ ���� ����\n");
            isValid = false;
        }
        break;
    case SteeringSystem_Q:
        if (!(answer >= 0 && answer <= 2)) {
            printf("ERROR :: ������ġ�� 0 ~ 2 ������ ���� ����\n");
            isValid = false;
        }
        break;
    case Run_Test:
        if (!(answer >= 0 && answer <= 2)) {
            printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
            isValid = false;
        }
        break;
    }

    if (!isValid) {
        delay(800);
        return -1;
    }

    return answer;
}

void UserInterface::processAnswer(int answer) {
    switch (currentStep) {
    case CarType_Q:
        car.selectCarType(answer);
        delay(800);
        currentStep = Engine_Q;
        break;
    case Engine_Q:
        car.selectEngine(answer);
        delay(800);
        currentStep = BreakSystem_Q;
        break;
    case BreakSystem_Q:
        car.selectBreakSystem(answer);
        delay(800);
        currentStep = SteeringSystem_Q;
        break;
    case SteeringSystem_Q:
        car.selectSteeringSystem(answer);
        delay(800);
        currentStep = Run_Test;
        break;
    case Run_Test:
        if (answer == 1) {
            car.runProducedCar();
        }
        else if (answer == 2) {
            car.testProducedCar();
        }
        delay(800);
        break;
    }
}

void UserInterface::printCarType_Q() {
    printf(CLEAR_SCREEN);
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    for (auto c : car.getCarTypeNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printEngine_Q() {
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    for (auto c : car.getEngineTypeNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printBreakSystem_Q() {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    for (auto c : car.getBreakSystemNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printSteeringSystem_Q() {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    for (auto c : car.getSteeringSystemNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printRun_Test() {
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

