#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#define SIZE 10
using namespace std;

class myStack {
    int arr[SIZE];
    int top;

public:
    myStack() {
        top = -1;
    }

    int isstackempty() {
        return (top == -1);
    }

    int isstackfull() {
        return (top == SIZE - 1);
    }

    void push(int data) {
        if (!isstackfull()) {
            arr[++top] = data;
        } else
            cout << "Stack full" << endl;
    }

    int pop() {
        if (!isstackempty()) {
            return arr[top--];
        } else {
            cout << "Stack is Empty" << endl;
            return -1;
        }
    }

    int peek() {
        if (!isstackempty())
            return arr[top];
        else
            return -1;
    }
};

// ---------------------------------------------------------------------------------
class Infix_to_Postfix {
    char infix[100];
    char postfix[200];

public:
    void getInfix() {
        cout << "Enter Infix Expression: ";
        cin.ignore();
        cin.getline(infix, 100);
    }

    int precedence(char op) {
        if (op == '^')
            return 3;
        else if (op == '*' || op == '/')
            return 2;
        else if (op == '+' || op == '-')
            return 1;
        else
            return -1;
    }

    bool isOperator(char ch) {
        return (ch == '^' || ch == '*' || ch == '/' || ch == '-' || ch == '+');
    }

    bool isDigit(char ch) {
        return (ch >= '0' && ch <= '9');
    }

    void convert() {
        myStack s;
        int j = 0;
        int n = strlen(infix);
        for (int i = 0; i < n; i++) {
            if (isDigit(infix[i])) {
                while (i < n && isDigit(infix[i])) {
                    postfix[j++] = infix[i++];
                }
                postfix[j++] = ' ';
                i--;
            } else if (infix[i] == '(') {
                s.push(infix[i]);
            } else if (infix[i] == ')') {
                while (!s.isstackempty() && s.peek() != '(') {
                    postfix[j++] = (char)s.pop();
                    postfix[j++] = ' ';
                }
                s.pop();
            } else if (isOperator(infix[i])) {
                while (!s.isstackempty() && precedence(infix[i]) <= precedence(s.peek())) {
                    postfix[j++] = (char)s.pop();
                    postfix[j++] = ' ';
                }
                s.push(infix[i]);
            }
        }
        while (!s.isstackempty()) {
            postfix[j++] = (char)s.pop();
            postfix[j++] = ' ';
        }
        postfix[j] = '\0';
        cout << "\nPostfix expression is: " << postfix << endl;
    }

    void Postfix_evaluation() {
        myStack s;
        int n = strlen(postfix);
        for (int i = 0; i < n; i++) {
            if (isDigit(postfix[i])) {
                int num = 0;
                while (i < n && isDigit(postfix[i])) {
                    num = num * 10 + (postfix[i] - '0');
                    i++;
                }
                s.push(num);
            } else if (isOperator(postfix[i])) {
                int x = s.pop();
                int y = s.pop();
                switch (postfix[i]) {
                case '+':
                    s.push(y + x);
                    break;
                case '-':
                    s.push(y - x);
                    break;
                case '*':
                    s.push(y * x);
                    break;
                case '/':
                    s.push(y / x);
                    break;
                case '^':
                    s.push(pow(y, x));
                    break;
                default:
                    cout << "Invalid operation" << endl;
                }
            }
        }
        cout << "Evaluation Result is: " << s.pop() << endl;
    }
};

// ---------------------------------------------------------------------------------
int main() {
    Infix_to_Postfix obj;
    int choice;

    do {
        cout << "\n===== STACK & EXPRESSION MENU =====";
        cout << "\n1. Enter Infix Expression";
        cout << "\n2. Convert Infix to Postfix";
        cout << "\n3. Evaluate Postfix Expression";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            obj.getInfix();
            break;
        case 2:
            obj.convert();
            break;
        case 3:
            obj.Postfix_evaluation();
            break;
        case 4:
            cout << "\nExiting Program...\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
