#include <iostream>
#include <string>
using namespace std;

struct Item {
    string name;
    int quantity;
    float price;
    Item* next;
};


Item* createItem(string name, int quantity, float price) {
    Item* newItem = new Item;
    newItem->name = name;
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->next = NULL;  
    return newItem;
}


void addItem(Item*& head) {
    string name;
    int quantity;
    float price;

    cout << "Enter item name: ";
    cin.ignore(); 
    getline(cin, name);
    cout << "Enter quantity: ";
    cin >> quantity;
    cout << "Enter price per unit: ";
    cin >> price;

    Item* newItem = createItem(name, quantity, price);

    if (head == NULL) {
        head = newItem;
    } else {
        Item* temp = head;
        while (temp->next != NULL) 
            temp = temp->next;
        temp->next = newItem;
    }
    cout << "Item added successfully!\n";
}


void displayItems(Item* head) {
    if (head == NULL) { 
        cout << "No items to display.\n";
        return;
    }

    cout << "\nGrocery Bill:\n";
    cout << "------------------------------------\n";
    cout << "Name\tQuantity\tPrice\tTotal\n";
    cout << "------------------------------------\n";

    Item* temp = head;
    while (temp != NULL) {
        cout << temp->name << "\t" << temp->quantity << "\t\t" 
             << temp->price << "\t" << temp->quantity * temp->price << "\n";
        temp = temp->next;
    }
    cout << "------------------------------------\n";
}


void calculateTotal(Item* head) {
    float total = 0;
    Item* temp = head;
    while (temp != NULL) { 
        total += temp->quantity * temp->price;
        temp = temp->next;
    }
    cout << "Total Amount: $" << total << "\n";
}

void freeList(Item* head) {
    while (head != NULL) {
        Item* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Item* head = NULL; 
    int choice;

    do {
        cout << "\n--- Grocery Billing System ---\n";
        cout << "1. Add Item\n";
        cout << "2. Display Bill\n";
        cout << "3. Calculate Total\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addItem(head);
                break;
            case 2:
                displayItems(head);
                break;
            case 3:
                calculateTotal(head);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 4);

    freeList(head);
    return 0;
}
