#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <string>
using std::string;

// Doctor class inherits from Person
class Doctor : public Person {
private:
    int doctorID;
    // 📢 THESE LINES MUST BE PRESENT IN DOCTOR.H:
    string specialization; 
    string availability;
    // ---------------------------------------------

public:
    Doctor();

    void inputInfo() override;
    void displayInfo() const override;

    int getDoctorID() const;
    void setDoctorID(int id); 

    string toFileString() const;
    void fromFileString(const string& line);
};

#endif