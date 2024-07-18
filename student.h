#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
private:
    int admissionNumber;
    char studentName[50];
    int borrowedBookID;
    int tokens;

public:
    Student();
    void createStudent();
    void displayStudent() const;
    void listStudents() const;
    void setToken(int token);
    void resetToken();
    int getBorrowedBookID() const;
    int getAdmissionNumber() const;
};

#endif
