#include "car.h"
#include "user_interface.h"

int main() {
    // �ڵ��� ��ü ����
    Car car;

    // ����� �������̽� ��ü ���� �� ����
    UserInterface ui(car);
    ui.run();

    return 0;
}