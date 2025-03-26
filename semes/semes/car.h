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
    // 부품 선택 상태 저장
    
    // 이름을 더 적절하게 변경
    std::map<int, std::string> carTypeNames = {
        {1, "세단"},
        {2, "SUV"},
        {3, "TRUCK"}
    };
    std::map<int, std::string> engineTypeNames = {
        {1, "GM"},
        {2, "TOYOTA"},
        {3, "WIA"},
        {4, "고장난엔진"}
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

    // 차량 타입 선택
    void selectCarType(int answer);

    // 엔진 선택
    void selectEngine(int answer);

    // 제동 장치 선택
    void selectBreakSystem(int answer);

    // 조향 장치 선택
    void selectSteeringSystem(int answer);

    // 자동차 주행
    void runProducedCar();

    // 자동차 테스트
    void testProducedCar();

    // 상태 접근자
    int getCarType() const;
    int getEngineType() const;
    int getBreakSystemType() const;
    int getSteeringSystemType() const;

    // 이름 접근자
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