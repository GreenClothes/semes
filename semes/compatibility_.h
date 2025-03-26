#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include "carInfo.h"

using Part = std::variant<CarType, Engine, BreakSystem, SteeringSystem>;
extern std::unordered_set<std::string> partList;

template <typename T>
class PartSystem {
public:
    virtual ~PartSystem() = default;

    // 자동차 타입과 "호환되지 않는" 엔진, 제동, 조향을 추가한다.
    void add_incompatible_part(CarType car, T part) {
        // car가 enum CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // part가 enum T에 존재하는지 확인한다.
        if (static_cast<int>(part) <= 0) {
            std::cout << "It's an invalid part.\n";
            return;
        }
        incompatible_parts[car].insert(part);
    }

    // 특정 장치와 유일하게 "호환되는" 장치를 추가한다.
    void add_compatible_part(T part1, std::string partType, Part part2) {
        // part1이 enum T에 존재하는지 확인한다.
        if (static_cast<int>(part1) <= 0) {
            std::cout << "It's an invalid part.\n";
            return;
        }
        // partType이 부품 목록에 존재하는지 확인한다.
        if (partList.find(partType) == partList.end()) {
            std::cout << "It's an invalid partType.\n";
            return;
        }
        compatible_parts[part1].insert({ partType, part2 });
    }

    // 자동차 타입과 "호환되지 않는" 엔진, 제동, 조향을 제거한다.
    void remove_part(CarType car, T part) {
        // car가 enum CarType에 존재하는지 확인한다.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // part가 enum T에 존재하는지 확인한다.
        if (static_cast<int>(part) <= 0) {
            std::cout << "It's an invalid part.\n";
            return;
        }
        // car가 incompatible_parts에 존재하는지 확인한다.
        if (incompatible_parts.find(car) == incompatible_parts.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // part가 incompatible_parts[car]에 존재하는지 확인한다.
            if (incompatible_parts[car].find(part) == incompatible_parts[car].end()) {
                std::cout << "Part " << static_cast<int>(part) << " does not exist.\n";
                return;
            }
            incompatible_parts[car].erase(part);
            if (incompatible_parts[car].empty()) {
                incompatible_parts.erase(car);
            }
        }
    }

    // 호환성을 확인한다. -> 호환되면 true를 반환한다.
    bool is_compatible(T part1, Part part2) {
        // 같은 장치를 여러 개 사용하지 않는다.
        if (std::holds_alternative<T>(part2)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // part1이 enum T에 존재하는지 확인한다.
        if (static_cast<int>(part1) <= 0) {
            std::cout << "It's an invalid part.\n";
            return false;
        }
        // 부품과 자동차의 호환성을 판단한다.
        if (std::holds_alternative<CarType>(part2)) {
            CarType car = std::get<CarType>(part2);
            // car가 enum CarType에 존재하는지 확인한다.
            if (static_cast<int>(car) <= 0) {
                std::cout << "It's an invalid car type.\n";
                return false;
            }
            // car가 incompatible_parts에 존재하는지 확인한다.
            if (incompatible_parts.find(car) == incompatible_parts.end()) {
                return true;
            }
            else {
                // part1이 incompatible_parts[car]에 존재하는지 확인한다.
                if (incompatible_parts[car].find(part1) == incompatible_parts[car].end()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        // 다른 장치와 호환성을 판단한다.(타 사 제품 호환 x)
        else {
            std::string partType = find_type(part2);
            if (compatible_parts.find(part1) == compatible_parts.end()) {
                return true;
            }
            if (compatible_parts[part1].find(partType) == compatible_parts[part1].end()) {
                return true;
            }
            if (compatible_parts[part1][partType] == part2) {
                return true;
            }
        }
        return false;
    }

    // 장치 목록 출력
    void show_parts() const {
        std::cout << "[Incompatible]\n";
        for (const auto& [car, parts] : incompatible_parts) {
            std::cout << "Car Type " << static_cast<int>(car) << " has incompatible parts: ";
            for (const auto& p : parts) {
                std::cout << static_cast<int>(p) << " ";
            }
            std::cout << "\n";
        }
        std::cout << "[Compatible]\n";
        for (const auto& [part, parts] : compatible_parts) {
            std::cout << "Part " << static_cast<int>(part) << " has compatible parts: ";
            for (const auto& [type, p] : parts) {
                std::cout << type << " ";
            }
            std::cout << "\n";
        }
    }

protected:
    std::string find_type(Part part) const {
        if (std::holds_alternative<CarType>(part)) {
            return "car";
        }
        if (std::holds_alternative<Engine>(part)) {
            return "engine";
        }
        if (std::holds_alternative<BreakSystem>(part)) {
            return "break";
        }
        if (std::holds_alternative<SteeringSystem>(part)) {
            return "steering";
        }
        std::cout << "It's an invalid type.\n";
        return "";
    }

    std::unordered_map<CarType, std::unordered_set<T>> incompatible_parts;
    std::unordered_map<T, std::unordered_map<std::string, Part>> compatible_parts;
};

// 엔진의 호환성 관리
class EngineSystemManagement : public PartSystem<Engine> {
public:
    EngineSystemManagement() {
        partList.insert("engine");
    }
};

// 제동장치의 호환성 관리
class BreakSystemManagement : public PartSystem<BreakSystem> {
public:
    BreakSystemManagement() {
        partList.insert("break");
    }
};

// 조향장치의 호환성 관리
class SteeringSystemManagement : public PartSystem<SteeringSystem> {
public:
    SteeringSystemManagement() {
        partList.insert("steering");
    }
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

    // 호환되지 않는 부품을 추가하는 기능
    void add_incompatible_part(const std::string& partType, CarType car, Part part);

    // 호환되는 부품을 추가하는 기능
    void add_compatible_part(const std::string& partType, Part part1, const std::string& addPartType, Part part2);

    // 부품을 제거하는 기능
    void remove_part(const std::string& partType, CarType car, Part part);

    // 모든 부품 간 호환성 확인
    bool is_compatible_all(std::unordered_map<std::string, Part>& parts);

    // 부품 시스템 정보 출력
    void show_systems(const std::string& partType);

    // 모든 부품 시스템 정보 출력
    void show_systems_all();

private:
    PartSystem<Engine>* engineSystemManagement;
    PartSystem<BreakSystem>* breakSystemManagement;
    PartSystem<SteeringSystem>* steeringSystemManagement;
};