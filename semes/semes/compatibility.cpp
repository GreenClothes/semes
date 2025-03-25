#include "compatibility.h"

//Compatibility::Compatibility() {
//
//}

//template <typename PartType>
//inline void Compatibility::add_part(CarType car, PartType part) {
//    // (추가) car가 enum class CarType에 존재하는지 확인한다.
//
//    // 부품 리스트에 값을 추가한다.
//    // (추가) part가 enum class PartType에 존재하는지 확인한다.
//    if constexpr (std::is_same_v<PartType, Engine>) {
//        engine[car].insert(part);
//    }
//    else if constexpr (std::is_same_v<PartType, BreakSystem>) {
//        break_system[car].insert(part);
//    }
//    else if constexpr (std::is_same_v<PartType, SteeringSystem>) {
//        steering_system[car].insert(part);
//    }
//    else {
//        std::cout << "Unsupported part type.\n";
//    }
//}

//template <typename PartType>
//void Compatibility::remove_part(CarType car, PartType part) {
//    // (추가) car가 enum class CarType에 존재하는지 확인한다.
//
//    // 부품 리스트에서 값을 제거한다.
//    // (추가) part가 enum class PartType에 존재하는지 확인한다.
//    if constexpr (std::is_same_v<PartType, Engine>) {
//        if (engine.find(car) != engine.end()) {
//            engine[car].erase(part);
//        }
//        else {
//            std::cout << static_cast<int>(car) << " does not exist.\n";
//        }
//    }
//    else if constexpr (std::is_same_v<PartType, BreakSystem>) {
//        if (break_system.find(car) != break_system.end()) {
//            break_system[car].erase(part);
//        }
//        else {
//            std::cout << static_cast<int>(car) << " does not exist.\n";
//        }
//    }
//    else if constexpr (std::is_same_v<PartType, SteeringSystem>) {
//        if (steering_system.find(car) != steering_system.end()) {
//            steering_system[car].erase(part);
//        }
//        else {
//            std::cout << static_cast<int>(car) << " does not exist.\n";
//        }
//    }
//    else {
//        std::cout << "Unsupported part type.\n";
//    }
//}

//template <typename PartType>
//bool is_compatible(CarType car, PartType part) {
//
//    return 0;
//}

void Compatibility::show_engine() {
    using std::cout;
    for (const auto& car : engine) {
        cout << "Car Type: " << static_cast<int>(car.first) << " (";
        switch (car.first) {
        case CarType::SEDAN: 
            cout << "SEDAN"; break;
        case CarType::SUV: 
            cout << "SUV"; break;
        case CarType::TRUCK: 
            cout << "TRUCK"; break;
        default:
            cout << static_cast<int>(car.first) << " does not exist.\n";
        }
        std::cout << ")\n-> Incompatible Engines: ";

        if (car.second.empty()) {
            std::cout << "None";
        }
        else {
            for (const auto& x : car.second) {
                switch (x) {
                case Engine::GM: 
                    std::cout << "GM "; break;
                case Engine::TOYOTA: 
                    std::cout << "TOYOTA "; break;
                case Engine::WIA: 
                    std::cout << "WIA "; break;
                default:
                    cout << static_cast<int>(x) << " does not exist.\n";
                }
            }
        }
        std::cout << '\n';
    }
}
void Compatibility::show_break() {
    using std::cout;
    for (const auto& car : break_system) {
        cout << "Car Type: " << static_cast<int>(car.first) << " (";
        switch (car.first) {
        case CarType::SEDAN:
            cout << "SEDAN"; break;
        case CarType::SUV:
            cout << "SUV"; break;
        case CarType::TRUCK:
            cout << "TRUCK"; break;
        default:
            cout << static_cast<int>(car.first) << " does not exist.\n";
        }
        std::cout << ")\n-> Incompatible BreakSystems: ";

        if (car.second.empty()) {
            std::cout << "None";
        }
        else {
            for (const auto& x : car.second) {
                switch (x) {
                case BreakSystem::MANDO:
                    std::cout << "MANDO "; break;
                case BreakSystem::CONTINENTAL:
                    std::cout << "CONTINENTAL "; break;
                case BreakSystem::BOSCH:
                    std::cout << "BOSCH "; break;
                default:
                    cout << static_cast<int>(x) << " does not exist.\n";
                }
            }
        }
        std::cout << '\n';
    }
}
void Compatibility::show_steering() {
    using std::cout;
    for (const auto& car : steering_system) {
        cout << "Car Type: " << static_cast<int>(car.first) << " (";
        switch (car.first) {
        case CarType::SEDAN:
            cout << "SEDAN"; break;
        case CarType::SUV:
            cout << "SUV"; break;
        case CarType::TRUCK:
            cout << "TRUCK"; break;
        default:
            cout << static_cast<int>(car.first) << " does not exist.\n";
        }
        std::cout << ")\n-> Incompatible SteeringSystems: ";

        if (car.second.empty()) {
            std::cout << "None";
        }
        else {
            for (const auto& x : car.second) {
                switch (x) {
                case SteeringSystem::BOSCH:
                    std::cout << "BOSCH "; break;
                case SteeringSystem::MOBIS:
                    std::cout << "MOBIS "; break;
                default:
                    cout << static_cast<int>(x) << " does not exist.\n";
                }
            }
        }
        std::cout << '\n';
    }
}
