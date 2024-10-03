#include <iostream>
#include <string>

using namespace std;

// Base class for Cars
class Car {
private:
    string make, model;
    int year;
    double price;
    bool isAvailable;

    static int totalCarsSold;
    static double totalRevenue;

public:
    // Constructors and Destructor
    Car() : make("Unknown"), model("Unknown"), year(0), price(0.0), isAvailable(false) {
        cout << "Default Constructor called: Car created with default values." << endl;
    }

    Car(string make, string model, int year, double price)
        : make(make), model(model), year(year), price(price), isAvailable(true) {
        cout << "Parameterized Constructor called: Car created with specified values." << endl;
    }

    ~Car() {
        cout << "Destructor called: Car object is being destroyed." << endl;
    }

    // Accessors and Mutators
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    bool getIsAvailable() const { return isAvailable; }

    void setMake(const string& newMake) { make = newMake; }
    void setModel(const string& newModel) { model = newModel; }
    void setYear(int newYear) { year = newYear; }
    void setPrice(double newPrice) { price = newPrice; }
    void setIsAvailable(bool availability) { isAvailable = availability; }

    // Display car info
    void displayInfo() const {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year 
             << ", Price: " << price << " Rs, " 
             << (isAvailable ? "Available" : "Sold") << endl;
    }

    // Mark car as sold
    void markAsSold() {
        if (isAvailable) {
            isAvailable = false;
            totalCarsSold++;
            totalRevenue += price;
            cout << "The car has been marked as sold." << endl;
        } else {
            cout << "Car is already sold." << endl;
        }
    }

    // Static methods
    static int getTotalCarsSold() { return totalCarsSold; }
    static double getTotalRevenue() { return totalRevenue; }
};

// Initialize static variables
int Car::totalCarsSold = 0;
double Car::totalRevenue = 0.0;

// Derived class for Single Inheritance
class LuxuryCar : public Car {
private:
    string luxuryFeatures;

public:
    LuxuryCar(string make, string model, int year, double price, string features)
        : Car(make, model, year, price), luxuryFeatures(features) {
        cout << "Luxury Car created with additional features." << endl;
    }

    void displayLuxuryInfo() const {
        displayInfo();
        cout << "Luxury Features: " << luxuryFeatures << endl;
    }
};

// Base class for Customers
class Customer {
private:
    string name;

    static int totalCustomers;

public:
    // Constructors and Destructor
    Customer() : name("Unknown") {
        cout << "Default Constructor called: Customer created with default name." << endl;
        totalCustomers++;
    }

    Customer(string name) : name(name) {
        cout << "Parameterized Constructor called: Customer created with specified name." << endl;
        totalCustomers++;
    }

    ~Customer() {
        cout << "Destructor called: Customer object is being destroyed." << endl;
    }

    // Accessors and Mutators
    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }

    // Inquire and test drive
    void inquire(const Car& car) const {
        cout << name << " is inquiring about the following car:" << endl;
        car.displayInfo();
    }

    void testDrive(const Car& car) const {
        cout << name << " is test driving the inquired car." << endl;
    }

    // Purchase a car
    void purchase(Car& car) {
        if (car.getIsAvailable()) {
            car.markAsSold();
            cout << name << " bought the inquired car." << endl;
        } else {
            cout << "Car is not available for purchase." << endl;
        }
    }

    // Static method
    static int getTotalCustomers() { return totalCustomers; }
};

// Initialize static variable
int Customer::totalCustomers = 0;

// Multilevel Inheritance
class RegularCustomer : public Customer {
public:
    RegularCustomer(string name) : Customer(name) {
        cout << "Regular Customer created." << endl;
    }
};

class VIPCustomer : public RegularCustomer {
public:
    VIPCustomer(string name) : RegularCustomer(name) {
        cout << "VIP Customer created with extra perks." << endl;
    }
};

// Main function demonstrating the use of inheritance and examples
int main() {
    // Creating dynamic Car objects (Regular and Luxury)
    Car* carArray[3];
    carArray[0] = new Car("Honda", "Civic", 2023, 220000);
    carArray[1] = new LuxuryCar("BMW", "7 Series", 2023, 500000, "Leather seats, Sunroof, Premium sound system");
    carArray[2] = new Car("Ford", "Mustang", 2021, 300000);

    // Creating dynamic Customer objects (Regular and VIP)
    RegularCustomer* customerArray[3];
    customerArray[0] = new VIPCustomer("Sahil Kharatmol");
    customerArray[1] = new RegularCustomer("Parth Shah");
    customerArray[2] = new RegularCustomer("Divyam Seth");

    // Accessor and mutator examples
    cout << "Before modification:" << endl;
    cout << "Car Make: " << carArray[0]->getMake() << ", Model: " << carArray[0]->getModel() << endl;
    cout << "Customer Name: " << customerArray[0]->getName() << endl;

    carArray[0]->setMake("Hyundai");
    carArray[0]->setModel("Elantra");
    customerArray[0]->setName("Aditya Borhade");

    cout << "After modification:" << endl;
    cout << "Car Make: " << carArray[0]->getMake() << ", Model: " << carArray[0]->getModel() << endl;
    cout << "Customer Name: " << customerArray[0]->getName() << endl;

    // Customer interactions
    customerArray[0]->inquire(*carArray[0]);
    customerArray[0]->testDrive(*carArray[0]);
    customerArray[0]->purchase(*carArray[0]);

    customerArray[1]->inquire(*carArray[1]);
    customerArray[1]->testDrive(*carArray[1]);
    customerArray[1]->purchase(*carArray[1]);

    customerArray[2]->inquire(*carArray[2]);
    customerArray[2]->testDrive(*carArray[2]);

    // Display all cars' status
    cout << "List of Cars:" << endl;
    for (int i = 0; i < 3; i++) {
        carArray[i]->displayInfo();
    }

    // Static method calls
    cout << "Total Customers: " << Customer::getTotalCustomers() << endl;
    cout << "Total Cars Sold: " << Car::getTotalCarsSold() << endl;
    cout << "Total Revenue: " << Car::getTotalRevenue() << " Rs" << endl;

    // Clean up
    for (int i = 0; i < 3; i++) {
        delete carArray[i];
        delete customerArray[i];
    }

    return 0;
}
