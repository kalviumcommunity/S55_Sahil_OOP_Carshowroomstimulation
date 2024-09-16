#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    // Private data members
    string make;
    string model;
    int year;
    double price;
    bool isAvailable;

    // Static variables (also private)
    static int totalCarsSold;
    static double totalRevenue;

public:
    // Constructor
    Car(string make, string model, int year, double price)
        : make(make), model(model), year(year), price(price), isAvailable(true) {}

    // Public accessors (getters) for private data members
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    bool getIsAvailable() const { return isAvailable; }

    // Public mutators (setters) for private data members
    void setMake(const string& newMake) { make = newMake; }
    void setModel(const string& newModel) { model = newModel; }
    void setYear(int newYear) { year = newYear; }
    void setPrice(double newPrice) { price = newPrice; }
    void setIsAvailable(bool availability) { isAvailable = availability; }

    // Public member function to display car info
    void displayInfo() const {
        cout << "Make: " << getMake() << ", Model: " << getModel() << ", Year: " << getYear()
             << ", Price: " << getPrice() << " Rs, " << (getIsAvailable() ? "Available" : "Sold") << endl;
    }

    // Public function to mark the car as sold
    void markAsSold() {
        if (getIsAvailable()) {
            setIsAvailable(false);
            totalCarsSold++;
            totalRevenue += getPrice();
            cout << "The car has been marked as sold." << endl;
        } else {
            cout << "Car is already sold." << endl;
        }
    }

    // Static methods to retrieve static private data
    static int getTotalCarsSold() {
        return totalCarsSold;
    }

    static double getTotalRevenue() {
        return totalRevenue;
    }
};

// Initialize static variables outside the class
int Car::totalCarsSold = 0;
double Car::totalRevenue = 0.0;

class Customer {
private:
    // Private data member
    string name;

    // Static variable
    static int totalCustomers;

public:
    // Constructor
    Customer(string name) : name(name) {
        totalCustomers++;
    }

    // Public accessor (getter)
    string getName() const { return name; }

    // Public mutator (setter)
    void setName(const string& newName) { name = newName; }

    // Public methods for customer interactions
    void inquire(const Car& car) const {
        cout << getName() << " is inquiring about the following car:" << endl;
        car.displayInfo();
    }

    void testDrive(const Car& car) const {
        cout << getName() << " is test driving the inquired car." << endl;
    }

    void purchase(Car& car) {
        if (car.getIsAvailable()) {
            car.markAsSold();
            cout << getName() << " bought the inquired car." << endl;
        } else {
            cout << "Car is not available for purchase." << endl;
        }
    }

    // Static method to get the total number of customers
    static int getTotalCustomers() {
        return totalCustomers;
    }
};

// Initialize static variable outside the class
int Customer::totalCustomers = 0;

int main() {
    // Creating dynamic Car objects
    Car* carArray[3];
    carArray[0] = new Car("Honda", "Civic", 2023, 220000);
    carArray[1] = new Car("Toyota", "Camry", 2022, 250000);
    carArray[2] = new Car("Ford", "Mustang", 2021, 300000);

    // Creating dynamic Customer objects
    Customer* customerArray[3];
    customerArray[0] = new Customer("Sahil Kharatmol");
    customerArray[1] = new Customer("Parth Shah");
    customerArray[2] = new Customer("Divyam Seth");

    // Using accessors (getters) and mutators (setters)
    cout << "Before modification:" << endl;
    cout << "Car Make: " << carArray[0]->getMake() << ", Model: " << carArray[0]->getModel() << endl;
    cout << "Customer Name: " << customerArray[0]->getName() << endl;

    // Modifying attributes using mutators
    carArray[0]->setMake("Hyundai");
    carArray[0]->setModel("Elantra");
    customerArray[0]->setName("Aditya Borhade");

    cout << "After modification:" << endl;
    cout << "Car Make: " << carArray[0]->getMake() << ", Model: " << carArray[0]->getModel() << endl;
    cout << "Customer Name: " << customerArray[0]->getName() << endl;

    // Customer interactions with cars
    customerArray[0]->inquire(*carArray[0]);
    customerArray[0]->testDrive(*carArray[0]);
    customerArray[0]->purchase(*carArray[0]);

    customerArray[1]->inquire(*carArray[1]);
    customerArray[1]->testDrive(*carArray[1]);
    customerArray[1]->purchase(*carArray[1]);

    customerArray[2]->inquire(*carArray[2]);
    customerArray[2]->testDrive(*carArray[2]);
    // The third customer does not purchase the car

    // Display all cars' status
    cout << "List of Cars:" << endl;
    for (int i = 0; i < 3; i++) {
        carArray[i]->displayInfo();
    }

    // Displaying static info
    cout << "Total Customers: " << Customer::getTotalCustomers() << endl;
    cout << "Total Cars Sold: " << Car::getTotalCarsSold() << endl;
    cout << "Total Revenue: " << Car::getTotalRevenue() << " Rs" << endl;

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        delete carArray[i];
        delete customerArray[i];
    }

    return 0;
}
