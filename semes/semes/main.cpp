#include "car.h"
#include "user_interface.h"

int main() {
    // 자동차 객체 생성
    Car car;

    // 사용자 인터페이스 객체 생성 및 실행
    UserInterface ui(car);
    ui.run();

    return 0;
}