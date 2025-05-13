#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_SIZE 100

typedef struct Node {
    char ch;
    struct Node* next;
} Node;

void push(Node** top, char ch) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->ch = ch;
    newNode->next = *top;
    *top = newNode;
}

char pop(Node** top) {
    if (*top == NULL) return '\0';
    Node* temp = *top;
    char ch = temp->ch;
    *top = temp->next;
    free(temp);
    return ch;
}

void clearStack(Node** top) {
    while (*top) {
        Node* temp = *top;
        *top = temp->next;
        free(temp);
    }
}

void printCurrentText(Node* undoStack) {
    Node* reversed = NULL;
    Node* temp = undoStack;

    while (temp) {
        push(&reversed, temp->ch);
        temp = temp->next;
    }

    temp = reversed;
    if (!temp) {
        printf("(empty)");
    }

    while (temp) {
        printf("%c", temp->ch);
        temp = temp->next;
    }

    clearStack(&reversed);
}

int main() {
    Node* undoStack = NULL;
    Node* redoStack = NULL;
    int choice;
    char input[TEXT_SIZE];

    do {
        printf("\n--- Simple Text Editor ---\n");
        printf("Current Text: ");
        printCurrentText(undoStack);
        printf("\n");

        printf("1. Type Text\n2. Undo\n3. Redo\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter text to add: ");
                fgets(input, TEXT_SIZE, stdin);
                input[strcspn(input, "\n")] = 0;

                for (int i = 0; input[i] != '\0'; i++) {
                    push(&undoStack, input[i]);
                }
                clearStack(&redoStack);
                break;

            case 2: {
                char ch = pop(&undoStack);
                if (ch != '\0') {
                    push(&redoStack, ch);
                } else {
                    printf("Nothing to undo.\n");
                }
                break;
            }

            case 3: {
                char ch = pop(&redoStack);
                if (ch != '\0') {
                    push(&undoStack, ch);
                } else {
                    printf("Nothing to redo.\n");
                }
                break;
            }

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    clearStack(&undoStack);
    clearStack(&redoStack);
    return 0;
}
