#include <iostream>
#include <fstream>
#include "book.h"
#include "student.h"

using namespace std;

void writeBook();
void writeStudent();
void listAllBooks();
void listAllStudents();
void searchBook(int id);
void searchStudent(int id);
void issueBook(int admissionNumber, int bookID);
void returnBook(int admissionNumber, int bookID);

int main() {
    int choice;
    do {
        cout << "\n\nMENU";
        cout << "\n1. Add Book";
        cout << "\n2. Add Student";
        cout << "\n3. List All Books";
        cout << "\n4. List All Students";
        cout << "\n5. Search Book";
        cout << "\n6. Search Student";
        cout << "\n7. Issue Book";
        cout << "\n8. Return Book";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                writeBook();
                break;
            case 2:
                writeStudent();
                break;
            case 3:
                listAllBooks();
                break;
            case 4:
                listAllStudents();
                break;
            case 5:
                int bookID;
                cout << "\nEnter book ID: ";
                cin >> bookID;
                searchBook(bookID);
                break;
            case 6:
                int admissionNumber;
                cout << "\nEnter admission number: ";
                cin >> admissionNumber;
                searchStudent(admissionNumber);
                break;
            case 7:
                cout << "\nEnter admission number: ";
                cin >> admissionNumber;
                cout << "\nEnter book ID: ";
                cin >> bookID;
                issueBook(admissionNumber, bookID);
                break;
            case 8:
                cout << "\nEnter admission number: ";
                cin >> admissionNumber;
                cout << "\nEnter book ID: ";
                cin >> bookID;
                returnBook(admissionNumber, bookID);
                break;
            case 0:
                break;
            default:
                cout << "\nInvalid choice. Please try again.";
        }
    } while (choice != 0);

    return 0;
}

void writeBook() {
    Book bk;
    bk.createBook();
    ofstream outFile("books.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char *>(&bk), sizeof(Book));
    outFile.close();
    cout << "\nBook added successfully.";
}

void writeStudent() {
    Student st;
    st.createStudent();
    ofstream outFile("students.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
    outFile.close();
    cout << "\nStudent added successfully.";
}

void listAllBooks() {
    Book bk;
    ifstream inFile("books.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened.";
        return;
    }
    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book))) {
        bk.listBooks();
    }
    inFile.close();
}

void listAllStudents() {
    Student st;
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened.";
        return;
    }
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
        st.listStudents();
    }
    inFile.close();
}

void searchBook(int id) {
    Book bk;
    ifstream inFile("books.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened.";
        return;
    }
    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book))) {
        if (bk.getBookID() == id) {
            bk.displayBook();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "\nBook not found.";
    }
}

void searchStudent(int id) {
    Student st;
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened.";
        return;
    }
    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student))) {
        if (st.getAdmissionNumber() == id) {
            st.displayStudent();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "\nStudent not found.";
    }
}

void issueBook(int admissionNumber, int bookID) {
    Book bk;
    Student st;
    fstream bookFile("books.dat", ios::binary | ios::in | ios::out);
    fstream studentFile("students.dat", ios::binary | ios::in | ios::out);
    if (!bookFile || !studentFile) {
        cout << "\nFile could not be opened.";
        return;
    }
    bool bookFound = false, studentFound = false;
    while (bookFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && !bookFound) {
        if (bk.getBookID() == bookID && bk.getStock() > 0) {
            bookFound = true;
            bk.updateStock(-1);
            int pos = -static_cast<int>(sizeof(bk));
            bookFile.seekp(pos, ios::cur);
            bookFile.write(reinterpret_cast<char *>(&bk), sizeof(Book));
        }
    }
    while (studentFile.read(reinterpret_cast<char *>(&st), sizeof(Student)) && !studentFound) {
        if (st.getAdmissionNumber() == admissionNumber && st.getBorrowedBookID() == 0) {
            studentFound = true;
            st.setToken(bookID);
            int pos = -static_cast<int>(sizeof(st));
            studentFile.seekp(pos, ios::cur);
            studentFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
        }
    }
    bookFile.close();
    studentFile.close();
    if (bookFound && studentFound) {
        cout << "\nBook issued successfully.";
    } else {
        cout << "\nIssue operation failed.";
    }
}

void returnBook(int admissionNumber, int bookID) {
    Book bk;
    Student st;
    fstream bookFile("books.dat", ios::binary | ios::in | ios::out);
    fstream studentFile("students.dat", ios::binary | ios::in | ios::out);
    if (!bookFile || !studentFile) {
        cout << "\nFile could not be opened.";
        return;
    }
    bool bookFound = false, studentFound = false;
    while (bookFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && !bookFound) {
        if (bk.getBookID() == bookID) {
            bookFound = true;
            bk.updateStock(1);
            int pos = -static_cast<int>(sizeof(bk));
            bookFile.seekp(pos, ios::cur);
            bookFile.write(reinterpret_cast<char *>(&bk), sizeof(Book));
        }
    }
    while (studentFile.read(reinterpret_cast<char *>(&st), sizeof(Student)) && !studentFound) {
        if (st.getAdmissionNumber() == admissionNumber && st.getBorrowedBookID() == bookID) {
            studentFound = true;
            st.resetToken();
            int pos = -static_cast<int>(sizeof(st));
            studentFile.seekp(pos, ios::cur);
            studentFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
        }
    }
    bookFile.close();
    studentFile.close();
    if (bookFound && studentFound) {
        cout << "\nBook returned successfully.";
    } else {
        cout << "\nReturn operation failed.";
    }
}
