#ifndef CAR_H
#define CAR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>

#define CLEAR_SCREEN "\033[H\033[2J"

extern int stack[10];

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

class Car {
private:
    // ��ǰ ���� ���� ����
    
    // �̸��� �� �����ϰ� ����
    std::map<int, std::string> carTypeNames = {
        {1, "����"},
        {2, "SUV"},
        {3, "TRUCK"}
    };
    std::map<int, std::string> engineTypeNames = {
        {1, "GM"},
        {2, "TOYOTA"},
        {3, "WIA"},
        {4, "���峭����"}
    };
    std::map<int, std::string> breakSystemNames = {
        {1, "MANDO"},
        {2, "CONTINENTAL"},
        {3, "BOSCH_B"}
    };
    std::map<int, std::string> steeringSystemNames = {
        {1, "BOSCH_S"},
        {2, "MOBIS"}
    };

public:

    // ���� Ÿ�� ����
    void selectCarType(int answer);

    // ���� ����
    void selectEngine(int answer);

    // ���� ��ġ ����
    void selectBreakSystem(int answer);

    // ���� ��ġ ����
    void selectSteeringSystem(int answer);

    // �ڵ��� ����
    void runProducedCar();

    // �ڵ��� �׽�Ʈ
    void testProducedCar();

    // ���� ������
    int getCarType() const;
    int getEngineType() const;
    int getBreakSystemType() const;
    int getSteeringSystemType() const;

    // �̸� ������
    std::string getCarTypeName(int id) const;
    std::string getEngineName(int id) const;
    std::string getBreakSystemName(int id) const;
    std::string getSteeringSystemName(int id) const;

    std::map<int, std::string> getCarTypeNames() const;
    std::map<int, std::string> getEngineTypeNames() const;
    std::map<int, std::string> getBreakSystemNames() const;
    std::map<int, std::string> getSteeringSystemNames() const;
};

void delay(int ms);

#endif // CAR_H