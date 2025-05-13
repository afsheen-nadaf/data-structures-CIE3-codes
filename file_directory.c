#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50

typedef struct Node {
    char name[NAME_SIZE];
    int isFolder; // 1 = folder, 0 = file
    struct Node* child;
    struct Node* sibling;
} Node;

// Create a new node (file or folder)
Node* createNode(const char* name, int isFolder) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->isFolder = isFolder;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Find a folder by path recursively
Node* findNode(Node* root, char* path) {
    if (strcmp(path, "/") == 0) return root;

    char* token = strtok(path, "/");
    Node* current = root->child;

    while (token != NULL && current != NULL) {
        while (current && strcmp(current->name, token) != 0) {
            current = current->sibling;
        }

        if (current == NULL) return NULL; // Path not found
        token = strtok(NULL, "/");

        if (token) current = current->child;
    }

    return current;
}

// Add file or folder under a directory
void addNode(Node* root, char* path, const char* name, int isFolder) {
    char pathCopy[100];
    strcpy(pathCopy, path); // strtok modifies the original string

    Node* parent = findNode(root, pathCopy);
    if (!parent) {
        printf("Path not found.\n");
        return;
    }

    Node* newNode = createNode(name, isFolder);

    // Add as the first child or sibling of existing child
    if (!parent->child) {
        parent->child = newNode;
    } else {
        Node* temp = parent->child;
        while (temp->sibling) {
            temp = temp->sibling;
        }
        temp->sibling = newNode;
    }

    printf("%s added successfully under %s\n", name, path);
}

// Display the directory tree
void displayTree(Node* root, int level) {
    for (int i = 0; i < level; i++) printf("  ");
    printf("|-- %s%s\n", root->name, root->isFolder ? "/" : "");

    Node* child = root->child;
    while (child) {
        displayTree(child, level + 1);
        child = child->sibling;
    }
}

// Driver code
int main() {
    Node* root = createNode("root", 1); // Root directory
    int choice;
    char path[100], name[50];
    int isFolder;

    do {
        printf("\n--- File System Menu ---\n");
        printf("1. Add Folder\n2. Add File\n3. Display Structure\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
            case 2:
                printf("Enter parent directory path (e.g., / or /Documents): ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;

                printf("Enter name of %s: ", choice == 1 ? "folder" : "file");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                isFolder = (choice == 1) ? 1 : 0;
                addNode(root, path, name, isFolder);
                break;

            case 3:
                printf("\n--- Directory Structure ---\n");
                displayTree(root, 0);
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