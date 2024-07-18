#include "student.h"

Student::Student() : admissionNumber(0), borrowedBookID(0), tokens(0) {
    strcpy(studentName, "");
}

void Student::createStudent() {
    cout << "\nEnter admission number: ";
    cin >> admissionNumber;
    cin.ignore();
    cout << "\nEnter student name: ";
    cin.getline(studentName, 50);
}

void Student::displayStudent() const {
    cout << "\nAdmission Number: " << admissionNumber;
    cout << "\nName: " << studentName;
    cout << "\nBorrowed Book ID: " << borrowedBookID;
    cout << "\nTokens: " << tokens;
}

void Student::listStudents() const {
    cout << admissionNumber << "\t" << studentName << "\t" << borrowedBookID << "\t" << tokens << endl;
}

void Student::setToken(int token) {
    tokens = token;
}

void Student::resetToken() {
    tokens = 0;
}

int Student::getBorrowedBookID() const {
    return borrowedBookID;
}

int Student::getAdmissionNumber() const {
    return admissionNumber;
}
