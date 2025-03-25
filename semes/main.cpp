#include "compatibility.h"

int main() {
	Compatibility compatibility;

	std::cout << "[add] ===================\n";
	compatibility.add_part(CarType::SEDAN, BreakSystem::CONTINENTAL);
	compatibility.add_part(CarType::SUV, Engine::TOYOTA);
	compatibility.add_part(CarType::TRUCK, Engine::WIA);
	compatibility.add_part(CarType::TRUCK, BreakSystem::MANDO);

	// 제거 테스트 용
	compatibility.add_part(CarType::SEDAN, BreakSystem::BOSCH);
	compatibility.add_part(CarType::SEDAN, SteeringSystem::BOSCH);
	
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
	
	return 0;
}