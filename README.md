Library Management System (C++)

This project is a simple console-based Library Management System implemented in C++ using linked lists.
It allows managing books, users, and transactions without using advanced data structures such as vectors.

Features
Book Management

Add new books

Search books by:

Title

Author

ISBN

Sort books by:

Title

Author

Borrow and return books

Track availability status

Save book data to books.txt

User Management

Add new users

Store user details such as ID, name, and contact number

Save user data to users.txt

Transaction Management

Record borrow and return transactions

Automatically attach timestamps

Save all transactions to transactions.txt

Statistics

Display:

Total number of books

Available books

Borrowed books

Total number of registered users

Total transactions

File Structure
File	Purpose
main.cpp	Contains the full program source code
books.txt	Stores all book records
users.txt	Stores all user records
transactions.txt	Stores all borrow/return logs
How It Works

The program uses singly linked lists to store:

Books

Users

Transactions

Each new record is inserted at the beginning of the linked list.
Data is saved to files every time a new record is added or updated.

Compilation and Execution
Using g++
g++ main.cpp -o library
./library

Menu Options

Add Book

Add User

Borrow Book

Return Book

Search Book

Sort Books

Show Statistics

Exit

Limitations

Data is stored using simple text files (not a database).

Linked lists are used instead of vectors or STL containers.

Program does not load data from text files on startup (optional improvement).
