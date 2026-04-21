#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Base Class: Abstract
class Container {
public:
    virtual double calculateVolume() const = 0;
    virtual ~Container() {}
};

// Derived Class: Box
class Box : public Container {
private:
    double length, width, height;
public:
    Box(double l, double w, double h) : length(l), width(w), height(h) {}
    double calculateVolume() const override {
        return length * width * height;
    }
};

// Derived Class: Cylinder
class Cylinder : public Container {
private:
    double radius, height;
public:
    Cylinder(double r, double h) : radius(r), height(h) {}
    double calculateVolume() const override {
        return 3.14159 * radius * radius * height;
    }
};

// Derived Class: Pyramid
class Pyramid : public Container {
private:
    double baseLength, baseWidth, height;
public:
    Pyramid(double bl, double bw, double h) : baseLength(bl), baseWidth(bw), height(h) {}
    double calculateVolume() const override {
        return (baseLength * baseWidth * height) / 3.0;
    }
};

int main() {
    const int MAX_CONTAINERS = 10;
    Container* warehouse[MAX_CONTAINERS];
    int count = 0;

    warehouse[count++] = new Box(10.0, 5.0, 2.0);
    warehouse[count++] = new Cylinder(3.0, 10.0);
    warehouse[count++] = new Pyramid(6.0, 4.0, 5.0);
    warehouse[count++] = new Box(2.0, 2.0, 2.0);

    double totalVolume = 0.0;

    cout << fixed << setprecision(2);
    cout << "--- Warehouse Inventory (Array Implementation) ---" << endl;

    for (int i = 0; i < count; ++i) {
        double vol = warehouse[i]->calculateVolume();
        totalVolume += vol;
        cout << "Container " << i + 1 << " Volume: " << vol << endl;
    }

    cout << "Total Volume: " << totalVolume << " units^3" << endl;

    for (int i = 0; i < count; ++i) {
        delete warehouse[i];
    }

    return 0;
}