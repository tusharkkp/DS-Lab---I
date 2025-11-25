#include <iostream>
using namespace std;

class Node {
public:
    int rno;
    int marks;
    string name;
    Node* next;
    Node* prev;
};

class DLL {
public:
    Node* head = NULL;

    void create() {
        int ch;
        Node* temp;
        while (true) {
            if (head == NULL) {
                head = new Node;
                cout << "Enter Roll No.: ";
                cin >> head->rno;
                cout << "Enter Name: ";
                cin >> head->name;
                cout << "Enter Marks: ";
                cin >> head->marks;

                head->next = NULL;
                head->prev = NULL;
                temp = head;
            } else {
                Node* t = new Node;
                cout << "Enter Roll No.: ";
                cin >> t->rno;
                cout << "Enter Name: ";
                cin >> t->name;
                cout << "Enter Marks: ";
                cin >> t->marks;

                t->next = NULL;
                t->prev = temp;
                temp->next = t;
                temp = t;
            }

            cout << "Do you want to continue? (1 = Yes, 0 = No): ";
            cin >> ch;
            if (ch == 0) break;
        }
    }

    void display() {
        Node* temp = head;
        if (temp == NULL) {
            cout << "\nNo records to display.\n";
            return;
        }

        cout << "\nStudent Records:\n";
        cout << "---------------------\n";
        while (temp != NULL) {
            cout << "Roll No.: " << temp->rno << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Marks: " << temp->marks << endl;
            cout << "---------------------\n";
            temp = temp->next;
        }
    }

    void search() {
        if (head == NULL) {
            cout << "\nList is empty.\n";
            return;
        }

        int rn;
        cout << "Enter the roll no to search: ";
        cin >> rn;

        Node* temp = head;
        while (temp != NULL && temp->rno != rn) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "❌ Roll Number not found.\n";
        } else {
            cout << "\n✅ Roll Number found:\n";
            cout << "---------------------\n";
            cout << "Roll No.: " << temp->rno << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Marks: " << temp->marks << endl;
            cout << "---------------------\n";
        }
    }

    void sort() {
        if (head == NULL || head->next == NULL) return;

        bool swapped;
        Node* ptr1;
        Node* lptr = NULL;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->marks > ptr1->next->marks) {
                    swap(ptr1->rno, ptr1->next->rno);
                    swap(ptr1->name, ptr1->next->name);
                    swap(ptr1->marks, ptr1->next->marks);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << "\n✅ List sorted by marks successfully.\n";
    }
};

int main() {
    DLL d;
    int choice;

    do {
        cout << "\n===== STUDENT DATABASE MENU =====";
        cout << "\n1. Create Records";
        cout << "\n2. Display Records";
        cout << "\n3. Search Record";
        cout << "\n4. Sort Records by Marks";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
		switch (choice) {
            case 1:
                d.create();
                break;
            case 2:
                d.display();
                break;
            case 3:
                d.search();
                break;
            case 4:
                d.sort();
                cout << "\nAfter Sorting:";
                d.display();
                break;
            case 5:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);
	return 0;
}
