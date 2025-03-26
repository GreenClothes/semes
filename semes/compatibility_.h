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

    // �ڵ��� Ÿ�԰� "ȣȯ���� �ʴ�" ����, ����, ������ �߰��Ѵ�.
    virtual void add_incompatible_part(CarType car, T part) = 0;

    // Ư�� ��ġ�� �����ϰ� "ȣȯ�Ǵ�" ��ġ�� �߰��Ѵ�.
    //virtual void add_compatible_part(T part, std::string partType, int partNum) = 0;

    // �ڵ��� Ÿ�԰� "ȣȯ���� �ʴ�" ����, ����, ������ �����Ѵ�.
    virtual void remove_part(CarType car, T part) = 0;

    // ȣȯ���� Ȯ���Ѵ�. -> ȣȯ�Ǹ� true�� ��ȯ�Ѵ�.
    virtual bool is_compatible(T part1, Part part2) = 0;

    // ��ġ ��� ���
    virtual void show_parts() const = 0;

protected:
    //std::unordered_set<std::string> partList;
};
// ������ ȣȯ�� ����
class EngineSystemManagement : public PartSystem<Engine> {
public:
    //EngineSystemManagement() {
    //    partList.insert("engine");
    //}

    void add_incompatible_part(CarType car, Engine engine) override {
        // car�� enum class CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // engine�� enum class Engine�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(engine) <= 0) {
            std::cout << "It's an invalid engine.\n";
            return;
        }
        engines[car].insert(engine);
        std::cout << "Engine " << static_cast<int>(engine) << " added.\n";
    }

    //void add_compatible_part(Engine engine, std::string partType, int partNum) override {
    //    // engine�� enum class Engine�� �����ϴ��� Ȯ���Ѵ�.
    //    if (static_cast<int>(engine) <= 0) {
    //        std::cout << "It's an invalid engine.\n";
    //        return;
    //    }
    //    // partType�� ��ǰ ��Ͽ� �����ϴ��� Ȯ���Ѵ�.
    //    if (partList.find(partType) == partList.end()) {
    //        std::cout << "It's an invalid partType.\n";
    //        return;
    //    }
    //    // partNum�� ������� Ȯ���Ѵ�.(partNum�� 1���� �����Ѵ�.)
    //    if (partNum <= 0) {
    //        std::cout << "It's an invalid partNum.\n";
    //        return;
    //    }
    //    engineOnly[engine].insert({ partType, partNum });
    //    std::cout << partType << " " << partNum << " added to Engine "
    //        << static_cast<int>(engine) << "\n";
    //}

    void remove_part(CarType car, Engine engine) override {
        // car�� enum class CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // engine�� enum class Engine�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(engine) <= 0) {
            std::cout << "It's an invalid engine.\n";
            return;
        }
        // car�� engines�� �����ϴ��� Ȯ���Ѵ�.
        if (engines.find(car) == engines.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // engine�� �����ϴ��� Ȯ���Ѵ�.
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

    // �������� ȣȯ���� �Ǵ��Ѵ�.
    bool is_compatible(Engine engine, Part part) override {
        // ���� ��ġ�� ���� �� ������� �ʴ´�.
        if (std::holds_alternative<Engine>(part)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // ������ �ڵ����� ȣȯ���� �Ǵ��Ѵ�.
        if (std::holds_alternative<CarType>(part)) {
            CarType car = std::get<CarType>(part);
            if (engines[car].find(engine) == engines[car].end()) {
                return true;
            }
            else {
                return false;
            }
        }
        // ������ �ٸ� ��ġ�� ȣȯ���� �Ǵ��Ѵ�.(Ÿ �� ��ǰ ȣȯ x)
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
    // Ư�� �ڵ����� "ȣȯ���� �ʴ�" ���� ����
    std::unordered_map<CarType, std::unordered_set<Engine>> engines;

    // �����ϰ� "ȣȯ�Ǵ�" ��ġ ���� <���� ����, <��ġ ����, ��ǰ ��ȣ>>
    //std::unordered_map<Engine, std::unordered_set<std::pair<std::string, int>>> engineOnly;
};
// ������ġ�� ȣȯ�� ����
class BreakSystemManagement : public PartSystem<BreakSystem> {
public:
    void add_incompatible_part(CarType car, BreakSystem breaksystem) override {
        // car�� enum class CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // breaksystem�� enum class BreakSystem�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(breaksystem) <= 0) {
            std::cout << "It's an invalid breaksystem.\n";
            return;
        }
        breaksystems[car].insert(breaksystem);
        std::cout << "BreakSystem " << static_cast<int>(breaksystem) << " added.\n";
    }

    void remove_part(CarType car, BreakSystem breaksystem) override {
        // car�� enum class CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // breaksystem�� enum class BreakSystem�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(breaksystem) <= 0) {
            std::cout << "It's an invalid breaksystem.\n";
            return;
        }
        // car�� breaksystems�� �����ϴ��� Ȯ���Ѵ�.
        if (breaksystems.find(car) == breaksystems.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // breaksystem�� �����ϴ��� Ȯ���Ѵ�.
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

    // ������ġ���� ȣȯ���� �Ǵ��Ѵ�.
    bool is_compatible(BreakSystem breaksystem, Part part) override {
        // ���� ��ġ�� ���� �� ������� �ʴ´�.
        if (std::holds_alternative<BreakSystem>(part)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // ������ġ�� �ڵ����� ȣȯ���� �Ǵ��Ѵ�.
        if (std::holds_alternative<CarType>(part)) {
            CarType car = std::get<CarType>(part);
            if (breaksystems[car].find(breaksystem) == breaksystems[car].end()) {
                return true;
            }
            else {
                return false;
            }
        }
        // ������ġ�� �ٸ� ��ġ�� ȣȯ���� �Ǵ��Ѵ�.(Ÿ �� ��ǰ ȣȯ x)
        else {
            if (breaksystem == BreakSystem::BOSCH) {
                if (std::holds_alternative<SteeringSystem>(part)) {
                    SteeringSystem steeringsystem = std::get<SteeringSystem>(part);
                    if (steeringsystem == SteeringSystem::BOSCH) {
                        return true;
                    }
                    std::cout << "������ġ�� Bosch ��ǰ�� ��ٸ�, ������ġ�� Bosch ��ǰ�� ����մϴ�.\n";
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
    // Ư�� �ڵ����� "ȣȯ���� �ʴ�" ������ġ ����
    std::unordered_map<CarType, std::unordered_set<BreakSystem>> breaksystems;

    // �����ϰ� "ȣȯ�Ǵ�" ��ġ ���� <������ġ ����, <��ġ ����, ��ǰ �̸�>>
    //std::unordered_map<Engine, std::unordered_set<std::pair<std::string, std::string>>> engine_only;
};
// ������ġ�� ȣȯ�� ����
class SteeringSystemManagement : public PartSystem<SteeringSystem> {
public:
    void add_incompatible_part(CarType car, SteeringSystem steeringsystem) override {
        // car�� enum class CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
            return;
        }
        // steeringsystem�� enum class SteeringSystem�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(steeringsystem) <= 0) {
            std::cout << "It's an invalid steeringsystem.\n";
            return;
        }
        steeringsystems[car].insert(steeringsystem);
        std::cout << "SteeringSystem " << static_cast<int>(steeringsystem) << " added.\n";
    }

    void remove_part(CarType car, SteeringSystem steeringsystem) override {
        // car�� enum class CarType�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(car) <= 0) {
            std::cout << "It's an invalid car type.\n";
        }
        // steeringsystem�� enum class SteeringSystem�� �����ϴ��� Ȯ���Ѵ�.
        if (static_cast<int>(steeringsystem) <= 0) {
            std::cout << "It's an invalid steeringsystem.\n";
            return;
        }
        // car�� steeringsystems�� �����ϴ��� Ȯ���Ѵ�.
        if (steeringsystems.find(car) == steeringsystems.end()) {
            std::cout << "Car " << static_cast<int>(car) << " does not exist.\n";
            return;
        }
        else {
            // steeringsystem�� �����ϴ��� Ȯ���Ѵ�.
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

    // ������ġ���� ȣȯ���� �Ǵ��Ѵ�.
    bool is_compatible(SteeringSystem steeringsystem, Part part) override {
        // ���� ��ġ�� ���� �� ������� �ʴ´�.
        if (std::holds_alternative<SteeringSystem>(part)) {
            std::cout << "Can't use multiple of the same part.\n";
            return false;
        }
        // ������ġ�� �ڵ����� ȣȯ���� �Ǵ��Ѵ�.
        if (std::holds_alternative<CarType>(part)) {
            CarType car = std::get<CarType>(part);
            if (steeringsystems[car].find(steeringsystem) == steeringsystems[car].end()) {
                return true;
            }
            else {
                return false;
            }
        }
        // ������ġ�� �ٸ� ��ġ�� ȣȯ���� �Ǵ��Ѵ�.(Ÿ �� ��ǰ ȣȯ x)
        else {
            if (steeringsystem == SteeringSystem::BOSCH) {
                if (std::holds_alternative<BreakSystem>(part)) {
                    BreakSystem breaksystem = std::get<BreakSystem>(part);
                    if (breaksystem == BreakSystem::BOSCH) {
                        return true;
                    }
                    std::cout << "������ġ�� Bosch ��ǰ�� ��ٸ�, ������ġ�� Bosch ��ǰ�� ����մϴ�.\n";
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
    // Ư�� �ڵ����� "ȣȯ���� �ʴ�" ������ġ ����
    std::unordered_map<CarType, std::unordered_set<SteeringSystem>> steeringsystems;

    // �����ϰ� "ȣȯ�Ǵ�" ��ġ ���� <������ġ ����, <��ġ ����, ��ǰ �̸�>>
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

    // ��ǰ�� �߰��ϴ� ���
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

    // ��ǰ�� �����ϴ� ���
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

    // ��ǰ �� ȣȯ�� Ȯ��
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

    // ��� ��ǰ �� ȣȯ�� Ȯ��
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

    // ��ǰ �ý��� ���� ���
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

    // ��� ��ǰ �ý��� ���� ���
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