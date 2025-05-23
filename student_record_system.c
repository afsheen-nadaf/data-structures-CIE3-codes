#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define NAME_SIZE 50

typedef struct {
    int id;
    char name[NAME_SIZE];
    int isOccupied;
    int isDeleted; // New flag
} Student;

Student hashTable[TABLE_SIZE];

void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].isOccupied = 0;
        hashTable[i].isDeleted = 0;
    }
}

int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void insertStudent(int id, const char* name) {
    int index = hashFunction(id);
    int startIndex = index;

    while (hashTable[index].isOccupied && !hashTable[index].isDeleted) {
        if (hashTable[index].id == id) {
            printf("Duplicate ID! Student already exists.\n");
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            printf("Hash table is full!\n");
            return;
        }
    }

    hashTable[index].id = id;
    strcpy(hashTable[index].name, name);
    hashTable[index].isOccupied = 1;
    hashTable[index].isDeleted = 0;
    printf("Student inserted at index %d.\n", index);
}

void searchStudent(int id) {
    int index = hashFunction(id);
    int startIndex = index;

    while (hashTable[index].isOccupied || hashTable[index].isDeleted) {
        if (hashTable[index].isOccupied && !hashTable[index].isDeleted && hashTable[index].id == id) {
            printf("Student Found:\n");
            printf("ID: %d, Name: %s\n", hashTable[index].id, hashTable[index].name);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) break;
    }

    printf("Student with ID %d not found.\n", id);
}

void deleteStudent(int id) {
    int index = hashFunction(id);
    int startIndex = index;

    while (hashTable[index].isOccupied || hashTable[index].isDeleted) {
        if (hashTable[index].isOccupied && !hashTable[index].isDeleted && hashTable[index].id == id) {
            hashTable[index].isDeleted = 1;
            hashTable[index].isOccupied = 0;
            printf("Student with ID %d deleted.\n", id);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) break;
    }

    printf("Student with ID %d not found.\n", id);
}

int main() {
    initTable();
    int choice, id;
    char name[NAME_SIZE];

    do {
        printf("\n--- Student Record System ---\n");
        printf("1. Insert Student\n2. Search Student\n3. Delete Student\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter student name: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                insertStudent(id, name);
                break;

            case 2:
                printf("Enter student ID to search: ");
                scanf("%d", &id);
                searchStudent(id);
                break;

            case 3:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    return 0;
}
