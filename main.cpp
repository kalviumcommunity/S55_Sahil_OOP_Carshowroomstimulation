#include <iostream>
#include <string>

using namespace std;

// Abstract Base class for Cars
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

    virtual ~Car() {
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

    // Pure virtual function to make Car an abstract class
    virtual void displayInfo() const = 0;  // Pure virtual function

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

// Derived class demonstrating runtime polymorphism
class LuxuryCar : public Car {
private:
    string luxuryFeatures;

public:
    LuxuryCar(string make, string model, int year, double price, string features)
        : Car(make, model, year, price), luxuryFeatures(features) {
        cout << "Luxury Car created with additional features." << endl;
    }

    // Overriding displayInfo to add luxury features
    void displayInfo() const override {
        cout << "Make: " << getMake() << ", Model: " << getModel() << ", Year: " << getYear() 
             << ", Price: " << getPrice() << " Rs, "
             << (getIsAvailable() ? "Available" : "Sold") << endl;
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

    // Function overloading (Compile-time polymorphism)
    void inquire(const Car& car) const {
        cout << name << " is inquiring about the following car:" << endl;
        car.displayInfo();
    }

    void inquire(const Car& car, const string& additionalRequest) const {
        cout << name << " is inquiring about the following car with additional request (" << additionalRequest << "):" << endl;
        car.displayInfo();
    }

    // Test drive
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

int main() {
    // Creating dynamic Car objects (3 cars: Regular and Luxury)
    Car* carArray[3];
    carArray[0] = new LuxuryCar("BMW", "7 Series", 2023, 500000, "Leather seats, Sunroof, Premium sound system");
    carArray[1] = new LuxuryCar("Mercedes", "S Class", 2023, 400000, "Massage seats, Panoramic sunroof");
    carArray[2] = new LuxuryCar("Audi", "A8", 2023, 550000, "Heated seats, Night vision");

    // Creating dynamic Customer objects (Regular and VIP)
    RegularCustomer* customerArray[2];
    customerArray[0] = new VIPCustomer("Sahil Kharatmol");
    customerArray[1] = new RegularCustomer("Parth Shah");

    // Accessor and mutator examples
    cout << "Before modification:" << endl;
    cout << "Customer Name: " << customerArray[0]->getName() << endl;

    customerArray[0]->setName("Aditya Borhade");

    cout << "After modification:" << endl;
    cout << "Customer Name: " << customerArray[0]->getName() << endl;

    // Customer interactions demonstrating polymorphism
    customerArray[0]->inquire(*carArray[0]);
    customerArray[0]->inquire(*carArray[1], "with a premium package request");
    customerArray[0]->testDrive(*carArray[0]);
    customerArray[0]->purchase(*carArray[0]);

    customerArray[1]->inquire(*carArray[2]);
    customerArray[1]->testDrive(*carArray[2]);
    customerArray[1]->purchase(*carArray[2]);

    // Display all cars' status using runtime polymorphism
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
    }
    for (int i = 0; i < 2; i++) {
        delete customerArray[i];
    }

    return 0;
}
