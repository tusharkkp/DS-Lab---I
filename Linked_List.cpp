#include <iostream>
#include <cstring>
using namespace std;
class Node {
public:
    int rollNo;
    char name[20];
    float cgpa;
    Node *next;
    Node() {
        next = NULL;
    }
};
class Student {
public:
    Node *head = NULL;

    void create() {
        int ch;
        Node *temp;
        while (1) {
            Node *t = new Node;
            cout << "Enter Roll No.: ";
            cin >> t->rollNo;
            cout << "Enter Name: ";
            cin >> t->name;
            cout << "Enter CGPA: ";
            cin >> t->cgpa;

            if (head == NULL) {
                head = t;
                temp = head;
            } else {
                temp->next = t;
                temp = temp->next;
            }
			cout << "Do you want to continue? (1: Yes / 0: No): ";
            cin >> ch;
            if (ch == 0) {
                break;
            }
        }
    }

    void display() {
        Node *temp = head;
        if (temp == NULL) {
            cout << "No records to display.\n";
            return;
        }

        cout << "\n--- Student Records ---\n";
        while (temp != NULL) {
            cout << "Roll No.: " << temp->rollNo << endl;
            cout << "Name: " << temp->name << endl;
            cout << "CGPA: " << temp->cgpa << endl;
            cout << "-----------------------\n";
            temp = temp->next;
        }
    }

    void search() {
        int rn;
        cout << "Enter the roll number to search: ";
        cin >> rn;
        Node *temp = head;

        while (temp != NULL && temp->rollNo != rn) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Roll number not found.\n";
        } else {
            cout << "\n--- Student Found ---\n";
            cout << "Roll No.: " << temp->rollNo << endl;
            cout << "Name: " << temp->name << endl;
            cout << "CGPA: " << temp->cgpa << endl;
        }
    }

    void update() {
        int roll;
        cout << "Enter the roll number to be updated: ";
        cin >> roll;

        Node *temp = head;
        while (temp != NULL && temp->rollNo != roll) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Roll number not found.\n";
        } else {
            cout << "Enter new roll number: ";
            cin >> temp->rollNo;
            cout << "Enter new name: ";
            cin >> temp->name;
            cout << "Enter new CGPA: ";
            cin >> temp->cgpa;
            cout << "Record updated successfully.\n";
            display();
        }
    }

    void insert_after_value() {
        int roll;
        cout << "Enter the roll number after which you want to insert: ";
        cin >> roll;

        Node *temp = head;
        while (temp != NULL && temp->rollNo != roll) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Roll number not found.\n";
        } else {
            Node *t = new Node;
            cout << "Enter new roll number: ";
            cin >> t->rollNo;
            cout << "Enter name: ";
            cin >> t->name;
            cout << "Enter CGPA: ";
            cin >> t->cgpa;

            t->next = temp->next;
            temp->next = t;
            display();
        }
    }

    void insert_after_position() {
        int pos;
        cout << "Enter the position (starting from 1): ";
        cin >> pos;

        int length = 0;
        Node *temp = head;
        while (temp != NULL) {
            length++;
            temp = temp->next;
        }

        if (pos < 1 || pos > length + 1) {
            cout << "Invalid position.\n";
            return;
        }

        Node *t = new Node;
        cout << "Enter roll number: ";
        cin >> t->rollNo;
        cout << "Enter name: ";
        cin >> t->name;
        cout << "Enter CGPA: ";
        cin >> t->cgpa;

        if (pos == 1) {
            t->next = head;
            head = t;
        } else {
            temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            t->next = temp->next;
            temp->next = t;
        }
        display();
    }

    void delete_a_Node() {
        int choice;
        do {
            cout << "\nDelete Options:\n";
            cout << "1. At Beginning\n2. At End\n3. At Specific Position\n4. Exit\nEnter choice: ";
            cin >> choice;

            if (choice == 1) {
                if (head == NULL) {
                    cout << "List is empty.\n";
                } else {
                    Node *ptr = head;
                    head = head->next;
                    delete ptr;
                    cout << "Node deleted at beginning.\n";
                    display();
                }
            } else if (choice == 2) {
                if (head == NULL) {
                    cout << "List is empty.\n";
                } else if (head->next == NULL) {
                    delete head;
                    head = NULL;
                    cout << "Last node deleted.\n";
                    display();
                } else {
                    Node *temp = head;
                    while (temp->next->next != NULL) {
                        temp = temp->next;
                    }
                    delete temp->next;
                    temp->next = NULL;
                    cout << "Node deleted at end.\n";
                    display();
                }
            } else if (choice == 3) {
                int pos;
                cout << "Enter position: ";
                cin >> pos;

                if (pos < 1) {
                    cout << "Invalid position.\n";
                } else if (pos == 1) {
                    Node *ptr = head;
                    head = head->next;
                    delete ptr;
                    display();
                } else {
                    Node *temp = head;
                    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
                        temp = temp->next;
                    }
                    if (temp == NULL || temp->next == NULL) {
                        cout << "Position out of range.\n";
                    } else {
                        Node *ptr = temp->next;
                        temp->next = ptr->next;
                        delete ptr;
                        display();
                    }
                }
            }
        } while (choice != 4);
    }

    void reverse() {
        Node *prev = NULL;
        Node *curr = head;
        Node *next = NULL;

        while (curr != NULL) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        cout << "List reversed successfully.\n";
        display();
    }

    void sort_values() {
        if (head == NULL) return;

        for (Node *p = head; p->next != NULL; p = p->next) {
            for (Node *q = p->next; q != NULL; q = q->next) {
                if (p->rollNo > q->rollNo) {
                    swap(p->rollNo, q->rollNo);
                    swap(p->cgpa, q->cgpa);
                    char temp[20];
                    strcpy(temp, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, temp);
                }
            }
        }
        cout << "List sorted by Roll Number.\n";
        display();
    }
};

int main() {
    Student s;
    int choice;

    do {
        cout << "\n====== STUDENT RECORD MENU ======\n";
        cout << "1. Create Records\n";
        cout << "2. Display Records\n";
        cout << "3. Search Student by Roll No.\n";
        cout << "4. Update Student Record\n";
        cout << "5. Insert After Roll No.\n";
        cout << "6. Insert After Position\n";
        cout << "7. Delete a Node\n";
        cout << "8. Reverse List\n";
        cout << "9. Sort Records (by Roll No.)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: s.create(); break;
            case 2: s.display(); break;
            case 3: s.search(); break;
            case 4: s.update(); break;
            case 5: s.insert_after_value(); break;
            case 6: s.insert_after_position(); break;
            case 7: s.delete_a_Node(); break;
            case 8: s.reverse(); break;
            case 9: s.sort_values(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
