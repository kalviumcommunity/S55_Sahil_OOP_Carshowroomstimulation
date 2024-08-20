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

    // Static variable to keep track of the total number of cars sold
    static int totalCarsSold;
    // Static variable to keep track of the total revenue generated
    static double totalRevenue;

public:
    Car(string make, string model, int year, double price)
        : make(make), model(model), year(year), price(price), isAvailable(true) {}

    void displayInfo() const {
        cout << "Make: " << this->make << ", Model: " << this->model << ", Year: " << this->year
             << ", Price: " << this->price << " Rs, " << (this->isAvailable ? "Available" : "Sold") << endl;
    }

    void markAsSold() {
        this->isAvailable = false;
        totalCarsSold++;  // Increment the static variable when a car is sold
        totalRevenue += this->price;  // Add the price to the total revenue
        cout << "The car has been marked as sold." << endl;
    }

    bool checkAvailability() const {
        return this->isAvailable;
    }

    Car& getThisCar() {
        return *this;
    }

    // Static method to access the total number of cars sold
    static int getTotalCarsSold() {
        return totalCarsSold;
    }

    // Static method to access the total revenue
    static double getTotalRevenue() {
        return totalRevenue;
    }
};

// Initialize the static variables outside the class
int Car::totalCarsSold = 0;
double Car::totalRevenue = 0.0;

class Customer {
private:
    string name;
    static int totalCustomers;  // Static variable to keep track of the total number of customers

public:
    Customer(string name) : name(name) {
        totalCustomers++;  // Increment the static variable when a customer is created
    }

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

    // Static method to access the total number of customers
    static int getTotalCustomers() {
        return totalCustomers;
    }
};

// Initialize the static variable outside the class
int Customer::totalCustomers = 0;

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
    customerArray[0]->inquire(*carArray[0]);
    customerArray[0]->testDrive(*carArray[0]);
    customerArray[0]->purchase(*carArray[0]);

    customerArray[1]->inquire(*carArray[1]);
    customerArray[1]->testDrive(*carArray[1]);
    customerArray[1]->purchase(*carArray[1]);

    customerArray[2]->inquire(*carArray[2]);
    customerArray[2]->testDrive(*carArray[2]);
    // The third customer decides not to purchase the car

    // Displaying all cars' status
    cout << "List of Cars:" << endl;
    for(int i = 0; i < 3; i++) {
        carArray[i]->displayInfo();
    }

    // Displaying the total number of cars sold, total revenue, and total customers
    cout << "Total Customers: " << Customer::getTotalCustomers() << endl;
    cout << "Total Cars Sold: " << Car::getTotalCarsSold() << endl;
    cout << "Total Revenue: " << Car::getTotalRevenue() << " Rs" << endl;

    // Deallocating memory
    for(int i = 0; i < 3; i++) {
        delete carArray[i];
        delete customerArray[i];
    }

    return 0;
}
