#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>
using std::string;

class Patient : public Person {   // Patient inherits from Person
private:
    int patientID;//Unique for every patient
    string disease;
    int assignedDoctorID;

public:
    Patient();
    void inputInfo() override;
    void displayInfo() const override;  

    int getPatientID() const;
    int getAssignedDoctorID() const;

    void setAssignmentDoctorID(int id);
    void setPatientID(int id);

    string toFileString() const;
    void fromFileString(const string& line);
};

#endif

