#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#define _CRT_SECURE_NO_WARNINGS
#include "car.h"

class UserInterface {
private:
    Car& car;
    int currentStep;
    char inputBuffer[100];
    bool isRunning;

    

    // 화면 출력 메소드
    void printCarType_Q();
    void printEngine_Q();
    void printBreakSystem_Q();
    void printSteeringSystem_Q();
    void printRun_Test();

    // 현재 단계 화면 출력
    void printCurrentStep();

    // 입력 처리 메소드
    void processInput();

    // 입력 검증 메소드
    int validateAnswer(const char* input, int step);

    // 단계별 처리 메소드
    void processAnswer(int answer);

public:
    // 생성자
    UserInterface(Car& carRef);

    // 인터페이스 실행
    void run();

    // 종료 확인
    bool shouldExit() const;
};

#endif // USER_INTERFACE_H