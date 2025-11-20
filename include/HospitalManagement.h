#ifndef HOSPITALMANAGEMENT_H
#define HOSPITALMANAGEMENT_H

#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class HospitalManagement {
    private :
    vector <Doctor> doctors ;
    vector <Patient> patients ;
    vector <Appointment> appointments ;

    int nextDoctorID ;
    int nextPatientID ;
    int nextAppointmentID ;
    
    public : 
    HospitalManagement () ;
       
    void mainMenu();

   
    void manageDoctors();
    void addDoctor();
    void listDoctors() const;
    void searchDoctorByID() const;

    
    void managePatients();
    void addPatient();
    void listPatients() const;
    void searchPatientByID() const;
    void assignDoctorToPatient();

   
    void manageAppointments();
    void createAppointment();
    void listAppointments() const;

    
    void saveDoctorsToFile(const string& filename) const;
    void loadDoctorsFromFile(const string& filename);

    void savePatientsToFile(const string& filename) const;
    void loadPatientsFromFile(const string& filename);

    void saveAppointmentsToFile(const string& filename) const;
    void loadAppointmentsFromFile(const string& filename);


    template <typename T>
    void displayList(const vector<T>& list) const {
        for (const auto& item : list) {
            item.displayInfo();  
        }
    }
};
#endif