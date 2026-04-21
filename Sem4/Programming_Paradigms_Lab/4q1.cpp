#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char* title;
    int pages;

public:
    // Default Constructor
    Book() {
        title = new char[1];
        title[0] = '\0';
        pages = 0;
    }

    // Parameterized Constructor
    Book(const char* t, int p) {
        title = new char[strlen(t) + 1];
        strcpy(title, t);
        pages = p;
    }

    // Copy Constructor
    Book(const Book& other) {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
        pages = other.pages;
    }

    // Assignment Operator
    Book& operator=(const Book& other) {
        if (this != &other) {
            delete[] title;
            title = new char[strlen(other.title) + 1];
            strcpy(title, other.title);
            pages = other.pages;
        }
        return *this;
    }

    // Destructor
    virtual ~Book() {
        delete[] title;
    }

    virtual void readData() {
        char buffer[100];
        cout << "Enter Title: ";
        cin.ignore();
        cin.getline(buffer, 100);

        delete[] title;
        title = new char[strlen(buffer) + 1];
        strcpy(title, buffer);

        cout << "Enter Pages: ";
        cin >> pages;
    }

    virtual void displayData() const {
        cout << "Title: " << title << " | Pages: " << pages;
    }
};

class EBook : public Book {
private:
    double fileSizeMB;
    char* format;

public:
    // Default Constructor
    EBook() : Book() {
        fileSizeMB = 0.0;
        format = new char[1];
        format[0] = '\0';
    }

    // Parameterized Constructor
    EBook(const char* t, int p, double size, const char* f) : Book(t, p) {
        fileSizeMB = size;
        format = new char[strlen(f) + 1];
        strcpy(format, f);
    }

    // Copy Constructor
    EBook(const EBook& other) : Book(other) {
        fileSizeMB = other.fileSizeMB;
        format = new char[strlen(other.format) + 1];
        strcpy(format, other.format);
    }

    // Assignment Operator
    EBook& operator=(const EBook& other) {
        if (this != &other) {
            Book::operator=(other);
            delete[] format;
            fileSizeMB = other.fileSizeMB;
            format = new char[strlen(other.format) + 1];
            strcpy(format, other.format);
        }
        return *this;
    }

    // Destructor
    ~EBook() {
        delete[] format;
    }

    void readData() override {
        Book::readData();
        cout << "Enter File Size (MB): ";
        cin >> fileSizeMB;

        char buffer[20];
        cout << "Enter Format (PDF/EPUB/etc.): ";
        cin >> buffer;

        delete[] format;
        format = new char[strlen(buffer) + 1];
        strcpy(format, buffer);
    }

    void displayData() const override {
        Book::displayData();
        cout << " | Size: " << fileSizeMB << "MB | Format: " << format << endl;
    }
};

int main() {
    cout << "Book Object: " << endl;
    Book b1("BOOK 1", 180);
    b1.displayData();
    cout << endl << endl;

    cout << "EBook Object: " << endl;
    EBook eb1("EBook", 400, 2.5, "EPUB");
    eb1.displayData();

    cout << "\nDynamic Polymorphism (Base pointer to Derived): " << endl;
    Book* ptr = new EBook("C++ Guide", 500, 15.2, "PDF");
    ptr->displayData(); // Calls EBook's version because of virtual

    cout << "\nAssignment Operator: " << endl;
    EBook eb2;
    eb2 = eb1;
    eb2.displayData();

    delete ptr;
    return 0;
}