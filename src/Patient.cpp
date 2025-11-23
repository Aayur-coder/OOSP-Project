#include "../include/Patient.h"
#include <iostream>
#include <sstream> 
#include <limits> // Added for safety with ignore, although simple ignore is used
using namespace std;

// Constructor
Patient::Patient() {
    patientID = 0;
    assignedDoctorID = 0;
    // Note: 'disease' is a direct member in your code, not inherited from Person.
    // If 'disease' should be protected in Patient, it needs to be declared in Patient.h.
    disease = "";
}

// Input function (Removed manual ID and Assigned Doctor ID inputs)
void Patient::inputInfo() {
    // 1. CLEAR BUFFER: Clears the newline left by the previous integer input (ID choice) 
    // in HospitalManagement::addPatient(), ensuring getline(name) doesn't skip.
    std::cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    // Use cin >> for integer input
    cin >> age;
    // Clears the newline left by cin >> age, so getline(gender) works correctly
    std::cin.ignore(); 

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Disease/Problem: ";
    getline(cin, disease);
    
    // REMOVED: Assigned Doctor ID input, as this is now handled by the 
    // HospitalManagement::addPatient() validation loop.
}

// Setter for Patient ID (Used by HospitalManagement::addPatient)
void Patient::setPatientID(int id) {
    patientID = id;
}

// Display function
void Patient::displayInfo() const{
    cout << "\n--- Patient Details ---\n";
    cout << "Patient ID: " << patientID << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "Disease: " << disease << "\n";
    cout << "Assigned Doctor ID: " << assignedDoctorID << "\n";
}

// Getter for Patient ID
int Patient::getPatientID() const {
    return patientID;
}

// Getter for Assigned Doctor ID
int Patient::getAssignedDoctorID() const {
    return assignedDoctorID;
}

// Setter for Assigned Doctor ID (Used by HospitalManagement for validation)
void Patient::setAssignmentDoctorID(int id) {
    assignedDoctorID = id;
}

// Serialization (Object to File String)
string Patient::toFileString() const {
    stringstream ss;
    ss << patientID << "|" << name << "|" << age << "|" << gender
       << "|" << disease << "|" << assignedDoctorID;
    return ss.str();
}

// Deserialization (File String to Object)
void Patient::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    // 1. Patient ID
    getline(ss, token, '|');
    patientID = stoi(token);

    // 2. Name
    getline(ss, name, '|');

    // 3. Age
    getline(ss, token, '|');
    age = stoi(token);

    // 4. Gender
    getline(ss, gender, '|');
    
    // 5. Disease/Problem
    getline(ss, disease, '|');

    // 6. Assigned Doctor ID
    getline(ss, token, '|');
    assignedDoctorID = stoi(token);
}