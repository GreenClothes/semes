#include "compatibility_.h"

std::unordered_set<std::string> partList;

void Compatibility_::add_incompatible_part(const std::string& partType, CarType car, Part part) {
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

void Compatibility_::add_compatible_part(const std::string& partType, Part part1, const std::string& addPartType, Part part2) {
    if (partType == "engine") {
        if (std::holds_alternative<Engine>(part1)) {
            engineSystemManagement->add_compatible_part(std::get<Engine>(part1), addPartType, part2);
        }
        else {
            std::cout << "It's an invalid input.\n";
        }
    }
    else if (partType == "break") {
        if (std::holds_alternative<BreakSystem>(part1)) {
            breakSystemManagement->add_compatible_part(std::get<BreakSystem>(part1), addPartType, part2);
        }
        else {
            std::cout << "It's an invalid input.\n";
        }
    }
    else if (partType == "steering") {
        if (std::holds_alternative<SteeringSystem>(part1)) {
            steeringSystemManagement->add_compatible_part(std::get<SteeringSystem>(part1), addPartType, part2);
        }
        else {
            std::cout << "It's an invalid input.\n";
        }
    }
    else {
        std::cout << "Invalid part type\n";
    }
}

void Compatibility_::remove_part(const std::string& partType, CarType car, Part part) {
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

bool Compatibility_::is_compatible_all(std::unordered_map<std::string, Part>& parts) {
    if (!engineSystemManagement->is_compatible(std::get<Engine>(parts["engine"]), std::get<CarType>(parts["car"]))) {
        return false;
    }
    if (!breakSystemManagement->is_compatible(std::get<BreakSystem>(parts["break"]), std::get<CarType>(parts["car"]))) {
        return false;
    }
    if (!steeringSystemManagement->is_compatible(std::get<SteeringSystem>(parts["steering"]), std::get<CarType>(parts["car"]))) {
        return false;
    }

    if (!engineSystemManagement->is_compatible(std::get<Engine>(parts["engine"]), std::get<BreakSystem>(parts["break"]))) {
        return false;
    }
    if (!engineSystemManagement->is_compatible(std::get<Engine>(parts["engine"]), std::get<SteeringSystem>(parts["steering"]))) {
        return false;
    }
    if (!breakSystemManagement->is_compatible(std::get<BreakSystem>(parts["break"]), std::get<Engine>(parts["engine"]))) {
        return false;
    }
    if (!breakSystemManagement->is_compatible(std::get<BreakSystem>(parts["break"]), std::get<SteeringSystem>(parts["steering"]))) {
        return false;
    }
    if (!steeringSystemManagement->is_compatible(std::get<SteeringSystem>(parts["steering"]), std::get<Engine>(parts["engine"]))) {
        return false;
    }
    if (!steeringSystemManagement->is_compatible(std::get<SteeringSystem>(parts["steering"]), std::get<BreakSystem>(parts["break"]))) {
        return false;
    }
    return true;
}

void Compatibility_::show_systems(const std::string& partType) {
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

void Compatibility_::show_systems_all() {
    engineSystemManagement->show_parts();
    breakSystemManagement->show_parts();
    steeringSystemManagement->show_parts();
}