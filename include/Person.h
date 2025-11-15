#ifndef Person_H
#define Peron_H
#include <string>
using std :: string ;
class Person{ // this is abstract base class
    protected :
    string name ;
    int age ;
    string gender ; 
    public :
    virtual void inputInfo () = 0 ; //virtual function
    virtual void displayInfo () = 0 ;
};
#endif