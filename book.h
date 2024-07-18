#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Book {
private:
    int bookID;
    int stock;
    char title[100];
    char author[100];
    char publisher[100];

public:
    Book();
    void createBook();
    void displayBook() const;
    void listBooks() const;
    void setBookID(int id);
    void updateStock(int count);
    int getStock() const;
    int getBookID() const;
};

#endif
