#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;
    double price;
    bool isAvailable;

public:
    Car(string make, string model, int year, double price)
        : make(make), model(model), year(year), price(price), isAvailable(true) {}

    void displayInfo() const {
        cout << "Make: " << this->make << ", Model: " << this->model << ", Year: " << this->year
             << ", Price: " << this->price << "Rs, " << (this->isAvailable ? "Available" : "Sold") << endl;
    }

    void markAsSold() {
        this->isAvailable = false;
        cout << "The car has been marked as sold." << endl;
    }

    bool checkAvailability() const {
        return this->isAvailable;
    }

    Car& getThisCar() {
        return *this;
    }
};

class Customer {
private:
    string name;

public:
    Customer(string name) : name(name) {}

    void inquire(const Car& car) const {
        cout << this->name << " is inquiring about the following car:" << endl;
        car.displayInfo();
    }

    void testDrive(const Car& car) const {
        cout << this->name << " is test driving the inquired car." << endl;
    }

    void purchase(Car& car) {
        if (car.getThisCar().checkAvailability()) {
            car.getThisCar().markAsSold();
            cout << this->name << " bought the inquired car." << endl;
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
