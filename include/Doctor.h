#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <string>
using std::string;

// Doctor class inherits from Person
class Doctor : public Person {
private:
    int doctorID;
    string specialization;
    string availability;

public:
    // Function declarations
    void inputInfo() override;       // Polymorphism
    void displayInfo() override;     // Polymorphism

    // Getter function
    int getDoctorID() const;

    // For file handling (later in .cpp)
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif
