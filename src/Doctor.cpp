#include "../include/Doctor.h"
#include <iostream>
#include <sstream>   
using namespace std;

// Constructor
Doctor::Doctor() {
    doctorID = 0;
    specialization = "";
    availability = "";
}

// Input function (ID input removed, as management class handles it)
void Doctor::inputInfo() {
    // Note: Removed lines for Doctor ID input.
    // The ID is now set by the HospitalManagement::addDoctor method via setDoctorID().

    // Clear buffer after previous cin operation (e.g., from menu choice)
    cin.ignore();  
    
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    // Use >> for age
    cin >> age;
    // Clear buffer after cin >> age
    cin.ignore(); 

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Specialization: ";
    getline(cin, specialization);

    cout << "Enter Availability (e.g., 9AM-5PM): ";
    getline(cin, availability);
}

// Display function
void Doctor::displayInfo() const {
    cout << "\n--- Doctor Details ---\n";
    cout << "Doctor ID: " << doctorID << "\n";
    // Inherited from Person:
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    // Doctor members:
    cout << "Specialization: " << specialization << "\n";
    cout << "Availability: " << availability << "\n";
}

// Getter for ID
int Doctor::getDoctorID() const {
    return doctorID;
}

// Setter for ID (Added for HospitalManagement to assign ID)
void Doctor::setDoctorID(int id) {
    doctorID = id;
}

// Serialization
string Doctor::toFileString() const {
    stringstream ss;
    ss << doctorID << "|" << name << "|" << age << "|" << gender
       << "|" << specialization << "|" << availability;
    return ss.str();
}

// Deserialization
void Doctor::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    doctorID = stoi(token);

    getline(ss, name, '|');

    getline(ss, token, '|');
    age = stoi(token);

    getline(ss, gender, '|');
    getline(ss, specialization, '|');
    getline(ss, availability, '|');
}

// Ensure there are NO extra braces or code after this line.