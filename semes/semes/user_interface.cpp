#include "user_interface.h"

UserInterface::UserInterface(Car& carRef)
    : car(carRef), currentStep(CarType_Q), isRunning(true) {
}

void UserInterface::run() {
    while (isRunning) {
        // 현재 단계 화면 출력
        printCurrentStep();

        printf("===============================\n");
        printf("INPUT > ");

        // 사용자 입력 처리
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
        printf("오류: 알 수 없는 단계입니다.\n");
        break;
    }
}

void UserInterface::processInput() {
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    // 엔터 개행문자 제거
    strtok(inputBuffer, "\r");
    strtok(inputBuffer, "\n");

    // 종료 명령 확인
    if (!strcmp(inputBuffer, "exit")) {
        printf("바이바이\n");
        isRunning = false;
        return;
    }

    // 입력 검증
    int answer = validateAnswer(inputBuffer, currentStep);
    if (answer == -1) {
        return;
    }

    // 뒤로가기 처리
    if (answer == 0) {
        if (currentStep == Run_Test) {
            currentStep = CarType_Q;
        }
        else if (currentStep >= 1) {
            currentStep--;
        }
        return;
    }

    // 정상적인 답변 처리
    processAnswer(answer);
}

int UserInterface::validateAnswer(const char* input, int step) {
    // 숫자로 된 대답인지 확인
    char* checkNumber;
    int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0') {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return -1;
    }

    // 단계별 허용 범위 검증
    bool isValid = true;

    switch (step) {
    case CarType_Q:
        if (!(answer >= 1 && answer <= 3)) {
            printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
            isValid = false;
        }
        break;
    case Engine_Q:
        if (!(answer >= 0 && answer <= 4)) {
            printf("ERROR :: 엔진은 0 ~ 4 범위만 선택 가능\n");
            isValid = false;
        }
        break;
    case BreakSystem_Q:
        if (!(answer >= 0 && answer <= 3)) {
            printf("ERROR :: 제동장치는 0 ~ 3 범위만 선택 가능\n");
            isValid = false;
        }
        break;
    case SteeringSystem_Q:
        if (!(answer >= 0 && answer <= 2)) {
            printf("ERROR :: 조향장치는 0 ~ 2 범위만 선택 가능\n");
            isValid = false;
        }
        break;
    case Run_Test:
        if (!(answer >= 0 && answer <= 2)) {
            printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
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
    printf("어떤 차량 타입을 선택할까요?\n");
    for (auto c : car.getCarTypeNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printEngine_Q() {
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    for (auto c : car.getEngineTypeNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printBreakSystem_Q() {
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    for (auto c : car.getBreakSystemNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printSteeringSystem_Q() {
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    for (auto c : car.getSteeringSystemNames()) {
        std::cout << c.first << ". " << c.second << "\n";
    }
}

void UserInterface::printRun_Test() {
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

