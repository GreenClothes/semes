#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include "carInfo.h"

using Part = std::variant<CarType, Engine, BreakSystem, SteeringSystem>;

template <typename T>
class PartSystem {
public:

    virtual ~PartSystem() = default;

    // 자동차 타입과 "호환되지 않는" 엔진, 제동, 조향을 추가한다.
    virtual void add_incompatible_part(CarType car, T part) = 0;

    // 특정 장치와 유일하게 "호환되는" 장치를 추가한다.
    //virtual void add_compatible_part(T part, std::string partType, int partNum) = 0;

    // 자동차 타입과 "호환되지 않는" 엔진, 제동, 조향을 제거한다.
    virtual void remove_part(CarType car, T part) = 0;

    // 호환성을 확인한다. -> 호환되면 true를 반환한다.
    virtual bool is_compatible(T part1, Part part2) = 0;

    // 장치 목록 출력
    virtual void show_parts() const = 0;

protected:
    //std::unordered_set<std::string> partList;
};
// 엔진의 호환성 관리
class EngineSystemManagement : public PartSystem<Engine> {
public:
    //EngineSystemManagement() {
    //    partList.insert("engine");
    //}

    void add_incompatible_part(CarType car, Engine engine) override {
        // car가 enum class CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // engine이 enum class Engine에 존재하는지 확인한다.
        if (static_cast<int>(engine) <= 0) {
            std::cout << "It's an invalid engine.\n";
            return;
        }
        engines[car].insert(engine);
        std::cout << "Engine " << static_cast<int>(engine) << " added.\n";
    }

    //void add_compatible_part(Engine engine, std::string partType, int partNum) override {
    //    // engine이 enum class Engine에 존재하는지 확인한다.
    //    if (static_cast<int>(engine) <= 0) {
    //        std::cout << "It's an invalid engine.\n";
    //        return;
    //    }
    //    // partType이 부품 목록에 존재하는지 확인한다.
    //    if (partList.find(partType) == partList.end()) {
    //        std::cout << "It's an invalid partType.\n";
    //        return;
    //    }
    //    // partNum이 양수인지 확인한다.(partNum은 1부터 시작한다.)
    //    if (partNum <= 0) {
    //        std::cout << "It's an invalid partNum.\n";
    //        return;
    //    }
    //    engineOnly[engine].insert({ partType, partNum });
    //    std::cout << partType << " " << partNum << " added to Engine "
    //        << static_cast<int>(engine) << "\n";
    //}

    void remove_part(CarType car, Engine engine) override {
        // car가 enum class CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // engine이 enum class Engine에 존재하는지 확인한다.
        if (static_cast<int>(engine) <= 0) {
            std::cout << "It's an invalid engine.\n";
            return;
        }
        // car가 engines에 존재하는지 확인한다.
        if (engines.find(car) == engines.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // engine이 존재하는지 확인한다.
            if (engines[car].find(engine) == engines[car].end()) {
                std::cout << "Engine " << static_cast<int>(engine) << " does not exist.\n";
                return;
            }
            engines[car].erase(engine);
            if (engines[car].empty()) {
                engines.erase(car);
            }
            std::cout << "Engine " << static_cast<int>(engine) << " removed.\n";
        }
    }

    // 엔진과의 호환성을 판단한다.
    bool is_compatible(Engine engine, Part part) override {
        // 같은 장치를 여러 개 사용하지 않는다.
        if (std::holds_alternative<Engine>(part)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // 엔진과 자동차의 호환성을 판단한다.
        if (std::holds_alternative<CarType>(part)) {
            CarType car = std::get<CarType>(part);
            if (engines[car].find(engine) == engines[car].end()) {
                return true;
            }
            else {
                return false;
            }
        }
        // 엔진과 다른 장치의 호환성을 판단한다.(타 사 제품 호환 x)
        else {
            //std::cout << "The part is not compatible with other companies' products.\n";
        }
        return false;
    }

    void show_parts() const override {
        for (const auto& [car, engine] : engines) {
            std::cout << "Car Type " << static_cast<int>(car) << " has incompatible engines: ";
            for (const auto& e : engine) {
                std::cout << static_cast<int>(e) << " ";
            }
            std::cout << "\n";
        }
    }

private:
    // 특정 자동차와 "호환되지 않는" 엔진 정보
    std::unordered_map<CarType, std::unordered_set<Engine>> engines;

    // 유일하게 "호환되는" 장치 정보 <엔진 종류, <장치 종류, 부품 번호>>
    //std::unordered_map<Engine, std::unordered_set<std::pair<std::string, int>>> engineOnly;
};
// 제동장치의 호환성 관리
class BreakSystemManagement : public PartSystem<BreakSystem> {
public:
    void add_incompatible_part(CarType car, BreakSystem breaksystem) override {
        // car가 enum class CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // breaksystem이 enum class BreakSystem에 존재하는지 확인한다.
        if (static_cast<int>(breaksystem) <= 0) {
            std::cout << "It's an invalid breaksystem.\n";
            return;
        }
        breaksystems[car].insert(breaksystem);
        std::cout << "BreakSystem " << static_cast<int>(breaksystem) << " added.\n";
    }

    void remove_part(CarType car, BreakSystem breaksystem) override {
        // car가 enum class CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // breaksystem이 enum class BreakSystem에 존재하는지 확인한다.
        if (static_cast<int>(breaksystem) <= 0) {
            std::cout << "It's an invalid breaksystem.\n";
            return;
        }
        // car가 breaksystems에 존재하는지 확인한다.
        if (breaksystems.find(car) == breaksystems.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // breaksystem이 존재하는지 확인한다.
            if (breaksystems[car].find(breaksystem) == breaksystems[car].end()) {
                std::cout << "BreakSystem " << static_cast<int>(breaksystem) << " does not exist.\n";
                return;
            }
            breaksystems[car].erase(breaksystem);
            if (breaksystems[car].empty()) {
                breaksystems.erase(car);
            }
            std::cout << "BreakSystem " << static_cast<int>(breaksystem) << " removed.\n";
        }
    }

    // 제동장치와의 호환성을 판단한다.
    bool is_compatible(BreakSystem breaksystem, Part part) override {
        // 같은 장치를 여러 개 사용하지 않는다.
        if (std::holds_alternative<BreakSystem>(part)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // 제동장치와 자동차의 호환성을 판단한다.
        if (std::holds_alternative<CarType>(part)) {
            CarType car = std::get<CarType>(part);
            if (breaksystems[car].find(breaksystem) == breaksystems[car].end()) {
                return true;
            }
            else {
                return false;
            }
        }
        // 제동장치와 다른 장치의 호환성을 판단한다.(타 사 제품 호환 x)
        else {
            if (breaksystem == BreakSystem::BOSCH) {
                if (std::holds_alternative<SteeringSystem>(part)) {
                    SteeringSystem steeringsystem = std::get<SteeringSystem>(part);
                    if (steeringsystem == SteeringSystem::BOSCH) {
                        return true;
                    }
                    std::cout << "제동장치에 Bosch 제품을 썼다면, 조향장치도 Bosch 제품을 써야합니다.\n";
                    return false;
                }
                else {
                    return true;
                }
            }
            return true;
            //std::cout << "The part is not compatible with other companies' products.\n";
        }
        return false;
    }

    void show_parts() const override {
        for (const auto& [car, breaksystem] : breaksystems) {
            std::cout << "Car Type " << static_cast<int>(car) << " has incompatible breaksystems: ";
            for (const auto& b : breaksystem) {
                std::cout << static_cast<int>(b) << " ";
            }
            std::cout << "\n";
        }
    }

private:
    // 특정 자동차와 "호환되지 않는" 제동장치 정보
    std::unordered_map<CarType, std::unordered_set<BreakSystem>> breaksystems;

    // 유일하게 "호환되는" 장치 정보 <제동장치 종류, <장치 종류, 부품 이름>>
    //std::unordered_map<Engine, std::unordered_set<std::pair<std::string, std::string>>> engine_only;
};
// 조향장치의 호환성 관리
class SteeringSystemManagement : public PartSystem<SteeringSystem> {
public:
    void add_incompatible_part(CarType car, SteeringSystem steeringsystem) override {
        // car가 enum class CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // steeringsystem이 enum class SteeringSystem에 존재하는지 확인한다.
        if (static_cast<int>(steeringsystem) <= 0) {
            std::cout << "It's an invalid steeringsystem.\n";
            return;
        }
        steeringsystems[car].insert(steeringsystem);
        std::cout << "SteeringSystem " << static_cast<int>(steeringsystem) << " added.\n";
    }

    void remove_part(CarType car, SteeringSystem steeringsystem) override {
        // car가 enum class CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // steeringsystem이 enum class SteeringSystem에 존재하는지 확인한다.
        if (static_cast<int>(steeringsystem) <= 0) {
            std::cout << "It's an invalid steeringsystem.\n";
            return;
        }
        // car가 steeringsystems에 존재하는지 확인한다.
        if (steeringsystems.find(car) == steeringsystems.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // steeringsystem이 존재하는지 확인한다.
            if (steeringsystems[car].find(steeringsystem) == steeringsystems[car].end()) {
                std::cout << "SteeringSystem " << static_cast<int>(steeringsystem) << " does not exist.\n";
                return;
            }
            steeringsystems[car].erase(steeringsystem);
            if (steeringsystems[car].empty()) {
                steeringsystems.erase(car);
            }
            std::cout << "SteeringSystem " << static_cast<int>(steeringsystem) << " removed.\n";
        }
    }

    // 조향장치와의 호환성을 판단한다.
    bool is_compatible(SteeringSystem steeringsystem, Part part) override {
        // 같은 장치를 여러 개 사용하지 않는다.
        if (std::holds_alternative<SteeringSystem>(part)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // 조향장치와 자동차의 호환성을 판단한다.
        if (std::holds_alternative<CarType>(part)) {
            CarType car = std::get<CarType>(part);
            if (steeringsystems[car].find(steeringsystem) == steeringsystems[car].end()) {
                return true;
            }
            else {
                return false;
            }
        }
        // 조향장치와 다른 장치의 호환성을 판단한다.(타 사 제품 호환 x)
        else {
            if (steeringsystem == SteeringSystem::BOSCH) {
                if (std::holds_alternative<BreakSystem>(part)) {
                    BreakSystem breaksystem = std::get<BreakSystem>(part);
                    if (breaksystem == BreakSystem::BOSCH) {
                        return true;
                    }
                    std::cout << "조향장치에 Bosch 제품을 썼다면, 제동장치도 Bosch 제품을 써야합니다.\n";
                    return false;
                }
                else {
                    return true;
                }
            }
            return true;
            //std::cout << "The part is not compatible with other companies' products.\n";
        }
        return false;
    }

    void show_parts() const override {
        for (const auto& [car, steeringsystem] : steeringsystems) {
            std::cout << "Car Type " << static_cast<int>(car) << " has incompatible steeringsystems: ";
            for (const auto& s : steeringsystem) {
                std::cout << static_cast<int>(s) << " ";
            }
            std::cout << "\n";
        }
    }

private:
    // 특정 자동차와 "호환되지 않는" 조향장치 정보
    std::unordered_map<CarType, std::unordered_set<SteeringSystem>> steeringsystems;

    // 유일하게 "호환되는" 장치 정보 <조향장치 종류, <장치 종류, 부품 이름>>
    //std::unordered_map<Engine, std::unordered_set<std::pair<std::string, std::string>>> engine_only;
};

class Compatibility_ {
public:
    Compatibility_()
        : engineSystemManagement(new EngineSystemManagement()), breakSystemManagement(new BreakSystemManagement()), steeringSystemManagement(new SteeringSystemManagement()) {
    }

    ~Compatibility_() {
        delete engineSystemManagement;
        delete breakSystemManagement;
        delete steeringSystemManagement;
    }

    // 부품을 추가하는 기능
    void add_incompatible_part(const std::string& partType, CarType car, Part part) {
        if (partType == "engine") {
            if (std::holds_alternative<Engine>(part)) {
                engineSystemManagement->add_incompatible_part(car, std::get<Engine>(part));
            }
            else {
                std::cout << "It's an invalid input.\n";
            }
        }
        else if (partType == "break") {
            if (std::holds_alternative<BreakSystem>(part)) {
                breakSystemManagement->add_incompatible_part(car, std::get<BreakSystem>(part));
            }
            else {
                std::cout << "It's an invalid input.\n";
            }
        }
        else if (partType == "steering") {
            if (std::holds_alternative<SteeringSystem>(part)) {
                steeringSystemManagement->add_incompatible_part(car, std::get<SteeringSystem>(part));
            }
            else {
                std::cout << "It's an invalid input.\n";
            }
        }
        else {
            std::cout << "Invalid part type\n";
        }
    }

    // 부품을 제거하는 기능
    void remove_part(const std::string& partType, CarType car, Part part) {
        if (partType == "engine") {
            if (std::holds_alternative<Engine>(part)) {
                engineSystemManagement->remove_part(car, std::get<Engine>(part));
            }
            else {
                std::cout << "It's an invalid input.\n";
            }
        }
        else if (partType == "break") {
            if (std::holds_alternative<BreakSystem>(part)) {
                breakSystemManagement->remove_part(car, std::get<BreakSystem>(part));
            }
            else {
                std::cout << "It's an invalid input.\n";
            }
        }
        else if (partType == "steering") {
            if (std::holds_alternative<SteeringSystem>(part)) {
                steeringSystemManagement->remove_part(car, std::get<SteeringSystem>(part));
            }
            else {
                std::cout << "It's an invalid input.\n";
            }
        }
        else {
            std::cout << "Invalid part type\n";
        }
    }

    // 부품 간 호환성 확인
    //bool is_compatible(const std::string& partType, Part part1, Part part2) {
    //    if (partType == "engine") {
    //        return engineSystemManagement->is_compatible(std::get<Engine>(part1), part2);
    //    }
    //    else if (partType == "break") {
    //        return breakSystemManagement->is_compatible(std::get<BreakSystem>(part1), part2);
    //    }
    //    else if (partType == "steering") {
    //        return steeringSystemManagement->is_compatible(std::get<SteeringSystem>(part1), part2);
    //    }
    //    else {
    //        std::cout << "Invalid part type\n";
    //    }
    //    return false;
    //}

    // 모든 부품 간 호환성 확인
    bool is_compatible_all(std::unordered_map<std::string, Part>& parts) {
        if (!engineSystemManagement->is_compatible(std::get<Engine>(parts["engine"]), std::get<CarType>(parts["car"]))) {
            return false;
        }
        if (!breakSystemManagement->is_compatible(std::get<BreakSystem>(parts["break"]), std::get<CarType>(parts["car"]))) {
            return false;
        }
        if (!steeringSystemManagement->is_compatible(std::get<SteeringSystem>(parts["steering"]), std::get<CarType>(parts["car"]))) {
            return false;
        }
        if (!breakSystemManagement->is_compatible(std::get<BreakSystem>(parts["break"]), std::get<SteeringSystem>(parts["steering"]))) {
            return false;
        }
        if (!steeringSystemManagement->is_compatible(std::get<SteeringSystem>(parts["steering"]), std::get<BreakSystem>(parts["break"]))) {
            return false;
        }
        return true;
    }

    // 부품 시스템 정보 출력
    void show_systems(const std::string& partType) {
        if (partType == "engine") {
            engineSystemManagement->show_parts();
        }
        else if (partType == "break") {
            breakSystemManagement->show_parts();
        }
        else if (partType == "steering") {
            steeringSystemManagement->show_parts();
        }
        else {
            std::cout << "Invalid part type\n";
        }
    }

    // 모든 부품 시스템 정보 출력
    void show_systems_all() {
        engineSystemManagement->show_parts();
        breakSystemManagement->show_parts();
        steeringSystemManagement->show_parts();
    }

private:
    PartSystem<Engine>* engineSystemManagement;
    PartSystem<BreakSystem>* breakSystemManagement;
    PartSystem<SteeringSystem>* steeringSystemManagement;
};