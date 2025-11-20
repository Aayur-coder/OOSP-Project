#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
using  std :: string ;
class Appointment {
    int appointmentID ;
    int doctorID ; // an unique number for identification of the doctor.
    int patientID ; // unique id for different patients.
    string date ;
public : 
    Appointment () ;
    Appointment (int apid , int did , int pid , const string& d) ;
    void scheduleAppointment();
    void displayAppointment() const;

    int getAppointmentID() const;
    int getDoctorID() const;
    int getPatientID() const;


    string toFileString() const;
    void fromFileString(const string& line);
};
#endif