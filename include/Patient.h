#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>
using std::string;

class Patient : public Person {
private:
    int patientID;
    string disease;
    int assignedDoctorID;   
public:

    void inputInfo() override;       
    void displayInfo() override;    

    int getPatientID() const;
    int getAssignedDoctorID() const;


    void setAssignedDoctorID(int id);

    string toFileString() const;
    void fromFileString(const string& line);
};

#endif



