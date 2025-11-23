#ifndef PERSON_H
#define PERSON_H

#include <string>
using std::string;

// Abstract base class
class Person {
protected:
    string name;//Name of anyone including doctor , patient.
    int age;
    string gender;

public:
    virtual void inputInfo() = 0;          // pure virtual
    virtual void displayInfo() const = 0;  // MUST be const
};

#endif
