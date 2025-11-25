#include <iostream>
using namespace std;
class node {
public:
    int data;
    node* next;
};
class Dequeue {
public:
    node* front;
    node* rear;

    Dequeue() {
        front = NULL;
        rear = NULL;
    }

    void Insert_front(int n);
    void Insert_rear(int n);
    void delete_front();
    void delete_rear();
    void display();
};

void Dequeue::display() {
    if (front == NULL)
        cout << "Queue is Empty" << endl;
    else {
        node* ptr = front;
        cout << "Queue elements: ";
        while (ptr != NULL) {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

void Dequeue::Insert_front(int n) {
    node* temp = new node;
    temp->data = n;
    temp->next = NULL;

    if (front == NULL) {
        front = rear = temp;
    } else {
        temp->next = front;
        front = temp;
    }
    cout << "Inserted Successfully at Front" << endl;
}

void Dequeue::Insert_rear(int n) {
    node* temp = new node;
    temp->data = n;
    temp->next = NULL;

    if (front == NULL) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
    cout << "Inserted Successfully at Rear" << endl;
}

void Dequeue::delete_front() {
    if (front == NULL) {
        cout << "Queue is Empty" << endl;
        return;
    }
    node* ptr = front;
    front = front->next;
    delete ptr;
    if (front == NULL) rear = NULL;
    cout << "Deleted Successfully from Front" << endl;
}

void Dequeue::delete_rear() {
    if (front == NULL) {
        cout << "Queue is Empty" << endl;
        return;
    }
    if (front == rear) {
        delete front;
        front = rear = NULL;
    } else {
        node* temp = front;
        while (temp->next != rear)
            temp = temp->next;
        delete rear;
        rear = temp;
        rear->next = NULL;
    }
    cout << "Deleted Successfully from Rear" << endl;
}

int main() {
    Dequeue dq;
    int ch, num, cont = 1;

    while (cont) {
        cout << "\nChoose Mode:\n1. Input Restricted Deque\n2. Output Restricted Deque\nChoice: ";
        cin >> ch;

        if (ch == 1) {
            int op;
            do {
                cout << "\n-- Input Restricted Deque --"
                     << "\n1. Delete Front"
                     << "\n2. Delete Rear"
                     << "\n3. Insert at Rear"
                     << "\n4. Display"
                     << "\n5. Exit to Main Menu"
                     << "\nChoice: ";
                cin >> op;

                switch (op) {
                    case 1: dq.delete_front(); break;
                    case 2: dq.delete_rear(); break;
                    case 3:
                        cout << "Enter value: ";
                        cin >> num;
                        dq.Insert_rear(num);
                        break;
                    case 4: dq.display(); break;
                    case 5:
                        cout << "Exiting to Main Menu...\n";
                        break;
                    default: cout << "Invalid Choice!" << endl;
                }
            } while (op != 5);
        } else if (ch == 2) {
            int op;
            do {
                cout << "\n-- Output Restricted Deque --"
                     << "\n1. Insert Front"
                     << "\n2. Insert Rear"
                     << "\n3. Delete Front"
                     << "\n4. Display"
                     << "\n5. Exit to Main Menu"
                     << "\nChoice: ";
                cin >> op;

                switch (op) {
                    case 1:
                        cout << "Enter value: ";
                        cin >> num;
                        dq.Insert_front(num);
                        break;
                    case 2:
                        cout << "Enter value: ";
                        cin >> num;
                        dq.Insert_rear(num);
                        break;
                    case 3: dq.delete_front(); break;
                    case 4: dq.display(); break;
                    case 5:
                        cout << "Exiting to Main Menu...\n";
                        break;
                    default: cout << "Invalid Choice!" << endl;
                }
            } while (op != 5);
        } else {
            cout << "Invalid Choice!" << endl;
        }
        cout << "\nContinue? (1 = Yes / 0 = No): ";
        cin >> cont;
    }
    return 0;
}
