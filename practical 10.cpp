#include <iostream>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float sgpa;
    char dept[30];
};

void swapStudent(Student &a, Student &b) {
    Student temp = a;
    a = b;
    b = temp;
}

int compareStr(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void display(Student s[], int n) {
    cout << "\nRollNo\tName\t\tSGPA\tDept\n";
    cout << "--------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << s[i].rollNo << "\t" << s[i].name << "\t\t" 
             << s[i].sgpa << "\t" << s[i].dept << "\n";
    }
    cout << "--------------------------------------\n";
}

void bubbleSort(Student s[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (s[j].rollNo > s[j + 1].rollNo) {
                swapStudent(s[j], s[j + 1]);
            }
        }
    }
}

void insertionSort(Student s[], int n) {
    int i, j;
    Student key;
    for (i = 1; i < n; i++) {
        key = s[i];
        j = i - 1;
        while (j >= 0 && compareStr(s[j].name, key.name) > 0) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}

int partition(Student s[], int low, int high) {
    float pivot = s[high].sgpa;
    int i = low - 1;
    int j;
    for (j = low; j < high; j++) {
        if (s[j].sgpa > pivot) {
            i++;
            swapStudent(s[i], s[j]);
        }
    }
    swapStudent(s[i + 1], s[high]);
    return i + 1;
}

void quickSort(Student s[], int low, int high) {
    if (low < high) {
        int pi = partition(s, low, high);
        quickSort(s, low, pi - 1);
        quickSort(s, pi + 1, high);
    }
}

void linearSearchSGPA(Student s[], int n, float key) {
    int i;
    int found = 0;
    for (i = 0; i < n; i++) {
        if (s[i].sgpa == key) {
            cout << s[i].rollNo << "\t" << s[i].name << "\t"
                 << s[i].sgpa << "\t" << s[i].dept << "\n";
            found = 1;
        }
    }
    if (!found)
        cout << "No student found with SGPA " << key << "\n";
}

void binarySearchName(Student s[], int n, char key[]) {
    int low = 0, high = n - 1;
    int found = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = compareStr(s[mid].name, key);
        if (cmp == 0) {
            cout << "Found: " << s[mid].rollNo << "\t" << s[mid].name 
                 << "\t" << s[mid].sgpa << "\t" << s[mid].dept << "\n";
            found = 1;
            break;
        } else if (cmp > 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (!found)
        cout << "Student not found with name " << key << "\n";
}

int minInt(int x, int y) {
    if (x < y) return x;
    else return y;
}

void fibonacciSearchDept(Student s[], int n, char key[]) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    int found = 0;

    while (fibM > 1) {
        int i = minInt(offset + fibMMm2, n - 1);
        int cmp = compareStr(s[i].name, key);

        if (cmp < 0) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (cmp > 0) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            cout << "\nStudent found: " << s[i].name 
                 << " Dept: " << s[i].dept << "\n";
            if (compareStr(s[i].dept, (char*)"Computer") == 0)
                cout << "? Yes, belongs to Computer department\n";
            else
                cout << "? No, does not belong to Computer department\n";
            found = 1;
            break;
        }
    }
    if (!found)
        cout << "Student not found.\n";
}

int main() {
    int n, choice;
    cout << "Enter number of students (>=15): ";
    cin >> n;

    Student s[100];
    int i;
    for (i = 0; i < n; i++) {
        cout << "\nEnter details of student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> s[i].rollNo;
        cout << "Name: ";
        cin >> s[i].name;
        cout << "SGPA: ";
        cin >> s[i].sgpa;
        cout << "Department: ";
        cin >> s[i].dept;
    }

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Sort by Roll No (Bubble Sort)\n";
        cout << "2. Sort by Name (Insertion Sort)\n";
        cout << "3. Find Top 10 (Quick Sort)\n";
        cout << "4. Search by SGPA (Linear Search)\n";
        cout << "5. Search by Name (Binary Search)\n";
        cout << "6. Check Computer Dept (Fibonacci Search)\n";
        cout << "7. Display All\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            bubbleSort(s, n);
            display(s, n);
        } else if (choice == 2) {
            insertionSort(s, n);
            display(s, n);
        } else if (choice == 3) {
            quickSort(s, 0, n - 1);
            cout << "\nTop 10 Toppers:\n";
            int limit = n;
            if (n > 10) limit = 10;
            display(s, limit);
        } else if (choice == 4) {
            float sg;
            cout << "Enter SGPA to search: ";
            cin >> sg;
            linearSearchSGPA(s, n, sg);
        } else if (choice == 5) {
            char key[50];
            cout << "Enter Name to search: ";
            cin >> key;
            insertionSort(s, n);
            binarySearchName(s, n, key);
        } else if (choice == 6) {
            char key[50];
            cout << "Enter Name to check: ";
            cin >> key;
            insertionSort(s, n);
            fibonacciSearchDept(s, n, key);
        } else if (choice == 7) {
            display(s, n);
        }
    } while (choice != 0);

    return 0;
}
