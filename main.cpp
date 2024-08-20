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

    void displayCustomer() const {
        cout << "Customer Name: " << this->name << endl;
    }
};

int main() {
    // Dynamic allocation of Car objects
    Car* carArray[3];
    carArray[0] = new Car("Honda", "Civic", 2023, 220000);
    carArray[1] = new Car("Toyota", "Camry", 2022, 250000);
    carArray[2] = new Car("Ford", "Mustang", 2021, 300000);

    // Dynamic allocation of Customer objects
    Customer* customerArray[3];
    customerArray[0] = new Customer("Sahil Kharatmol");
    customerArray[1] = new Customer("Parth Shah");
    customerArray[2] = new Customer("Divyam Seth");

    // Interactions with the customers and cars
    for (int i = 0; i < 3; i++) {
        customerArray[i]->inquire(*carArray[i]);
        customerArray[i]->testDrive(*carArray[i]);
        customerArray[i]->purchase(*carArray[i]);
    }

    // Displaying all cars' status
    cout << "List of Cars:" << endl;
    for(int i = 0; i < 3; i++) {
        carArray[i]->displayInfo();
    }

    // Deallocating memory
    for(int i = 0; i < 3; i++) {
        delete carArray[i];
        delete customerArray[i];
    }

    return 0;
}
