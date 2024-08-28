#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_USER 100
#define MAX_BOOKS 100
#define MAX_USERS 100

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int available; 
} Book;

typedef struct {
    int id;
    char name[MAX_USER];
    int borrowedBookId; 
} User;

Book books[MAX_BOOKS];
User users[MAX_USERS];

int bookCount = 0;
int userCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Cannot add more books. Library is full.\n");
        return;
    }
    
    Book newBook;
    newBook.id = bookCount + 1;
    printf("Enter title: ");
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; 

    printf("Enter author: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; 

    newBook.available = 1;

    books[bookCount] = newBook;
    bookCount++;

    printf("Book added successfully.\n");
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d\n", books[i].id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Available: %s\n", books[i].available ? "Yes" : "No");
        printf("--------------------\n");
    }
}

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("Cannot add more users. User list is full.\n");
        return;
    }
    
    User newUser;
    newUser.id = userCount + 1;
    newUser.borrowedBookId = -1;
    
    printf("Enter user name: ");
    fgets(newUser.name, MAX_USER, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0'; 

    users[userCount] = newUser;
    userCount++;

    printf("User added successfully.\n");
}

void borrowBook() {
    int userId, bookId;

    printf("Enter user ID: ");
    scanf("%d", &userId);
    getchar(); 

    printf("Enter book ID: ");
    scanf("%d", &bookId);
    getchar(); 

    if (userId < 1 || userId > userCount || bookId < 1 || bookId > bookCount) {
        printf("Invalid user ID or book ID.\n");
        return;
    }

    if (users[userId - 1].borrowedBookId != -1) {
        printf("User already borrowed a book.\n");
        return;
    }

    if (!books[bookId - 1].available) {
        printf("Book is not available.\n");
        return;
    }

    books[bookId - 1].available = 0;
    users[userId - 1].borrowedBookId = bookId;

    printf("Book borrowed successfully.\n");
}

void returnBook() {
    int userId;

    printf("Enter user ID: ");
    scanf("%d", &userId);
    getchar(); 

    if (userId < 1 || userId > userCount) {
        printf("Invalid user ID.\n");
        return;
    }

    int bookId = users[userId - 1].borrowedBookId;
    if (bookId == -1) {
        printf("User has no book to return.\n");
        return;
    }

    books[bookId - 1].available = 1;
    users[userId - 1].borrowedBookId = -1;

    printf("Book returned successfully.\n");
}

int main() {
    int choice;
    
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Add User\n");
        printf("4. Borrow Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                addUser();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
