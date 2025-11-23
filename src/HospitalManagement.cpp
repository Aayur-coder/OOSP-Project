#include "../include/HospitalManagement.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits> // Required for numeric_limits
#include <algorithm>
using namespace std;

// In HospitalManagement.cpp

HospitalManagement::HospitalManagement() {
    nextDoctorID = 101; // Default starting ID if no file exists
    nextPatientID = 201; 
    nextAppointmentID = 1;
    
    loadDoctorsFromFile("doctors.txt");
    loadPatientsFromFile("patients.txt");
    loadAppointmentsFromFile("appointments.txt");
}

// In HospitalManagement.cpp

void HospitalManagement::loadDoctorsFromFile(const string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        // KEEP: nextDoctorID is already 101 from the constructor
        return; 
    }

    doctors.clear();

    std::string line;
    int maxID = 100;

    int doctorCount = 0; // NEW: Local counter to track doctors loaded

    while (std::getline(inputFile, line)) {
        Doctor tempDoctor;
        tempDoctor.fromFileString(line);
        doctors.push_back(tempDoctor);

        if (tempDoctor.getDoctorID() > maxID) {
            maxID = tempDoctor.getDoctorID();
        }
        doctorCount++; // Increment count
    }

    inputFile.close();
    
    // Set the next ID to be one greater than the maximum ID found.
    nextDoctorID = maxID + 1;
    
    // NEW: Store the loading message in a member variable, or pass the count/maxID 
    // to the constructor for a one-time startup load and output, OR just handle the output 
    // inside the management function.

    // OPTION 1: Keep only the logic, remove the output entirely
    // REMOVED: std::cout << "Loaded " << doctors.size() << " doctors. Next Doctor ID will be: " << nextDoctorID << "\n";
}

// In HospitalManagement.cpp

// In HospitalManagement.cpp

void HospitalManagement::addDoctor() {
    int smallestID = findSmallestAvailableID();
    int chosenID = 0;
    int choice;
    
    // --- ID SELECTION PROMPT ---
    cout << "\n--- ID Assignment Options ---\n";
    
    // Option 1: Reuse smallest ID if a gap exists
    if (smallestID < nextDoctorID) {
        cout << "1. Use Smallest Available ID (Reuse gap): " << smallestID << "\n";
    }
    
    // Option 2: Use next sequential ID
    cout << "2. Use Latest Sequential ID: " << nextDoctorID << "\n";
    
    cout << "Enter your choice (1 or 2): ";
    
    // --- Input Validation and Assignment ---
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

    // --- Core Logic ---
    
    // Check if the chosen ID needs to increment the sequential counter
    bool incrementNextID = (chosenID == nextDoctorID);

    // 1. Assign the chosen ID
    Doctor newDoctor;
    newDoctor.setDoctorID(chosenID); 

    // 2. Prompt user for other details
    newDoctor.inputInfo();

    // 3. Add to the list
    doctors.push_back(newDoctor);

    // 4. Update nextDoctorID ONLY if we used the sequential ID
    if (incrementNextID) {
        nextDoctorID++;
    } 
    
    cout << "\nDoctor added successfully! Assigning Doctor ID: " << newDoctor.getDoctorID() << "\n";
    
    // Save changes
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

// In HospitalManagement.cpp

// NOTE: Requires #include <algorithm>

int HospitalManagement::findSmallestAvailablePatientID() const {
    // Start searching from the base patient ID (201, as defined in constructor)
    for (int i = 201; i < nextPatientID; ++i) {
        bool idFound = false;
        
        // Check if ID 'i' exists in the current patients vector
        for (const auto& patient : patients) {
            if (patient.getPatientID() == i) {
                idFound = true;
                break;
            }
        }

        // If ID 'i' was NOT found, it's the smallest available gap.
        if (!idFound) {
            return i;
        }
    }
    
    // If no gap is found, return the next sequential ID
    return nextPatientID;
}

// In HospitalManagement.cpp

void HospitalManagement::deletePatientByID() {
    int idToDelete;
    cout << "\nEnter Patient ID to delete: ";
    if (!(cin >> idToDelete)) {
        cout << "Invalid input. Please enter a valid numerical ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // Use std::remove_if to find and move the elements to be deleted.
    auto oldSize = patients.size();
    
    patients.erase(
        std::remove_if(patients.begin(), patients.end(),
            [idToDelete](const Patient& p) {
                return p.getPatientID() == idToDelete;
            }),
        patients.end());

    // Check if the size changed
    if (patients.size() < oldSize) {
        cout << "\nPatient with ID " << idToDelete << " deleted successfully!\n";
        savePatientsToFile("patients.txt"); 
    } else {
        cout << "\nError: Patient ID " << idToDelete << " not found!\n";
    }
}

// In HospitalManagement.cpp (Make sure this function now uses the new logic)

// In HospitalManagement.cpp (Revised addPatient)

void HospitalManagement::addPatient() {
    // --- ID SELECTION LOGIC START ---
    
    // 1. Declare variables at the top of the scope
    int smallestID = findSmallestAvailablePatientID();
    int latestID = nextPatientID;
    int chosenID = 0;
    int choice;
    
    // --- ID SELECTION PROMPT ---
    cout << "\n--- Patient ID Assignment Options ---\n";
    
    // Option 1: Reuse smallest ID if a gap exists
    if (smallestID < latestID) {
        cout << "1. Use Smallest Available ID (Reuse gap): " << smallestID << "\n";
    }
    
    // Option 2: Use next sequential ID
    cout << "2. Use Latest Sequential ID: " << latestID << "\n";
    
    cout << "Enter your choice (1 or 2): ";
    
    // --- Input Validation and Assignment ---
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
    
    // Check if the chosen ID needs to increment the sequential counter
    bool incrementNextID = (chosenID == latestID);
    
    // --- ID SELECTION LOGIC END ---

    
    // --- New Core Patient Object ---
    Patient newPatient;
    newPatient.setPatientID(chosenID); 

    // 1. Prompt user for general details (Name, Age, Disease, etc.)
    //    We assume Patient::inputInfo() now only gets basic info (NOT Doctor ID)
    newPatient.inputInfo(); // Assume this fills Name, Age, Gender, Disease/Problem

    // --- DOCTOR ASSIGNMENT AND VALIDATION LOOP ---
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
        
        // 2. Check if Doctor exists
        doctorExists = false;
        for (const auto& d : doctors) {
            if (d.getDoctorID() == did) {
                doctorExists = true;
                break;
            }
        }
        
        if (!doctorExists) {
            cout << "\nError: Doctor ID " << did << " does not exist. Please try again.\n";
            // Important: Clear the input buffer before asking for the ID again in the loop
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        // 3. Check Caseload Limit (THE NEW CONSTRAINT: max 3 patients)
        if (isDoctorCaseloadFull(did, 3)) {
            cout << "\nError: Doctor ID " << did << " already handles the maximum of 3 patients. Choose another doctor.\n";
            // Important: Clear the input buffer before asking for the ID again in the loop
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Loop continues, asks for ID again
        }

        // 4. Successful Assignment
        newPatient.setAssignmentDoctorID(did);
        assignmentSuccessful = true;
    }

    // 5. Add to the list
    patients.push_back(newPatient);

    // 6. Update nextPatientID ONLY if we used the sequential ID
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
    displayList(patients);   // TEMPLATE FUNCTION
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
    //to check if patient exists.
    bool patientFound = false;
    for (auto& p : patients) {
        if (p.getPatientID() == pid) {
            patientFound = true;

            // Check if doctor exists
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

// In HospitalManagement.cpp

void HospitalManagement::loadPatientsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    
    int maxID = 200; // Start at one less than the minimum ID (201)
    
    while (getline(file, line)) {
        Patient p;
        p.fromFileString(line);
        patients.push_back(p);
        
        // --- NEW LOGIC TO FIND MAX ID ---
        if (p.getPatientID() > maxID) {
            maxID = p.getPatientID();
        }
    }
    
    // --- NEW LOGIC TO SET NEXT ID ---
    nextPatientID = maxID + 1;
    // You might want to print a status message here too.
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

// In HospitalManagement.cpp

// New function to check the limit
bool HospitalManagement::isDoctorCaseloadFull(int doctorID, int maxPatients) const {
    if (doctorID == 0) {
        return false; // No limit if no doctor is assigned
    }
    
    int patientCount = 0;
    
    // Iterate through all patients
    for (const auto& p : patients) {
        if (p.getAssignedDoctorID() == doctorID) {
            patientCount++;
        }
    }
    
    // Check if the current count is already at or above the limit
    return patientCount >= maxPatients;
}
// This function is called when the user selects option 1 (Doctors)
// In HospitalManagement.cpp

void HospitalManagement::manageDoctors() {
    int choice;
    
    // Output moved here as per previous request
    std::cout << "Loaded " << doctors.size() << " doctors. Next Doctor ID will be: " << nextDoctorID << "\n";
    
    do {
        // --- Doctor Menu Display ---
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. Add Doctor\n";
        cout << "2. List Doctors\n";
        cout << "3. Search Doctor\n";
        // --- NEW LINE (Option 4) ---
        cout << "4. Delete Doctor\n"; 
        // --- UPDATED LINE (Option 5) ---
        cout << "5. Back\n";
        cout << "Enter choice: ";
        
        // --- Input Validation ---
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
            // --- NEW CASE ---
            case 4:
                deleteDoctorByID(); // Call the new function
                break;
            // --- UPDATED EXIT CASE ---
            case 5:
                cout << "Returning to Main Menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        
    } while (choice != 5); // Loop now continues until choice 5 (Back)
    
    // Best practice: Save changes after modifications
    saveDoctorsToFile("doctors.txt"); 
}

// In HospitalManagement.cpp

void HospitalManagement::managePatients() {
    int choice;

    // Load message (similar to doctors)
    std::cout << "Loaded " << patients.size() << " patients. Next Patient ID will be: " << nextPatientID << "\n";

    do {
        cout << "\n--- Patient Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. List Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Delete Patient\n"; // --- NEW OPTION ---
        cout << "5. Assign Doctor\n";
        cout << "6. Back\n"; // --- UPDATED BACK OPTION ---
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
                deletePatientByID(); // --- NEW CALL ---
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


// In HospitalManagement.cpp
// In HospitalManagement.cpp (Ensure #include <algorithm> is present)

// Helper to find the lowest unused ID (the "gap")
int HospitalManagement::findSmallestAvailableID() const {
    // Start searching from the base ID
    for (int i = 101; i < nextDoctorID; ++i) {
        bool idFound = false;
        
        // Check if ID 'i' exists in the current doctors vector
        for (const auto& doctor : doctors) {
            if (doctor.getDoctorID() == i) {
                idFound = true;
                break;
            }
        }

        // If ID 'i' was NOT found, it's the smallest available gap.
        if (!idFound) {
            return i;
        }
    }
    
    // If no gap is found, return the next sequential ID (which is nextDoctorID)
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

    // Use std::remove_if to find and move the elements to be kept to the front.
    // The lambda function checks if the current doctor's ID matches the ID to delete.
    auto oldSize = doctors.size();
    
    // 

    doctors.erase(
        std::remove_if(doctors.begin(), doctors.end(),
            [idToDelete](const Doctor& d) {
                return d.getDoctorID() == idToDelete;
            }),
        doctors.end());

    // Check if the size changed
    if (doctors.size() < oldSize) {
        cout << "\nDoctor with ID " << idToDelete << " deleted successfully!\n";
        // Update the next ID count in case the deleted one was the highest
        // (Though technically deleting the max ID is a special case, the next added 
        // doctor will still get the next highest available ID in this implementation.)
        // saveDoctorsToFile("doctors.txt"); // Will be called when manageDoctors() exits
    } else {
        cout << "\nError: Doctor ID " << idToDelete << " not found!\n";
    }
}