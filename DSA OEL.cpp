#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class Book {
public:
    string title, author, isbn;
    bool available;
    Book* next;
};

class User {
public:
    string id, name, contact;
    User* next;
};

class Transaction {
public:
    string userId, isbn, type, timestamp;
    Transaction* next;
};

Book* bookHead = NULL;
User* userHead = NULL;
Transaction* transHead = NULL;

string getTimeStamp() {
    time_t now = time(0);
    return ctime(&now);
}

void saveBooks() {
    ofstream f("books.txt");
    Book* temp = bookHead;
    while (temp != NULL) {
        f << temp->title << "|" << temp->author << "|"
          << temp->isbn << "|" << temp->available << "\n";
        temp = temp->next;
    }
}

void saveUsers() {
    ofstream f("users.txt");
    User* temp = userHead;
    while (temp != NULL) {
        f << temp->id << "|" << temp->name << "|" << temp->contact << "\n";
        temp = temp->next;
    }
}

void saveTransactions() {
    ofstream f("transactions.txt");
    Transaction* temp = transHead;
    while (temp != NULL) {
        f << temp->userId << "|" << temp->isbn << "|"
          << temp->type << "|" << temp->timestamp;
        temp = temp->next;
    }
}

void addBook() {
    Book* b = new Book;

    cout << "Enter Book Title: ";
    cin >> b->title;

    cout << "Enter Author Name: ";
    cin >> b->author;

    cout << "Enter ISBN Number: ";
    cin >> b->isbn;

    b->available = true;
    b->next = bookHead;
    bookHead = b;

    saveBooks();
    cout << "Book Added Successfully!\n";
}

void addUser() {
    User* u = new User;

    cout << "Enter User ID: ";
    cin >> u->id;

    cout << "Enter User Name: ";
    cin >> u->name;

    cout << "Enter Contact: ";
    cin >> u->contact;

    u->next = userHead;
    userHead = u;

    saveUsers();
    cout << "User Added Successfully!\n";
}

void addTransaction(string userId, string isbn, string type) {
    Transaction* t = new Transaction;
    t->userId = userId;
    t->isbn = isbn;
    t->type = type;
    t->timestamp = getTimeStamp();
    t->next = transHead;
    transHead = t;
    saveTransactions();
}

void borrowBook() {
    string uid, isbn;

    cout << "Enter User ID: ";
    cin >> uid;

    cout << "Enter Book ISBN: ";
    cin >> isbn;

    Book* temp = bookHead;
    while (temp != NULL) {
        if (temp->isbn == isbn && temp->available) {
            temp->available = false;
            addTransaction(uid, isbn, "Borrow");
            saveBooks();
            cout << "Book Borrowed Successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Book Unavailable!\n";
}

void returnBook() {
    string isbn;

    cout << "Enter ISBN to Return: ";
    cin >> isbn;

    Book* temp = bookHead;
    while (temp != NULL) {
        if (temp->isbn == isbn && !temp->available) {
            temp->available = true;
            addTransaction("N/A", isbn, "Return");
            saveBooks();
            cout << "Book Returned Successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Invalid ISBN or Book Not Borrowed!\n";
}

void searchBookByTitle(string key) {
    Book* temp = bookHead;
    while (temp != NULL) {
        if (temp->title == key)
            cout << temp->title << " | " << temp->author << " | "
                 << temp->isbn << " | "
                 << (temp->available ? "Available" : "Borrowed") << "\n";
        temp = temp->next;
    }
}

void searchBookByAuthor(string key) {
    Book* temp = bookHead;
    while (temp != NULL) {
        if (temp->author == key)
            cout << temp->title << " | " << temp->author << " | "
                 << temp->isbn << " | "
                 << (temp->available ? "Available" : "Borrowed") << "\n";
        temp = temp->next;
    }
}

void searchBookByISBN(string key) {
    Book* temp = bookHead;
    while (temp != NULL) {
        if (temp->isbn == key)
            cout << temp->title << " | " << temp->author << " | "
                 << temp->isbn << " | "
                 << (temp->available ? "Available" : "Borrowed") << "\n";
        temp = temp->next;
    }
}

void sortByTitle() {
    for (Book* i = bookHead; i != NULL; i = i->next) {
        for (Book* j = i->next; j != NULL; j = j->next) {
            if (i->title > j->title) {
                swap(i->title, j->title);
                swap(i->author, j->author);
                swap(i->isbn, j->isbn);
                swap(i->available, j->available);
            }
        }
    }
    saveBooks();
    cout << "Books Sorted by Title!\n";
}

void sortByAuthor() {
    for (Book* i = bookHead; i != NULL; i = i->next) {
        for (Book* j = i->next; j != NULL; j = j->next) {
            if (i->author > j->author) {
                swap(i->title, j->title);
                swap(i->author, j->author);
                swap(i->isbn, j->isbn);
                swap(i->available, j->available);
            }
        }
    }
    saveBooks();
    cout << "Books Sorted by Author!\n";
}

void sortBooks() {
    int ch;

    cout << "1. Sort by Title\n";
    cout << "2. Sort by Author\n";
    cout << "Enter Choice: ";
    cin >> ch;

    if (ch == 1) sortByTitle();
    else sortByAuthor();
}

void displayStats() {
    int totalBooks = 0, availableBooks = 0, borrowedBooks = 0;
    int totalUsers = 0, totalTransactions = 0;

    Book* b = bookHead;
    while (b != NULL) {
        totalBooks++;
        if (b->available) availableBooks++;
        else borrowedBooks++;
        b = b->next;
    }

    User* u = userHead;
    while (u != NULL) {
        totalUsers++;
        u = u->next;
    }

    Transaction* t = transHead;
    while (t != NULL) {
        totalTransactions++;
        t = t->next;
    }

    cout << "\n===== LIBRARY STATISTICS =====\n";
    cout << "Total Books: " << totalBooks << "\n";
    cout << "Available Books: " << availableBooks << "\n";
    cout << "Borrowed Books: " << borrowedBooks << "\n";
    cout << "Total Users: " << totalUsers << "\n";
    cout << "Total Transactions: " << totalTransactions << "\n";
    cout << "===================================\n";
}

void printMenu() {
    cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Book\n";
    cout << "2. Add User\n";
    cout << "3. Borrow Book\n";
    cout << "4. Return Book\n";
    cout << "5. Search Book\n";
    cout << "6. Sort Books\n";
    cout << "7. Show Statistics\n";
    cout << "8. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;

    while (true) {
        printMenu();
        cin >> choice;

        if (choice == 1) addBook();
        else if (choice == 2) addUser();
        else if (choice == 3) borrowBook();
        else if (choice == 4) returnBook();
        else if (choice == 5) {
            int c;
            string key;
            cout << "1. Search by Title\n";
            cout << "2. Search by Author\n";
            cout << "3. Search by ISBN\n";
            cout << "Enter choice: ";
            cin >> c;
            cout << "Enter Search Keyword: ";
            cin >> key;

            if (c == 1) searchBookByTitle(key);
            else if (c == 2) searchBookByAuthor(key);
            else searchBookByISBN(key);
        }
        else if (choice == 6) sortBooks();
        else if (choice == 7) displayStats();
        else if (choice == 8) break;
    }

    return 0;
}

