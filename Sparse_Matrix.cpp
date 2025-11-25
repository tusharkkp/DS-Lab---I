#include <iostream>
#include <cstring>
using namespace std;

#define MAX 100

class Sparse {
    int i, j, r, c;
    int k;
    int nz;
public:
    int a[MAX][MAX];
    int b[MAX][3];

    Sparse() {
        k = 1;
        nz = 0;
        r = c = 0;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
    }

    void read();
    void convert();
    void display();          
    void transpose();        
    void fast_transpose();   
    void Add(Sparse &s1, Sparse &s2);
    void Multi(Sparse &s1, Sparse &s2);
};

////////////////////////////////////////////////////////////////////////////
void Sparse::read() {
    cout << "Enter number of rows and columns: ";
    cin >> r >> c;

    cout << "Enter matrix elements (row-wise):\n";
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }
}
////////////////////////////////////////////////////////////////////////////
void Sparse::convert() {
    k = 1;
    nz = 0;
    b[0][0] = r;
    b[0][1] = c;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (a[i][j] != 0) {
                b[k][0] = i;        
                b[k][1] = j;        
                b[k][2] = a[i][j];  
                k++;
                nz++;
            }
        }
    }
    b[0][2] = nz; 
}
///////////////////////////////////////////////////////////////////////////////
void Sparse::display() {
    if (b[0][2] == 0) {
        cout << "Triplet is empty (no non-zero elements)\n";
        return;
    }
    cout << "Row\tCol\tVal\n";
    for (i = 0; i <= b[0][2]; i++) {
        cout << b[i][0] << "\t" << b[i][1] << "\t" << b[i][2] << endl;
    }
}
///////////////////////////////////////////////////////////////////////////////
void Sparse::transpose() {
    if (b[0][2] == 0) {
        cout << "Empty matrix - nothing to transpose\n";
        return;
    }
    int t[MAX][3];
    int kk = 1;
    t[0][0] = b[0][1];
    t[0][1] = b[0][0];
    t[0][2] = b[0][2];

    for (int col = 0; col < b[0][1]; col++) {
        for (int p = 1; p <= b[0][2]; p++) {
            if (b[p][1] == col) {
                t[kk][0] = b[p][1]; 
                t[kk][1] = b[p][0]; 
                t[kk][2] = b[p][2];
                kk++;
            }
        }
    }

    for (int p = 0; p < kk; p++) {
        cout << t[p][0] << "\t" << t[p][1] << "\t" << t[p][2] << endl;
    }
}
/////////////////////////////////////////////////////////////////////////////////
void Sparse::fast_transpose() {
    if (b[0][2] == 0) {
        cout << "Empty matrix - nothing to transpose\n";
        return;
    }
	int result[MAX][3];
    int total[MAX];
    int index[MAX];
    int cols = b[0][1];
    int terms = b[0][2];

    for (int i = 0; i < cols; i++) total[i] = 0;
	for (int i = 1; i <= terms; i++) {
        int col_no = b[i][1];
        total[col_no]++;
    }
	index[0] = 1;
    for (int i = 1; i < cols; i++) {
        index[i] = index[i - 1] + total[i - 1];
    }
	result[0][0] = b[0][1];
    result[0][1] = b[0][0];
    result[0][2] = b[0][2];

    for (int i = 1; i <= terms; i++) {
        int col_no = b[i][1];
        int loc = index[col_no];

        result[loc][0] = b[i][1];
        result[loc][1] = b[i][0];
        result[loc][2] = b[i][2];

        index[col_no]++;
    }

    for (int i = 0; i <= result[0][2]; i++) {
        cout << result[i][0] << "\t" << result[i][1] << "\t" << result[i][2] << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////
void Sparse::Add(Sparse &s1, Sparse &s2) {
    if (s1.b[0][0] != s2.b[0][0] || s1.b[0][1] != s2.b[0][1]) {
        cout << "Addition not possible: dimensions mismatch\n";
        return;
    }
	int i = 1, j = 1, k = 1;
    int a_terms = s1.b[0][2];
    int b_terms = s2.b[0][2];
    int sum[MAX][3];
	sum[0][0] = s1.b[0][0];
    sum[0][1] = s1.b[0][1];
	while (i <= a_terms && j <= b_terms) {
        if (s1.b[i][0] < s2.b[j][0] || (s1.b[i][0] == s2.b[j][0] && s1.b[i][1] < s2.b[j][1])) {
            sum[k][0] = s1.b[i][0];
            sum[k][1] = s1.b[i][1];
            sum[k][2] = s1.b[i][2];
            i++; k++;
        } else if (s1.b[i][0] > s2.b[j][0] || (s1.b[i][0] == s2.b[j][0] && s1.b[i][1] > s2.b[j][1])) {
            sum[k][0] = s2.b[j][0];
            sum[k][1] = s2.b[j][1];
            sum[k][2] = s2.b[j][2];
            j++; k++;
        } else { 
            int s = s1.b[i][2] + s2.b[j][2];
            if (s != 0) {
                sum[k][0] = s1.b[i][0];
                sum[k][1] = s1.b[i][1];
                sum[k][2] = s;
                k++;
            }
            i++; j++;
        }
    }
	while (i <= a_terms) {
        sum[k][0] = s1.b[i][0];
        sum[k][1] = s1.b[i][1];
        sum[k][2] = s1.b[i][2];
        i++; k++;
    }
	while (j <= b_terms) {
        sum[k][0] = s2.b[j][0];
        sum[k][1] = s2.b[j][1];
        sum[k][2] = s2.b[j][2];
        j++; k++;
    }
	sum[0][2] = k - 1;
	cout << "Row\tCol\tVal\n";
    for (int p = 0; p <= sum[0][2]; p++) {
        cout << sum[p][0] << "\t" << sum[p][1] << "\t" << sum[p][2] << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Sparse::Multi(Sparse &s1, Sparse &s2) {
    if (s1.b[0][1] != s2.b[0][0]) {
        cout << "Multiplication not possible: inner dimensions mismatch\n";
        return;
    }
	struct Trip { int r, c, v; };
    Trip temp[MAX * 4];
    int tempCount = 0;
	int a_terms = s1.b[0][2];
    int b_terms = s2.b[0][2];
	for (int p = 1; p <= a_terms; p++) {
        for (int q = 1; q <= b_terms; q++) {
            if (s1.b[p][1] == s2.b[q][0]) { 
                int row = s1.b[p][0];
                int col = s2.b[q][1];
                int val = s1.b[p][2] * s2.b[q][2];

                temp[tempCount].r = row;
                temp[tempCount].c = col;
                temp[tempCount].v = val;
                tempCount++;
            }
        }
    }
	if (tempCount == 0) {
        cout << "Product is a zero matrix (no non-zero terms)\n";
        return;
    }
	for (int x = 0; x < tempCount - 1; x++) {
        for (int y = x + 1; y < tempCount; y++) {
            if (temp[x].r > temp[y].r || (temp[x].r == temp[y].r && temp[x].c > temp[y].c)) {
                Trip t = temp[x]; temp[x] = temp[y]; temp[y] = t;
            }
        }
    }
	int prod[MAX][3];
    int kprod = 1;
    for (int t = 0; t < tempCount; ) {
        int rr = temp[t].r;
        int cc = temp[t].c;
        int sumv = 0;
        int u = t;
        while (u < tempCount && temp[u].r == rr && temp[u].c == cc) {
            sumv += temp[u].v;
            u++;
        }
        if (sumv != 0) {
            prod[kprod][0] = rr;
            prod[kprod][1] = cc;
            prod[kprod][2] = sumv;
            kprod++;
        }
        t = u;
    }

    prod[0][0] = s1.b[0][0];
    prod[0][1] = s2.b[0][1];
    prod[0][2] = kprod - 1;

    cout << "Product (triplet):\n";
    cout << "Row\tCol\tVal\n";
    for (int p = 0; p <= prod[0][2]; p++) {
        cout << prod[p][0] << "\t" << prod[p][1] << "\t" << prod[p][2] << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////

int main() {
    Sparse s1, s2, result;
    int choice;

    do {
        cout << "\n====== SPARSE MATRIX MENU ======\n";
        cout << "1. Read Matrix A\n";
        cout << "2. Convert A to Triplet\n";
        cout << "3. Display Triplet of A\n";
        cout << "4. Simple Transpose of A\n";
        cout << "5. Fast Transpose of A\n";
        cout << "6. Read Matrix B\n";
        cout << "7. Convert B to Triplet\n";
        cout << "8. Display Triplet of B\n";
        cout << "9. Add A + B\n";
        cout << "10. Multiply A * B\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: s1.read(); break;
            case 2: s1.convert(); break;
            case 3: s1.display(); break;
            case 4: s1.transpose(); break;
            case 5: s1.fast_transpose(); break;
            case 6: s2.read(); break;
            case 7: s2.convert(); break;
            case 8: s2.display(); break;
            case 9: result.Add(s1, s2); break;
            case 10: result.Multi(s1, s2); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
