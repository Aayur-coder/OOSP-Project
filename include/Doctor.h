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
    // Constructor
    Doctor();

    // Overridden functions (with const!)
    void inputInfo() override;
    void displayInfo() const override;

    // Getter
    int getDoctorID() const;

    // File handling helpers
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif
