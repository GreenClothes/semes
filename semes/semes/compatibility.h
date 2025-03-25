#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "carInfo.h"

class Compatibility {
public:
	// 자동차 타입에 "호환되지 않는" 엔진, 제동, 조향을 추가한다.
	template <typename PartType>
	void add_part(CarType, PartType);

	// 자동차 타입에 "호환되지 않는" 엔진, 제동, 조향을 제거한다.
	template <typename PartType>
	void remove_part(CarType, PartType);

	// 호환성을 확인한다. -> 호환되면 return true
	template <typename CmpType1, typename CmpType2>
	bool is_compatible(CmpType1, CmpType2);

	void show_engine();
	void show_break();
	void show_steering();

private:
	// 자동차 타입 <-> 엔진
	// Engine
	std::unordered_map<CarType, std::unordered_set<Engine>> engine;

	// 자동차 타입 <-> 제동
	// Break System
	std::unordered_map<CarType, std::unordered_set<BreakSystem>> break_system;

	// 자동차 타입 <-> 조향
	// Steering System
	std::unordered_map<CarType, std::unordered_set<SteeringSystem>> steering_system;
};

template <typename PartType>
inline void Compatibility::add_part(CarType car, PartType part) {
	// (추가) car가 enum class CarType에 존재하는지 확인한다.

	// 부품 리스트에 값을 추가한다.
	// (추가) part가 enum class PartType에 존재하는지 확인한다.
	if constexpr (std::is_same_v<PartType, Engine>) {
		engine[car].insert(part);
	}
	else if constexpr (std::is_same_v<PartType, BreakSystem>) {
		break_system[car].insert(part);
	}
	else if constexpr (std::is_same_v<PartType, SteeringSystem>) {
		steering_system[car].insert(part);
	}
	else {
		std::cout << "Unsupported part type.\n";
	}
}

template <typename PartType>
void Compatibility::remove_part(CarType car, PartType part) {
	// (추가) car가 enum class CarType에 존재하는지 확인한다.

	// 부품 리스트에서 값을 제거한다.
	// (추가) part가 enum class PartType에 존재하는지 확인한다.
	if constexpr (std::is_same_v<PartType, Engine>) {
		if (engine.find(car) == engine.end()) {
			std::cout << static_cast<int>(car) << " does not exist.\n";
			return;
		}
		if (engine[car].find(part) == engine[car].end()) {
			std::cout << static_cast<int>(part) << " does not exist.\n";
			return;
		}
		engine[car].erase(part);
		std::cout << "Erase " << static_cast<int>(part) << "\n";
	}
	else if constexpr (std::is_same_v<PartType, BreakSystem>) {
		if (break_system.find(car) == break_system.end()) {
			std::cout << static_cast<int>(car) << " does not exist.\n";
			return;
		}
		if (break_system[car].find(part) == break_system[car].end()) {
			std::cout << static_cast<int>(part) << " does not exist.\n";
			return;
		}
		break_system[car].erase(part);
		std::cout << "Erase " << static_cast<int>(part) << "\n";
	}
	else if constexpr (std::is_same_v<PartType, SteeringSystem>) {
		if (steering_system.find(car) == steering_system.end()) {
			std::cout << static_cast<int>(car) << " does not exist.\n";
			return;
		}
		if (steering_system[car].find(part) == steering_system[car].end()) {
			std::cout << static_cast<int>(part) << " does not exist.\n";
			return;
		}
		steering_system[car].erase(part);
		std::cout << "Erase " << static_cast<int>(part) << "\n";
	}
	else {
		std::cout << "Unsupported part type.\n";
	}
}

template <typename CmpType1, typename CmpType2>
bool Compatibility::is_compatible(CmpType1 type1, CmpType2 type2) {
	if constexpr (std::is_same_v<CmpType1, CarType>) {
		if constexpr (std::is_same_v<CmpType2, CarType>) {
			std::cout << "Can't use multiple of the car.\n";
			return false;
		}
		else {
			if constexpr (std::is_same_v<CmpType2, Engine>) {
				if (engine[type1].find(type2) == engine[type1].end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType2, BreakSystem>) {
				if (engine[type1].find(type2) == break_system[type1].end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType2, SteeringSystem>) {
				if (engine[type1].find(type2) == steering_system[type1].end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				std::cout << "Unsupported part type.\n";
				return false;
			}
		}
	}
	else if constexpr (std::is_same_v<CmpType2, CarType>) {
		if constexpr (std::is_same_v<CmpType1, CarType>) {
			std::cout << "Can't use multiple of the car.\n";
			return false;
		}
		else {
			if constexpr (std::is_same_v<CmpType1, Engine>) {
				if (engine[type2].find(type1) == engine[type2].end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType1, BreakSystem>) {
				if (engine[type2].find(type1) == break_system[type2].end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType1, SteeringSystem>) {
				if (engine[type2].find(type1) == steering_system[type2].end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				std::cout << "Unsupported part type.\n";
				return false;
			}
		}
	}
	else if constexpr (std::is_same_v<CmpType1, CmpType2>) {
		std::cout << "Can't use multiple of the same part.\n";
		return false;
	}
	else {
		if constexpr (std::is_same_v<CmpType1, BreakSystem> && std::is_same_v<CmpType2, SteeringSystem>) {
			if (type1 == BreakSystem::BOSCH) {
				if (type2 == SteeringSystem::BOSCH) {
					return true;
				}
				std::cout << "제동장치에 Bosch 제품을 썼다면, 조향장치도 Bosch 제품을 써야합니다.\n";
				return false;
			}
			else if (type2 == SteeringSystem::BOSCH) {
				if (type1 == BreakSystem::BOSCH) {
					return true;
				}
				std::cout << "조향장치에 Bosch 제품을 썼다면, 제동장치도 Bosch 제품을 써야합니다.\n";
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
		/*if constexpr (std::is_same_v<CmpType1, Engine>) {
			if constexpr (std::is_same_v<CmpType2, BreakSystem>) {
				if (type1 == type2) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType2, SteeringSystem>) {
				if (type1 == type2) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				std::cout << "Unsupported part type.\n";
				return false;
			}
		}
		else if constexpr (std::is_same_v<CmpType1, BreakSystem>) {
			if constexpr (std::is_same_v<CmpType2, Engine>) {
				if (type1 == type2) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType2, SteeringSystem>) {
				if (type1 == type2) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				std::cout << "Unsupported part type.\n";
				return false;
			}
		}
		else if constexpr (std::is_same_v<CmpType1, SteeringSystem>) {
			if constexpr (std::is_same_v<CmpType2, Engine>) {
				if (type1 == type2) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (std::is_same_v<CmpType2, BreakSystem>) {
				if (type1 == type2) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				std::cout << "Unsupported part type.\n";
				return false;
			}
		}
		else {
			std::cout << "Unsupported part type.\n";
			return false;
		}*/
	}
	return false;
}