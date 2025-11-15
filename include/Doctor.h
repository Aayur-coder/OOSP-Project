#ifndef DOCTOR_H
#define DOCTOR_H
#include "Person.h"
#include <string>
using std::string;
class Doctor : public Person {
private:
    int doctorID;
    string specialization;
    string availability;
public:
    void inputInfo() override;     
    void displayInfo() override;
    int getDoctorID() const;
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif
