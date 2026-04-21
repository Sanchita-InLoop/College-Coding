#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Vehicle {
protected:
    string brand;
    string licensePlate;
    string type;
    int capacity;

public:
    Vehicle(string b, string lp, string t, int cap)
        : brand(b), licensePlate(lp), type(t), capacity(cap) {}
   
    virtual ~Vehicle() {}

    void start() { cout << type << " (" << licensePlate << ") engine started." << endl; }
    void stop() { cout << type << " (" << licensePlate << ") engine stopped." << endl; }

    virtual void displayInfo() {
        cout << "Type: " << type << " | Brand: " << brand
             << " | Plate: " << licensePlate << " | Capacity: " << capacity;
    }

    virtual string serialize() {
        return type + "," + brand + "," + licensePlate + "," + to_string(capacity);
    }

    string getType() { return type; }
};

class Car : public Vehicle {
public:
    Car(string b, string lp, int cap) : Vehicle(b, lp, "Car", cap) {}
   
    void displayInfo() override {
        Vehicle::displayInfo();
        cout << " [Category: Passenger]" << endl;
    }
};

class Truck : public Vehicle {
public:
    Truck(string b, string lp, int cap) : Vehicle(b, lp, "Truck", cap) {}
   
    void displayInfo() override {
        Vehicle::displayInfo();
        cout << " [Load Capacity: " << capacity << " tons]" << endl;
    }
};

class Bus : public Vehicle {
public:
    Bus(string b, string lp, int cap) : Vehicle(b, lp, "Bus", cap) {}

    void displayInfo() override {
        Vehicle::displayInfo();
        cout << " [Category: Public Transport]" << endl;
    }
};

class FleetManager {
private:
    Vehicle* fleet[100];
    int vehicleCount;

public:
    FleetManager() : vehicleCount(0) {
        for (int i = 0; i < 100; i++) fleet[i] = nullptr;
    }

    ~FleetManager() {
        for (int i = 0; i < vehicleCount; i++) {
            delete fleet[i];
        }
    }

    void addVehicle(Vehicle* v) {
        if (vehicleCount < 100) {
            fleet[vehicleCount++] = v;
        } else {
            cout << "Fleet is full!" << endl;
        }
    }

    void showFleet() {
        if (vehicleCount == 0) {
            cout << "Fleet is empty." << endl;
            return;
        }
        for (int i = 0; i < vehicleCount; i++) {
            fleet[i]->displayInfo();
        }
    }

    void saveToFile(string filename) {
        ofstream outFile(filename);
        if (!outFile) return;

        for (int i = 0; i < vehicleCount; i++) {
            outFile << fleet[i]->serialize() << endl;
        }
        outFile.close();
        cout << ">> Fleet data saved to " << filename << endl;
    }

    void loadFromFile(string filename) {
        ifstream inFile(filename);
        if (!inFile) return;

        for (int i = 0; i < vehicleCount; i++) delete fleet[i];
        vehicleCount = 0;

        string line;
        while (getline(inFile, line) && vehicleCount < 100) {
            stringstream ss(line);
            string vType, vBrand, vPlate, vCap;

            getline(ss, vType, ',');
            getline(ss, vBrand, ',');
            getline(ss, vPlate, ',');
            getline(ss, vCap, ',');

            int cap = stoi(vCap);

            if (vType == "Car") addVehicle(new Car(vBrand, vPlate, cap));
            else if (vType == "Truck") addVehicle(new Truck(vBrand, vPlate, cap));
            else if (vType == "Bus") addVehicle(new Bus(vBrand, vPlate, cap));
        }
        inFile.close();
        cout << ">> Fleet data loaded from " << filename << endl;
    }
};

int main() {
    FleetManager myFleet;

    myFleet.addVehicle(new Car("Toyota", "CAM-123", 5));
    myFleet.addVehicle(new Truck("Freightliner", "TRK-99", 15));
    myFleet.addVehicle(new Bus("Mercedes", "BUS-77", 40));

    cout << "Initial Fleet" << endl;
    myFleet.showFleet();

    myFleet.saveToFile("data.csv");
   
    cout << "\nReloading Data" << endl;
    myFleet.loadFromFile("data.csv");
    myFleet.showFleet();

    return 0;
}
