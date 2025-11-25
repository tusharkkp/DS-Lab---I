#include <iostream> 
using namespace std; 
 
const int N = 4;   
 
void printBoard(int board[N][N]) { 
    cout << "+-----+-----+\n"; 
    for (int r = 0; r < N; r++) { 
        cout << "| "; 
        for (int c = 0; c < N; c++) { 
            cout << board[r][c] << " ";  
            if ((c + 1) % 2 == 0) cout << "| "; 
        } 
        cout << endl; 
        if ((r + 1) % 2 == 0) cout << "+-----+-----+\n"; 
    } 
} 
 
bool isSafe(int board[N][N], int row, int col, int num) { 
    for (int i = 0; i < N; i++) { 
        if (board[row][i] == num || board[i][col] == num) 
            return false; 
    } 
    int startRow = row - row % 2; 
    int startCol = col - col % 2; 
    for (int r = 0; r < 2; r++) { 
        for (int c = 0; c < 2; c++) { 
            if (board[startRow + r][startCol + c] == num) 
                return false; 
        } 
    } 
    return true; 
} 
 
bool solveSudoku(int board[N][N]) { 
    for (int row = 0; row < N; row++) { 
        for (int col = 0; col < N; col++) { 
            if (board[row][col] == 0) { 
                for (int num = 1; num <= N; num++) { 
                    if (isSafe(board, row, col, num)) { 
                        board[row][col] = num; 
                        if (solveSudoku(board)) 
                            return true; 
                        board[row][col] = 0; 
                    } 
                } 
                return false; 
            } 
        } 
    } 
    return true; 
} 
 
int main() { 
    int board[N][N]; 
 
    cout << "Enter 4x4 Sudoku puzzle (use 0 = empty cells):\n"; 
    for (int r = 0; r < N; r++) { 
        for (int c = 0; c < N; c++) { 
            cin >> board[r][c]; 
        } 
    } 
 
    cout << "\nInitial Sudoku:\n"; 
    printBoard(board); 
 
    if (solveSudoku(board)) { 
        cout << "\nSolved Sudoku:\n"; 
        printBoard(board); 
} else { 
cout << "\nNo solution exists!\n"; 
} 
return 0; 
}