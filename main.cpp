#include <iostream>
#include <string>

using namespace std;

class Car {
public:
    string make, model;
    int year;
    double price;
    bool isAvailable;

    Car(string make, string model, int year, double price)
        : make(make), model(model), year(year), price(price), isAvailable(true) {}

    void displayInfo() const {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year
             << ", Price: " << price << "Rs, " << (isAvailable ? "Available" : "Sold") << endl;
    }

    void markAsSold() {
        isAvailable = false;
        cout << "The inquired car has been marked as sold." << endl;
    }
};

class Customer {
public:
    string name;

    Customer(string name) : name(name) {}

    void inquire(const Car& car) const {
        cout << name << " is inquiring about the following car:" << endl;
        car.displayInfo();
    }

    void testDrive(const Car& car) const {
        cout << name << " is test driving the inquired car." << endl;
    }

    void purchase(Car& car) {
        if (car.isAvailable) {
            car.markAsSold();
            cout << name << " bought the inquired car." << endl;
        } else {
            cout << "Car is not available for purchase." << endl;
        }
    }
};

int main() {
    Car car1("Honda", "Civic", 2023, 220000);
    Car car2("Toyota", "Camry", 2022, 250000);

    Customer sahil("Sahil Kharatmol");

    sahil.inquire(car1);
    sahil.testDrive(car1);
    sahil.purchase(car1);

    cout << "List of Cars:" << endl;
    car1.displayInfo();
    car2.displayInfo();

    return 0;
}
