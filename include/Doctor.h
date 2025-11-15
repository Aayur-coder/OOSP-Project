#ifndef DOCTOR_H
#define DOCTOR_H
<<<<<<< HEAD

#include "Person.h"
#include <string>
using std::string;

// Doctor class inherits from Person
=======
#include "Person.h"
#include <string>
using std::string;
>>>>>>> 1c9f49c4f25fa622da184ff5d1e36aa9a472daba
class Doctor : public Person {
private:
    int doctorID;
    string specialization;
    string availability;
<<<<<<< HEAD

public:
   
    void inputInfo() override;       
    void displayInfo() override;     

    int getDoctorID() const;

=======
public:
    void inputInfo() override;     
    void displayInfo() override;
    int getDoctorID() const;
>>>>>>> 1c9f49c4f25fa622da184ff5d1e36aa9a472daba
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif
