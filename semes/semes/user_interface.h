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

    

    // ȭ�� ��� �޼ҵ�
    void printCarType_Q();
    void printEngine_Q();
    void printBreakSystem_Q();
    void printSteeringSystem_Q();
    void printRun_Test();

    // ���� �ܰ� ȭ�� ���
    void printCurrentStep();

    // �Է� ó�� �޼ҵ�
    void processInput();

    // �Է� ���� �޼ҵ�
    int validateAnswer(const char* input, int step);

    // �ܰ躰 ó�� �޼ҵ�
    void processAnswer(int answer);

public:
    // ������
    UserInterface(Car& carRef);

    // �������̽� ����
    void run();

    // ���� Ȯ��
    bool shouldExit() const;
};

#endif // USER_INTERFACE_H