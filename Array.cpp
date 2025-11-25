#include <iostream>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

class StudentArray {
    Student arr[100];  
    int size = 0;   

public:
    void read() {
        int n;
        cout << "Enter number of students: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "\nEnter Roll No.: ";
            cin >> arr[size].rollNo;
            cout << "Enter Name: ";
            cin >> arr[size].name;
            cout << "Enter Marks: ";
            cin >> arr[size].marks;
            size++;
        }
    }

    void display() {
        if (size == 0) {
            cout << "\nNo records to display.\n";
            return;
        }

        cout << "\nStudent Records:\n";
        cout << "---------------------------\n";
        for (int i = 0; i < size; i++) {
            cout << "Roll No.: " << arr[i].rollNo << ", Name: " << arr[i].name
                 << ", Marks: " << arr[i].marks << endl;
        }
        cout << "---------------------------\n";
    }

    void insert() {
        if (size >= 100) {
            cout << "Array is full, cannot insert new record.\n";
            return;
        }

        cout << "\nEnter Roll No.: ";
        cin >> arr[size].rollNo;
        cout << "Enter Name: ";
        cin >> arr[size].name;
        cout << "Enter Marks: ";
        cin >> arr[size].marks;
        size++;
        cout << "Record inserted successfully.\n";
    }

    void update() {
        int rn;
        cout << "\nEnter Roll No. to update: ";
        cin >> rn;

        int idx = -1;
        for (int i = 0; i < size; i++) {
            if (arr[i].rollNo == rn) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            cout << "Roll No. not found.\n";
            return;
        }

        cout << "Enter new Name: ";
        cin >> arr[idx].name;
        cout << "Enter new Marks: ";
        cin >> arr[idx].marks;
        cout << "Record updated successfully.\n";
    }

    void remove() {
        int rn;
        cout << "\nEnter Roll No. to delete: ";
        cin >> rn;

        int idx = -1;
        for (int i = 0; i < size; i++) {
            if (arr[i].rollNo == rn) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            cout << "Roll No. not found.\n";
            return;
        }

        for (int i = idx; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
        cout << "Record deleted successfully.\n";
    }
};

int main() {
    StudentArray s;
    int choice;

    do {
        cout << "\n--- Student Record Menu ---\n";
        cout << "1. Read Records\n";
        cout << "2. Display Records\n";
        cout << "3. Insert Record\n";
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: s.read(); break;
            case 2: s.display(); break;
            case 3: s.insert(); break;
            case 4: s.update(); break;
            case 5: s.remove(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
