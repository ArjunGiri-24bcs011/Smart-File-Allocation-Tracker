#include <stdio.h>
#include <string.h>
#define TABLE_SIZE 10  
struct IDCard {
    char id[20];
    char name[50];
    char dept[10];
    char contact[15];
    int isOccupied;
};
struct IDCard hashTable[TABLE_SIZE];
int customHash(char id[], char dept[]) {
    int sum = 0;
    int i=0;
    for ( i = 0; id[i] != '\0'; i++)
        sum += id[i];
    int deptCode = dept[0];
    return (sum * deptCode) % TABLE_SIZE;
}
void insert() {
    struct IDCard newCard;
    printf("\nEnter ID Number: ");
    scanf("%s", newCard.id);
    printf("Enter Name: ");
    scanf("%s", newCard.name);
    printf("Enter Department: ");
    scanf("%s", newCard.dept);
    printf("Enter Contact: ");
    scanf("%s", newCard.contact);
    newCard.isOccupied = 1;
	int index = customHash(newCard.id, newCard.dept);
    int start = index;
    while (hashTable[index].isOccupied) {
        printf("? Collision at index %d. Trying next slot...\n", index);
        index = (index + 1) % TABLE_SIZE;
        if (index == start) {
            printf("? Hash table is full!\n");
            return;
        }
    }
    hashTable[index] = newCard;
    printf("? Stored successfully at index %d\n", index);
}
void search() {
    char id[20], dept[10];
    printf("\nEnter ID Number to Search: ");
    scanf("%s", id);
    printf("Enter Department: ");
    scanf("%s", dept);

    int index = customHash(id, dept);
    int start = index;

    while (hashTable[index].isOccupied) {
        if (strcmp(hashTable[index].id, id) == 0) {
            printf("\n? ID Found at index %d\n", index);
            printf("Name: %s\n", hashTable[index].name);
            printf("Department: %s\n", hashTable[index].dept);
            printf("Contact: %s\n", hashTable[index].contact);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start) break;
    }

    printf("? ID not found!\n");
}
void deleteRecord() {
    char id[20], dept[10];
    printf("\nEnter ID Number to Delete: ");
    scanf("%s", id);
    printf("Enter Department: ");
    scanf("%s", dept);

    int index = customHash(id, dept);
    int start = index;

    while (hashTable[index].isOccupied) {
        if (strcmp(hashTable[index].id, id) == 0) {
            hashTable[index].isOccupied = 0;
            printf("?? ID deleted from index %d\n", index);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start) break;
    }

    printf("? ID not found to delete!\n");
}
void display() {
    printf("\n===== HASH TABLE =====\n");
    int i;
    for ( i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].isOccupied) {
            printf("[%d] ID: %s | Name: %s | Dept: %s | Contact: %s\n",
                   i,
                   hashTable[i].id,
                   hashTable[i].name,
                   hashTable[i].dept,
                   hashTable[i].contact);
        } else {
            printf("[%d] --- Empty ---\n", i);
        }
    }
}
int main() {
    int choice,i;
    for ( i = 0; i < TABLE_SIZE; i++)
        hashTable[i].isOccupied = 0;

    while (1) {
        printf("\n==============================");
        printf("\n LOST ID CARD RETRIEVAL SYSTEM");
        printf("\n==============================");
        printf("\n1. Report Lost ID");
        printf("\n2. Find Lost ID");
        printf("\n3. Delete Returned ID");
        printf("\n4. Display Hash Table");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: search(); break;
            case 3: deleteRecord(); break;
            case 4: display(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
