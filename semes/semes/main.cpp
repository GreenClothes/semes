#include "car.h"
#include "user_interface.h"
#include "CarServer.h"

int main() {
    // �ڵ��� ��ü ����
    Car car;

    CarServer* carServer = new CarServer();
    try {
        carServer->StartServer();

        // ����� �������̽� ��ü ���� �� ����
        UserInterface ui(car);
        ui.run();
    }
    catch (std::exception e) {
        std::cout << "Error Occur : " << e.what() << "\n";
        carServer->EndServer();
        delete carServer;
    }

    return 0;
}