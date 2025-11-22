#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>
using std::string;

class Patient : public Person {   // Patient inherits from Person
private:
    int patientID;
    string disease;
    int assignedDoctorID;

public:
    Patient();
    // Overridden methods
    void inputInfo() override;
    void displayInfo() const override;   // MUST be const

    // Getters
    int getPatientID() const;
    int getAssignedDoctorID() const;

    // Setter
    void setAssignmentDoctorID(int id);

    // File handling
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif

