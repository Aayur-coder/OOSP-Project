#ifndef HOSPITALMANAGEMENT_H
#define HOSPITALMANAGEMENT_H
//included all important header files .
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include <vector>
#include <string>
#include <map>
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
    int findSmallestAvailableID() const;
    int findSmallestAvailablePatientID() const;
    
    
    public : 
    HospitalManagement () ;
       
    void mainMenu();

   
    void manageDoctors();
    void addDoctor();
    void listDoctors() const;
    void searchDoctorByID() const;
    void deleteDoctorByID();
    bool isDoctorCaseloadFull(int doctorID, int maxPatients = 3) const;

    
    void managePatients();
    void addPatient();
    void listPatients() const;
    void searchPatientByID() const;
    void assignDoctorToPatient();
    void deletePatientByID();

   
    void manageAppointments();
    void createAppointment();
    void listAppointments() const;

    
    void saveDoctorsToFile(const string& filename) const;
    void loadDoctorsFromFile(const string& filename); // Must update nextDoctorID here

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
