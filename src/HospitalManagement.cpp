#include "../include/HospitalManagement.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits> 
#include <algorithm>
using namespace std;


HospitalManagement::HospitalManagement() {
    nextDoctorID = 101; 
    nextPatientID = 201; 
    nextAppointmentID = 1;
    
    loadDoctorsFromFile("doctors.txt");
    loadPatientsFromFile("patients.txt");
    loadAppointmentsFromFile("appointments.txt");
}


void HospitalManagement::loadDoctorsFromFile(const string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        return; 
    }

    doctors.clear();

    std::string line;
    int maxID = 100;

    int doctorCount = 0; 

    while (std::getline(inputFile, line)) {
        Doctor tempDoctor;
        tempDoctor.fromFileString(line);
        doctors.push_back(tempDoctor);

        if (tempDoctor.getDoctorID() > maxID) {
            maxID = tempDoctor.getDoctorID();
        }
        doctorCount++; 
    }

    inputFile.close();
    
    nextDoctorID = maxID + 1;
    
    
}



void HospitalManagement::addDoctor() {
    int smallestID = findSmallestAvailableID();
    int chosenID = 0;
    int choice;
    
    cout << "\n--- ID Assignment Options ---\n";
    
    if (smallestID < nextDoctorID) {
        cout << "1. Use Smallest Available ID (Reuse gap): " << smallestID << "\n";
    }
    
    cout << "2. Use Latest Sequential ID: " << nextDoctorID << "\n";
    
    cout << "Enter your choice (1 or 2): ";
    
    if (!(cin >> choice)) {
        cout << "Invalid input. Returning to Doctor Menu.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (choice == 1 && smallestID < nextDoctorID) {
        chosenID = smallestID;
    } else if (choice == 2) {
        chosenID = nextDoctorID;
    } else {
        cout << "Invalid option selected. Defaulting to Latest Sequential ID (" << nextDoctorID << ").\n";
        chosenID = nextDoctorID;
    }

    
    bool incrementNextID = (chosenID == nextDoctorID);

    Doctor newDoctor;
    newDoctor.setDoctorID(chosenID); 

    newDoctor.inputInfo();

    doctors.push_back(newDoctor);

    if (incrementNextID) {
        nextDoctorID++;
    } 
    
    cout << "\nDoctor added successfully! Assigning Doctor ID: " << newDoctor.getDoctorID() << "\n";
    
    saveDoctorsToFile("doctors.txt"); 
}
void HospitalManagement::listDoctors() const {
    if (doctors.empty()) {
        cout << "\nNo doctors available.\n";
        return;
    }
    displayList(doctors);   
}

void HospitalManagement::searchDoctorByID() const {
    cout << "\nEnter Doctor ID: ";
    int id;
    cin >> id;

    for (const auto& d : doctors) {
        if (d.getDoctorID() == id) {
            d.displayInfo();
            return;
        }
    }
    cout << "\nDoctor not found!\n";
}



int HospitalManagement::findSmallestAvailablePatientID() const {
    for (int i = 201; i < nextPatientID; ++i) {
        bool idFound = false;
        
        for (const auto& patient : patients) {
            if (patient.getPatientID() == i) {
                idFound = true;
                break;
            }
        }

        if (!idFound) {
            return i;
        }
    }
    
    return nextPatientID;
}


void HospitalManagement::deletePatientByID() {
    int idToDelete;
    cout << "\nEnter Patient ID to delete: ";
    if (!(cin >> idToDelete)) {
        cout << "Invalid input. Please enter a valid numerical ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto oldSize = patients.size();
    
    patients.erase(
        std::remove_if(patients.begin(), patients.end(),
            [idToDelete](const Patient& p) {
                return p.getPatientID() == idToDelete;
            }),
        patients.end());

    if (patients.size() < oldSize) {
        cout << "\nPatient with ID " << idToDelete << " deleted successfully!\n";
        savePatientsToFile("patients.txt"); 
    } else {
        cout << "\nError: Patient ID " << idToDelete << " not found!\n";
    }
}



void HospitalManagement::addPatient() {
    
    int smallestID = findSmallestAvailablePatientID();
    int latestID = nextPatientID;
    int chosenID = 0;
    int choice;
    
    cout << "\n--- Patient ID Assignment Options ---\n";
    
    if (smallestID < latestID) {
        cout << "1. Use Smallest Available ID (Reuse gap): " << smallestID << "\n";
    }
    
    cout << "2. Use Latest Sequential ID: " << latestID << "\n";
    
    cout << "Enter your choice (1 or 2): ";
    
    if (!(cin >> choice)) {
        cout << "Invalid input. Cancelling patient addition.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (choice == 1 && smallestID < latestID) {
        chosenID = smallestID;
    } else if (choice == 2) {
        chosenID = latestID;
    } else {
        cout << "Invalid option selected. Defaulting to Latest Sequential ID (" << latestID << ").\n";
        chosenID = latestID;
    }
    
    bool incrementNextID = (chosenID == latestID);
    

    
    Patient newPatient;
    newPatient.setPatientID(chosenID); 

    newPatient.inputInfo(); 
    int did = 0;
    bool doctorExists = false;
    bool assignmentSuccessful = false;
    
    while (!assignmentSuccessful) {
        cout << "Assigned Doctor ID (enter 0 if none): ";
        if (!(cin >> did)) {
            cout << "Invalid input. Cancelling patient addition.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (did == 0) {
            newPatient.setAssignmentDoctorID(0);
            assignmentSuccessful = true;
            break;
        }
        
        doctorExists = false;
        for (const auto& d : doctors) {
            if (d.getDoctorID() == did) {
                doctorExists = true;
                break;
            }
        }
        
        if (!doctorExists) {
            cout << "\nError: Doctor ID " << did << " does not exist. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        if (isDoctorCaseloadFull(did, 3)) {
            cout << "\nError: Doctor ID " << did << " already handles the maximum of 3 patients. Choose another doctor.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        newPatient.setAssignmentDoctorID(did);
        assignmentSuccessful = true;
    }

    patients.push_back(newPatient);

    if (incrementNextID) {
        nextPatientID++;
    } 
    
    cout << "\nPatient added successfully! Assigning Patient ID: " << newPatient.getPatientID() << "\n";
    savePatientsToFile("patients.txt"); 
}

void HospitalManagement::listPatients() const {
    if (patients.empty()) {
        cout << "\nNo patients found.\n";
        return;
    }
    displayList(patients);   
}

void HospitalManagement::searchPatientByID() const {
    cout << "\nEnter Patient ID: ";
    int id;
    cin >> id;

    for (const auto& p : patients) {
        if (p.getPatientID() == id) {
            p.displayInfo();
            return;
        }
    }
    cout << "\nPatient not found!\n";
}

void HospitalManagement::assignDoctorToPatient() {
    cout << "\nEnter Patient ID: ";
    int pid;
    cin >> pid;

    cout << "Enter Doctor ID: ";
    int did;
    cin >> did;
    bool patientFound = false;
    for (auto& p : patients) {
        if (p.getPatientID() == pid) {
            patientFound = true;

            bool doctorFound = false;
            for (const auto& d : doctors) {
                if (d.getDoctorID() == did) {
                    doctorFound = true;
                    break;
                }
            }

            if (!doctorFound) {
                cout << "\nError: Doctor ID does not exist!\n";
                return;
            }

            p.setAssignmentDoctorID(did);
            savePatientsToFile("patients.txt");
            cout << "\nDoctor assigned successfully!\n";
            return;
        }
    }

    if (!patientFound) cout << "\nError: Patient ID does not exist!\n";
}


void HospitalManagement::createAppointment() {
    cout << "\nEnter Doctor ID: ";
    int did;
    cin >> did;

    cout << "Enter Patient ID: ";
    int pid;
    cin >> pid;

    bool doctorExists = false, patientExists = false;

    for (auto& d : doctors)
        if (d.getDoctorID() == did) doctorExists = true;

    for (auto& p : patients)
        if (p.getPatientID() == pid) patientExists = true;

    if (!doctorExists || !patientExists) {
        cout << "\nError: Invalid doctor or patient ID!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Appointment Date and Time: ";
    string datetime;
    getline(cin, datetime);

    Appointment a(nextAppointmentID, did, pid, datetime);
    appointments.push_back(a);
    nextAppointmentID++;

    saveAppointmentsToFile("appointments.txt");
    cout << "\nAppointment created successfully!\n";
}

void HospitalManagement::listAppointments() const {
    if (appointments.empty()) {
        cout << "\nNo appointments found.\n";
        return;
    }
    for (const auto& a : appointments)
        a.displayAppointment();
}


void HospitalManagement::saveDoctorsToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& d : doctors) {
        file << d.toFileString() << "\n";
    }
}


void HospitalManagement::savePatientsToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& p : patients) {
        file << p.toFileString() << "\n";
    }
}


void HospitalManagement::loadPatientsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    
    int maxID = 200; 
    
    while (getline(file, line)) {
        Patient p;
        p.fromFileString(line);
        patients.push_back(p);
        
        if (p.getPatientID() > maxID) {
            maxID = p.getPatientID();
        }
    }
    
    nextPatientID = maxID + 1;
}

void HospitalManagement::saveAppointmentsToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& a : appointments) {
        file << a.toFileString() << "\n";
    }
}

void HospitalManagement::loadAppointmentsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Appointment a;
        a.fromFileString(line);
        appointments.push_back(a);
    }
}


bool HospitalManagement::isDoctorCaseloadFull(int doctorID, int maxPatients) const {
    if (doctorID == 0) {
        return false; 
    }
    
    int patientCount = 0;
    
    for (const auto& p : patients) {
        if (p.getAssignedDoctorID() == doctorID) {
            patientCount++;
        }
    }
    
    return patientCount >= maxPatients;
}

void HospitalManagement::manageDoctors() {
    int choice;
    
    std::cout << "Loaded " << doctors.size() << " doctors. Next Doctor ID will be: " << nextDoctorID << "\n";
    
    do {
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. Add Doctor\n";
        cout << "2. List Doctors\n";
        cout << "3. Search Doctor\n";
        cout << "4. Delete Doctor\n"; 
        cout << "5. Back\n";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cout << "Invalid choice! Please enter a number (1-5).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; 
            continue; 
        }
        
        switch (choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                listDoctors();
                break;
            case 3:
                searchDoctorByID();
                break;
            case 4:
                deleteDoctorByID(); 
                break;
            case 5:
                cout << "Returning to Main Menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        
    } while (choice != 5); 
    
    saveDoctorsToFile("doctors.txt"); 
}


void HospitalManagement::managePatients() {
    int choice;

    std::cout << "Loaded " << patients.size() << " patients. Next Patient ID will be: " << nextPatientID << "\n";

    do {
        cout << "\n--- Patient Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. List Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Delete Patient\n"; 
        cout << "5. Assign Doctor\n";
        cout << "6. Back\n"; 
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice! Please enter a number (1-6).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                listPatients();
                break;
            case 3:
                searchPatientByID();
                break;
            case 4:
                deletePatientByID(); 
                break;
            case 5:
                assignDoctorToPatient();
                break;
            case 6:
                cout << "Returning to Main Menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 6);
}

void HospitalManagement::manageAppointments() {
    int choice;
    do {
        cout << "\n--- Appointment Menu ---\n";
        cout << "1. Create Appointment\n";
        cout << "2. List Appointments\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAppointment(); break;
            case 2: listAppointments(); break;
        }
    } while (choice != 3);
}

void HospitalManagement::mainMenu() {
    int choice;
    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Doctors\n";
        cout << "2. Patients\n";
        cout << "3. Appointments\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manageDoctors(); break;
            case 2: managePatients(); break;
            case 3: manageAppointments(); break;
            case 4: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid choice!\n";
        }

    } while (choice != 4);
}



int HospitalManagement::findSmallestAvailableID() const {
    for (int i = 101; i < nextDoctorID; ++i) {
        bool idFound = false;
        
        for (const auto& doctor : doctors) {
            if (doctor.getDoctorID() == i) {
                idFound = true;
                break;
            }
        }

        if (!idFound) {
            return i;
        }
    }
    
    return nextDoctorID;
}

void HospitalManagement::deleteDoctorByID() {
    int idToDelete;
    cout << "\nEnter Doctor ID to delete: ";
    if (!(cin >> idToDelete)) {
        cout << "Invalid input. Please enter a valid numerical ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto oldSize = doctors.size();
     

    doctors.erase(
        std::remove_if(doctors.begin(), doctors.end(),
            [idToDelete](const Doctor& d) {
                return d.getDoctorID() == idToDelete;
            }),
        doctors.end());

    if (doctors.size() < oldSize) {
        cout << "\nDoctor with ID " << idToDelete << " deleted successfully!\n";

    } else {
        cout << "\nError: Doctor ID " << idToDelete << " not found!\n";
    }
}