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

    // �ڵ��� Ÿ�԰� "ȣȯ���� �ʴ�" ����, ����, ������ �߰��Ѵ�.
    void add_incompatible_part(CarType car, T part) {
        // car�� enum CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // part�� enum T�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(part) <= 0) {
            std::cout << "It's an invalid part.\n";
            return;
        }
        incompatible_parts[car].insert(part);
    }

    // Ư�� ��ġ�� �����ϰ� "ȣȯ�Ǵ�" ��ġ�� �߰��Ѵ�.
    void add_compatible_part(T part1, std::string partType, Part part2) {
        // part1�� enum T�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(part1) <= 0) {
            std::cout << "It's an invalid part.\n";
            return;
        }
        // partType�� ��ǰ ��Ͽ� �����ϴ��� Ȯ���Ѵ�.
        if (partList.find(partType) == partList.end()) {
            std::cout << "It's an invalid partType.\n";
            return;
        }
        compatible_parts[part1].insert({ partType, part2 });
    }

    // �ڵ��� Ÿ�԰� "ȣȯ���� �ʴ�" ����, ����, ������ �����Ѵ�.
    void remove_part(CarType car, T part) {
        // car�� enum CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // part�� enum T�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(part) <= 0) {
            std::cout << "It's an invalid part.\n";
            return;
        }
        // car�� incompatible_parts�� �����ϴ��� Ȯ���Ѵ�.
        if (incompatible_parts.find(car) == incompatible_parts.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // part�� incompatible_parts[car]�� �����ϴ��� Ȯ���Ѵ�.
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

    // ȣȯ���� Ȯ���Ѵ�. -> ȣȯ�Ǹ� true�� ��ȯ�Ѵ�.
    bool is_compatible(T part1, Part part2) {
        // ���� ��ġ�� ���� �� ������� �ʴ´�.
        if (std::holds_alternative<T>(part2)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // part1�� enum T�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(part1) <= 0) {
            std::cout << "It's an invalid part.\n";
            return false;
        }
        // ��ǰ�� �ڵ����� ȣȯ���� �Ǵ��Ѵ�.
        if (std::holds_alternative<CarType>(part2)) {
            CarType car = std::get<CarType>(part2);
            // car�� enum CarType�� �����ϴ��� Ȯ���Ѵ�.
            if (static_cast<int>(car) <= 0) {
                std::cout << "It's an invalid car type.\n";
                return false;
            }
            // car�� incompatible_parts�� �����ϴ��� Ȯ���Ѵ�.
            if (incompatible_parts.find(car) == incompatible_parts.end()) {
                return true;
            }
            else {
                // part1�� incompatible_parts[car]�� �����ϴ��� Ȯ���Ѵ�.
                if (incompatible_parts[car].find(part1) == incompatible_parts[car].end()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        // �ٸ� ��ġ�� ȣȯ���� �Ǵ��Ѵ�.(Ÿ �� ��ǰ ȣȯ x)
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

    // ��ġ ��� ���
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

// ������ ȣȯ�� ����
class EngineSystemManagement : public PartSystem<Engine> {
public:
    EngineSystemManagement() {
        partList.insert("engine");
    }
};

// ������ġ�� ȣȯ�� ����
class BreakSystemManagement : public PartSystem<BreakSystem> {
public:
    BreakSystemManagement() {
        partList.insert("break");
    }
};

// ������ġ�� ȣȯ�� ����
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

    // ȣȯ���� �ʴ� ��ǰ�� �߰��ϴ� ���
    void add_incompatible_part(const std::string& partType, CarType car, Part part);

    // ȣȯ�Ǵ� ��ǰ�� �߰��ϴ� ���
    void add_compatible_part(const std::string& partType, Part part1, const std::string& addPartType, Part part2);

    // ��ǰ�� �����ϴ� ���
    void remove_part(const std::string& partType, CarType car, Part part);

    // ��� ��ǰ �� ȣȯ�� Ȯ��
    bool is_compatible_all(std::unordered_map<std::string, Part>& parts);

    // ��ǰ �ý��� ���� ���
    void show_systems(const std::string& partType);

    // ��� ��ǰ �ý��� ���� ���
    void show_systems_all();

private:
    PartSystem<Engine>* engineSystemManagement;
    PartSystem<BreakSystem>* breakSystemManagement;
    PartSystem<SteeringSystem>* steeringSystemManagement;
};