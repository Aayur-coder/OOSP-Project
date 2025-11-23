#include "../include/Patient.h"
#include <iostream>
#include <sstream> 
#include <limits> 
using namespace std;

Patient::Patient() {//Constructor.
    patientID = 0;
    assignedDoctorID = 0;
    disease = "";
}

void Patient::inputInfo() {
    std::cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    std::cin.ignore(); 

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Disease/Problem: ";
    getline(cin, disease);
}

void Patient::setPatientID(int id) {
    patientID = id;
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
