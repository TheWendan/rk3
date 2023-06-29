#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 7
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHORS_LENGTH 100
#define MAX_ISBN_LENGTH 14

struct Book {
    char isbn[MAX_ISBN_LENGTH];
    char authors[MAX_AUTHORS_LENGTH];
    char title[MAX_TITLE_LENGTH];
    int total;
    int available;
};

void printMenu() {
    printf("Menu:\n");
    printf("1) Add a new book\n");
    printf("2) Delete a book by ISBN number\n");
    printf("3) Shut down the program\n");
    printf("Select an operation (1-3): ");
}

void addBook(struct Book* books, int* count) {
    if (*count >= MAX_BOOKS) {
        printf("\nThe maximum number of books has been reached\n\n");
        return;
    }

    struct Book newBook;

    printf("Enter the book's ISBN number: ");
    scanf("%s", newBook.isbn);

    for (int i = 0; i < *count; i++) {
        if (strcmp(newBook.isbn, books[i].isbn) == 0) {
            printf("A book with this ISBN number already exists\n");
            return;
        }
    }

    printf("Enter the full name of the authors: ");
    scanf(" %[^\n]s", newBook.authors);

    printf("Name of book: ");
    scanf(" %[^\n]s", newBook.title);

    printf("Enter the number of books: ");
    scanf("%d", &newBook.total);

    printf("Enter the number of available books: ");
    scanf("%d", &newBook.available);

    books[*count] = newBook;
    (*count)++;

    printf("The book was successfully added\n");
}

void removeBook(struct Book* books, int* count) {
    char isbnToRemove[MAX_ISBN_LENGTH];
    printf("Enter the ISBN number of the book to delete: ");
    scanf("%s", isbnToRemove);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(isbnToRemove, books[i].isbn) == 0) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                books[j] = books[j + 1];
            }
            (*count)--;
            printf("The book was successfully deleted\n");
            break;
        }
    }

    if (!found) {
        printf("A book with this ISBN number was not found\n");
    }
}

void saveBooksToFile(struct Book* books, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error when opening a file for saving\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s;%s;%d;%d\n", books[i].isbn, books[i].authors, books[i].title, books[i].total, books[i].available);
    }

    fclose(file);
    printf("The state of the library has been successfully saved to a file\n");
}

int main() {
    struct Book books[MAX_BOOKS];
    int count = 0;

    FILE* file = fopen("books.csv", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%[^;];%[^;];%[^;];%d;%d\n", books[count].isbn, books[count].authors, books[count].title, &books[count].total, &books[count].available);
            count++;
        }
        fclose(file);
    }

    int choice;
    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &count);
                break;
            case 2:
                removeBook(books, &count);
                break;
            case 3:
                saveBooksToFile(books, count, "books.csv");
                break;
            default:
                printf("Wrong choice. Try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}