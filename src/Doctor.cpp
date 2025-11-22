#include "../include/Doctor.h"
#include <iostream>
#include <sstream>   
using namespace std;
Doctor::Doctor() {
    doctorID = 0;
    specialization = "";
    availability = "";
}
void Doctor::inputInfo() {
    cout << "\nEnter Doctor ID: ";
    cin >> doctorID;
    cin.ignore();  // clear buffer

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Specialization: ";
    getline(cin, specialization);

    cout << "Enter Availability (e.g., 9AM-5PM): ";
    getline(cin, availability);
}
void Doctor::displayInfo() const {
    cout << "\n--- Doctor Details ---\n";
    cout << "Doctor ID: " << doctorID << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "Specialization: " << specialization << "\n";
    cout << "Availability: " << availability << "\n";
}
int Doctor::getDoctorID() const {
    return doctorID;
}
string Doctor::toFileString() const {
    stringstream ss;
    ss << doctorID << "|" << name << "|" << age << "|" << gender
       << "|" << specialization << "|" << availability;
    return ss.str();
}
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