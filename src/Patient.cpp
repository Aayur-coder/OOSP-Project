#include "../include/Patient.h"
#include <iostream>
#include <sstream>     
using namespace std;

 Patient::Patient() {
    patientID = 0;
    assignedDoctorID = 0;
    disease = "";
}

 void Patient::inputInfo() {
    cout << "\nEnter Patient ID: ";
    cin >> patientID;
    cin.ignore();    

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Disease/Problem: ";
    getline(cin, disease);

    cout << "Assigned Doctor ID (enter 0 if none): ";
    cin >> assignedDoctorID;
}

 void Patient::displayInfo() const{
    cout << "\n--- Patient Details ---\n";
    cout << "Patient ID: " << patientID << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "Disease: " << disease << "\n";
    cout << "Assigned Doctor ID: " << assignedDoctorID << "\n";
}

 int Patient::getPatientID() const {
    return patientID;
}

 int Patient::getAssignedDoctorID() const {
    return assignedDoctorID;
}

 void Patient::setAssignmentDoctorID(int id) {
    assignedDoctorID = id;
}

 string Patient::toFileString() const {
    stringstream ss;
    ss << patientID << "|" << name << "|" << age << "|" << gender
       << "|" << disease << "|" << assignedDoctorID;
    return ss.str();
}

 void Patient::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    patientID = stoi(token);

    getline(ss, name, '|');

    getline(ss, token, '|');
    age = stoi(token);

    getline(ss, gender, '|');
    getline(ss, disease, '|');

    getline(ss, token, '|');
    assignedDoctorID = stoi(token);
}



