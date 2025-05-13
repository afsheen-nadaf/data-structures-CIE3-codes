#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50

typedef struct Item {
    char name[NAME_SIZE];
    int quantity;
    struct Item* prev;
    struct Item* next;
} Item;

Item* head = NULL;

// Create a new item node
Item* createItem(const char* name, int quantity) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strncpy(newItem->name, name, NAME_SIZE);
    newItem->quantity = quantity;
    newItem->prev = NULL;
    newItem->next = NULL;
    return newItem;
}

// Check if item exists; if yes, return pointer
Item* findItem(const char* name) {
    Item* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add item or update quantity
void addOrUpdateItem(const char* name, int quantity) {
    Item* existing = findItem(name);
    if (existing) {
        existing->quantity += quantity;
        printf("Updated '%s' quantity to %d.\n", name, existing->quantity);
    } else {
        Item* newItem = createItem(name, quantity);
        if (!head) {
            head = newItem;
        } else {
            Item* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newItem;
            newItem->prev = temp;
        }
        printf("Added '%s' to cart (Qty: %d).\n", name, quantity);
    }
}

// Remove an item by name
void removeItem(const char* name) {
    Item* item = findItem(name);
    if (!item) {
        printf("Item '%s' not found.\n", name);
        return;
    }

    if (item->prev) item->prev->next = item->next;
    else head = item->next;

    if (item->next) item->next->prev = item->prev;

    free(item);
    printf("Removed '%s' from cart.\n", name);
}

// Update quantity (overwrite)
void updateQuantity(const char* name, int quantity) {
    Item* item = findItem(name);
    if (!item) {
        printf("Item '%s' not found.\n", name);
        return;
    }
    item->quantity = quantity;
    printf("'%s' quantity updated to %d.\n", name, quantity);
}

// Display cart
void displayCart() {
    if (!head) {
        printf("Cart is empty.\n");
        return;
    }

    printf("\nShopping Cart:\n-----------------------------\n");
    Item* temp = head;
    while (temp) {
        printf("Item: %-15s | Quantity: %d\n", temp->name, temp->quantity);
        temp = temp->next;
    }
}

// Menu
void printMenu() {
    printf("\nSelect an action:\n");
    printf("1. Add Item\n");
    printf("2. Remove Item\n");
    printf("3. Update Item Quantity\n");
    printf("4. View Cart\n");
    printf("5. Exit\n");
    printf("Your choice: ");
}

int main() {
    int choice, quantity;
    char name[NAME_SIZE];

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1:
                printf("Enter item name: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Enter quantity to add: ");
                scanf("%d", &quantity);
                getchar();

                addOrUpdateItem(name, quantity);
                break;

            case 2:
                printf("Enter item name to remove: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = 0;

                removeItem(name);
                break;

            case 3:
                printf("Enter item name to update: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Enter new quantity: ");
                scanf("%d", &quantity);
                getchar();

                updateQuantity(name, quantity);
                break;

            case 4:
                displayCart();
                break;

            case 5:
                printf("Exiting shopping cart.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    // Free memory
    Item* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}