#include <bits/stdc++.h>
using namespace std;
struct Book {
    int id;
    string title;
    string author;
    bool available;
    Book* next;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        available = true;
        next = nullptr;
    }
};

struct Action {
    string type; 
    int bookId;
};

class Inventory {
private:
    Book* head;

public:
    Inventory() : head(nullptr) {}

    void addBook(int id, string title, string author) {
        Book* newBook = new Book(id, title, author);
        newBook->next = head;
        head = newBook;
    }

    Book* searchById(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void searchByTitle(string title) {
        Book* temp = head;
        bool found = false;
        while (temp) {
            if (temp->title.find(title) != string::npos) {
                cout << "ID: " << temp->id 
                     << " | " << temp->title 
                     << " by " << temp->author 
                     << " | " << (temp->available ? "Available" : "Borrowed") 
                     << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) cout << "No books found with title containing: " << title << endl;
    }

    void searchByAuthor(string author) {
        Book* temp = head;
        bool found = false;
        while (temp) {
            if (temp->author.find(author) != string::npos) {
                cout << "ID: " << temp->id 
                     << " | " << temp->title 
                     << " by " << temp->author 
                     << " | " << (temp->available ? "Available" : "Borrowed") 
                     << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) cout << "No books found by author: " << author << endl;
    }

    void displayAll() {
        Book* temp = head;
        if (!temp) {
            cout << "No books in inventory.\n";
            return;
        }
        while (temp) {
            cout << "ID: " << temp->id 
                 << " | " << temp->title 
                 << " by " << temp->author 
                 << " | " << (temp->available ? "Available" : "Borrowed") 
                 << endl;
            temp = temp->next;
        }
    }
};

class ELibrary {
private:
    Inventory inventory;
    stack<Action> history;

public:
    void addBook(int id, string title, string author) {
        inventory.addBook(id, title, author);
    }

    void borrowBook(int id) {
        Book* book = inventory.searchById(id);
        if (book && book->available) {
            book->available = false;
            history.push({"borrow", id});
            cout << "You borrowed \"" << book->title << "\" successfully.\n";
        } else {
            cout << "Book not available or doesn't exist.\n";
        }
    }

    void returnBook(int id) {
        Book* book = inventory.searchById(id);
        if (book && !book->available) {
            book->available = true;
            history.push({"return", id});
            cout << "You returned \"" << book->title << "\" successfully.\n";
        } else {
            cout << "Invalid return operation.\n";
        }
    }

    void undoLastAction() {
        if (history.empty()) {
            cout << "No actions to undo.\n";
            return;
        }

        Action last = history.top();
        history.pop();

        Book* book = inventory.searchById(last.bookId);
        if (!book) return;

        if (last.type == "borrow") {
            book->available = true;
            cout << "Undo: Borrow of \"" << book->title << "\" reverted.\n";
        } else if (last.type == "return") {
            book->available = false;
            cout << "Undo: Return of \"" << book->title << "\" reverted.\n";
        }
    }

    void searchTitle(string title) { inventory.searchByTitle(title); }
    void searchAuthor(string author) { inventory.searchByAuthor(author); }
    void showInventory() { inventory.displayAll(); }
};

int main() {
    ELibrary lib;

    
    lib.addBook(1, "C++ Programming", "Bjarne Stroustrup");
    lib.addBook(2, "Introduction to Algorithms", "Thomas H. Cormen");
    lib.addBook(3, "Clean Code", "Robert C. Martin");

    int choice, id;
    string input;

    while (true) {
        cout << "\n=== E-Library Menu ===\n";
        cout << "1. Show all books\n";
        cout << "2. Search by Title\n";
        cout << "3. Search by Author\n";
        cout << "4. Borrow a book\n";
        cout << "5. Return a book\n";
        cout << "6. Undo last action\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                lib.showInventory();
                break;
            case 2:
                cout << "Enter title: ";
                getline(cin, input);
                lib.searchTitle(input);
                break;
            case 3:
                cout << "Enter author: ";
                getline(cin, input);
                lib.searchAuthor(input);
                break;
            case 4:
                cout << "Enter Book ID: ";
                cin >> id;
                lib.borrowBook(id);
                break;
            case 5:
                cout << "Enter Book ID: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 6:
                lib.undoLastAction();
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
