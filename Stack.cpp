//#include <iostream>
//#include <stack>
//#include <string>
//#include <cctype>
//#include <cmath>
//#include <map>
//#include <set>
//#include <sstream>  // for number to string conversion
#include<bits/stdc++.h>
using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Convert Prefix ? Infix
string prefixToInfix(string prefix) {
    stack<string> st;
    for (int i = prefix.size() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isalnum(c)) {
            st.push(string(1, c));
        } else if (isOperator(c)) {
            if (st.size() < 2) return "";
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            string exp = "(" + op1 + " " + c + " " + op2 + ")";
            st.push(exp);
        }
    }
    return st.empty() ? "" : st.top();
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Infix ? Postfix
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";

    for (size_t i = 0; i < infix.size(); i++) {
        char c = infix[i];
        if (isalnum(c))
            postfix += c;
        else if (c == '(')
            st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        } else if (isOperator(c)) {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

// Replace to_string() with C++98 version
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// Substitute variable values
string substituteValues(string expr, map<char, int>& values) {
    string substituted = "";
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (isalpha(c)) substituted += intToString(values[c]);
        else substituted += c;
    }
    return substituted;
}

// Evaluate Postfix
int evaluatePostfix(string postfix, map<char, int>& values) {
    stack<int> st;
    for (size_t i = 0; i < postfix.size(); i++) {
        char c = postfix[i];
        if (isalpha(c)) {
            st.push(values[c]);
        } else if (isdigit(c)) {
            st.push(c - '0');
        } else if (isOperator(c)) {
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();
            switch (c) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
                case '^': st.push((int)pow(val1, val2)); break;
            }
        }
    }
    return st.top();
}

int main() {
    cout << "=============================================\n";
    cout << "   PREFIX  INFIX  POSTFIX (STEP-BY-STEP)   \n";
    cout << "=============================================\n\n";

    string prefix;
    cout << "Enter a Prefix Expression (e.g. +A*BC): ";
    cin >> prefix;
    cout << endl;

    // Collect variables
    set<char> variables;
    for (size_t i = 0; i < prefix.size(); i++) {
        if (isalpha(prefix[i]))
            variables.insert(prefix[i]);
    }

    // Input variable values
    map<char, int> values;
    cout << "Enter variable values:\n";
    for (set<char>::iterator it = variables.begin(); it != variables.end(); ++it) {
        cout << "  " << *it << " = ";
        cin >> values[*it];
    }
    cout << endl;

    // Step 1: Prefix ? Infix
    string infix = prefixToInfix(prefix);
    cout << " Step 1: Prefix ? Infix\n";
    cout << "   Variable Expression: " << infix << endl;
    cout << "   Numeric Expression : " << substituteValues(infix, values) << endl;
    cout << endl;

    // Step 2: Infix ? Postfix
    string postfix = infixToPostfix(infix);
    cout << " Step 2: Infix ? Postfix\n";
    cout << "   Variable Expression: " << postfix << endl;
    cout << "   Numeric Expression : " << substituteValues(postfix, values) << endl;
    cout << endl;

    // Step 3: Postfix Evaluation
    int result = evaluatePostfix(postfix, values);
    cout << " Step 3: Postfix Evaluation\n";
    cout << "   Final Result: " << result << endl;
    cout << endl;

    cout << "=============================================\n";
    cout << "             PROCESS COMPLETED          \n";
    cout << "=============================================\n";

    return 0;
}

