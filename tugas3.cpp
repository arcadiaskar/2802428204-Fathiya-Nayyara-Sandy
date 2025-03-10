#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

struct Node {
    int key;
    char value[50];
    struct Node *next;
} *hashTable[TABLE_SIZE];

int (*hashFunction)(int);
void (*collisionHandler)(int, char[]);

int midSquare(int key) {
    int square = key * key;
    return (square / 100) % TABLE_SIZE;
}

int division(int key) {
    return key % TABLE_SIZE;
}

int folding(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    return sum % TABLE_SIZE;
}

int digitExtraction(int key) {
    return (key / 10) % TABLE_SIZE;
}

int rotation(int key) {
    int lastDigit = key % 10;
    key = (key / 10) + (lastDigit * 1000);
    return key % TABLE_SIZE;
}

void linearProbing(int key, char value[]) {
    int index = hashFunction(key);
    while (hashTable[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }
    hashTable[index] = (struct Node *)malloc(sizeof(struct Node));
    hashTable[index]->key = key;
    strcpy(hashTable[index]->value, value);
    hashTable[index]->next = NULL;
}

void chaining(int key, char value[]) {
    int index = hashFunction(key);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void rehashing(int key, char value[]) {
    int index = hashFunction(key);
    int newIndex = (index + 1) % TABLE_SIZE;
    while (hashTable[newIndex] != NULL) {
        newIndex = (newIndex + 1) % TABLE_SIZE;
    }
    hashTable[newIndex] = (struct Node *)malloc(sizeof(struct Node));
    hashTable[newIndex]->key = key;
    strcpy(hashTable[newIndex]->value, value);
    hashTable[newIndex]->next = NULL;
}

void insert(int key, char value[]) {
    collisionHandler(key, value);
}

void search(int key) {
    int index = hashFunction(key);
    struct Node *curr = hashTable[index];
    
    while (curr != NULL) {
        if (curr->key == key) {
            printf("Data found: %s\n", curr->value);
            return;
        }
        curr = curr->next;
    }
    printf("Data not found.\n");
}

// Display Hash Table
void display() {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        struct Node *curr = hashTable[i];
        while (curr != NULL) {
            printf("(%d, %s) -> ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, key;
    char value[50];

    printf("Choose Hash Function:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: hashFunction = midSquare; break;
        case 2: hashFunction = division; break;
        case 3: hashFunction = folding; break;
        case 4: hashFunction = digitExtraction; break;
        case 5: hashFunction = rotation; break;
        default: printf("Invalid choice\n"); return 0;
    }

    printf("Choose Collision Handling:\n");
    printf("1. Linear Probing\n2. Chaining\n3. Rehashing\n");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: collisionHandler = linearProbing; break;
        case 2: collisionHandler = chaining; break;
        case 3: collisionHandler = rehashing; break;
        default: printf("Invalid choice\n"); return 0;
    }
    
    do {
        printf("\n1. Insert Data\n2. Search Data\n3. Display Hash Table\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                scanf("%d", &key);
                scanf("%s", value);
                insert(key, value);
                break;
            case 2:
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                display();
                break;
        }
    } while (choice != 4);

    return 0;
}
