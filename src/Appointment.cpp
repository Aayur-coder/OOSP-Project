#include "../include/Appointment.h"
#include <iostream>
#include <sstream>
using namespace std;

Appointment::Appointment() {
    appointmentID = 0;
    doctorID = 0;
    patientID = 0;
    date = "";
}

Appointment::Appointment(int apid, int did, int pid, const string& d) {
    appointmentID = apid;
    doctorID = did;
    patientID = pid;
    date = d;
}

void Appointment::scheduleAppointment() {
    cout << "\nEnter Appointment ID: ";
    cin >> appointmentID;

    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    cout << "Enter Patient ID: ";
    cin >> patientID;

    cin.ignore();  
    cout << "Enter Appointment Date and Time (example: 2025-11-20 10:00): ";
    getline(cin, date);
}

void Appointment::displayAppointment() const {
    cout << "\n--- Appointment Details ---";
    cout << "\nAppointment ID: " << appointmentID;
    cout << "\nDoctor ID: " << doctorID;
    cout << "\nPatient ID: " << patientID;
    cout << "\nDate & Time: " << date << "\n";
}

int Appointment::getAppointmentID() const { return appointmentID; }
int Appointment::getDoctorID() const { return doctorID; }
int Appointment::getPatientID() const { return patientID; }

 string Appointment::toFileString() const {
    stringstream ss;
    ss << appointmentID << "|" << doctorID << "|" << patientID << "|" << date;
    return ss.str();
}

 void Appointment::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    appointmentID = stoi(token);

    getline(ss, token, '|');
    doctorID = stoi(token);

    getline(ss, token, '|');
    patientID = stoi(token);

    getline(ss, date, '|');
}
