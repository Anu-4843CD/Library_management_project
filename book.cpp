#include "book.h"

Book::Book() : bookID(0), stock(0) {
    strcpy(title, "");
    strcpy(author, "");
    strcpy(publisher, "");
}

void Book::createBook() {
    cout << "\nEnter book ID: ";
    cin >> bookID;
    cin.ignore();
    cout << "\nEnter book title: ";
    cin.getline(title, 100);
    cout << "\nEnter author name: ";
    cin.getline(author, 100);
    cout << "\nEnter publisher name: ";
    cin.getline(publisher, 100);
    cout << "\nEnter stock quantity: ";
    cin >> stock;
}

void Book::displayBook() const {
    cout << "\nBook ID: " << bookID;
    cout << "\nTitle: " << title;
    cout << "\nAuthor: " << author;
    cout << "\nPublisher: " << publisher;
    cout << "\nStock: " << stock;
}

void Book::listBooks() const {
    cout << bookID << "\t" << title << "\t" << author << "\t" << publisher << "\t" << stock << endl;
}

void Book::setBookID(int id) {
    bookID = id;
}

void Book::updateStock(int count) {
    stock += count;
}

int Book::getStock() const {
    return stock;
}

int Book::getBookID() const {
    return bookID;
}
