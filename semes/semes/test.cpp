#include <unordered_map>
#include <string>
#include "compatibility.h"
#include "compatibility_.h"

int main() {
	Compatibility_ compatibility_;

	std::cout << "[add] ===================\n";
	compatibility_.add_incompatible_part("break", CarType::SEDAN, BreakSystem::CONTINENTAL);
	compatibility_.add_incompatible_part("engine", CarType::SUV, Engine::TOYOTA);
	compatibility_.add_incompatible_part("engine", CarType::TRUCK, Engine::WIA);
	compatibility_.add_incompatible_part("break", CarType::TRUCK, BreakSystem::MANDO);

	compatibility_.add_compatible_part("break", BreakSystem::BOSCH_B, "steering", SteeringSystem::BOSCH_S);
	compatibility_.add_compatible_part("steering", SteeringSystem::BOSCH_S, "break", BreakSystem::BOSCH_B);

	std::cout << "[show] ===================\n";
	compatibility_.show_systems_all();

	std::cout << "[add] ===================\n";
	compatibility_.add_incompatible_part("break", CarType::SEDAN, BreakSystem::BOSCH_B);
	compatibility_.add_incompatible_part("steering", CarType::SEDAN, SteeringSystem::BOSCH_S);

	std::cout << "[remove] ===================\n";
	compatibility_.remove_part("break", CarType::SEDAN, BreakSystem::BOSCH_B);
	compatibility_.remove_part("steering", CarType::SEDAN, SteeringSystem::BOSCH_S);

	std::cout << "[show] ===================\n";
	compatibility_.show_systems_all();

	std::cout << "[test] ===================\n";
	std::unordered_map<std::string, Part> parts;
	parts.insert({ "car", CarType::SEDAN });
	parts.insert({ "engine", Engine::TOYOTA });
	parts.insert({ "break", BreakSystem::MANDO });
	parts.insert({ "steering", SteeringSystem::MOBIS });
	bool test = compatibility_.is_compatible_all(parts);
	std::cout << "Is it compatible? " << (test ? "Yes" : "No") << "\n";

	/*Compatibility compatibility;

	std::cout << "[add] ===================\n";
	compatibility.add_incompatible_part(CarType::SEDAN, BreakSystem::CONTINENTAL);
	compatibility.add_incompatible_part(CarType::SUV, Engine::TOYOTA);
	compatibility.add_incompatible_part(CarType::TRUCK, Engine::WIA);
	compatibility.add_incompatible_part(CarType::TRUCK, BreakSystem::MANDO);

	// 제거 테스트 용
	compatibility.add_incompatible_part(CarType::SEDAN, BreakSystem::BOSCH);
	compatibility.add_incompatible_part(CarType::SEDAN, SteeringSystem::BOSCH);

	compatibility.show_engine();
	compatibility.show_break();
	compatibility.show_steering();

	std::cout << "[remove] ===================\n";
	compatibility.remove_part(CarType::SEDAN, BreakSystem::BOSCH);
	compatibility.remove_part(CarType::SEDAN, SteeringSystem::BOSCH);

	compatibility.show_engine();
	compatibility.show_break();
	compatibility.show_steering();

	std::cout << "[compatible] ===================\n";
	// false
	std::cout << compatibility.is_compatible(CarType::TRUCK, Engine::WIA) << "\n";
	// true
	std::cout << compatibility.is_compatible(CarType::SUV, Engine::WIA) << "\n";
	// true
	std::cout << compatibility.is_compatible(BreakSystem::BOSCH, SteeringSystem::BOSCH) << "\n";
	// true
	std::cout << compatibility.is_compatible(SteeringSystem::BOSCH, BreakSystem::BOSCH) << "\n";
	// false
	std::cout << compatibility.is_compatible(BreakSystem::BOSCH, SteeringSystem::MOBIS) << "\n";
	// false
	std::cout << compatibility.is_compatible(BreakSystem::CONTINENTAL, SteeringSystem::BOSCH) << "\n";
	// true
	std::cout << compatibility.is_compatible(Engine::TOYOTA, SteeringSystem::MOBIS) << "\n";
	*/

	return 0;
}