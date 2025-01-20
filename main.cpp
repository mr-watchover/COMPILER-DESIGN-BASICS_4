#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <stdexcept>

using namespace std;

// Function to get the precedence of the operators
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// Function to perform arithmetic operations
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                throw invalid_argument("Division by zero!");
            }
            return a / b;
        default: return 0;
    }
}

// Function to evaluate the expression
int evaluateExpression(const string& expression) {
    stack<int> values;  // Stack to store operands
    stack<char> ops;    // Stack to store operators

    for (int i = 0; i < expression.length(); i++) {
        char currentChar = expression[i];

        // Skip white spaces
        if (isspace(currentChar)) {
            continue;
        }

        // If the current character is a number
        if (isdigit(currentChar)) {
            int value = 0;

            // Handle multiple digit numbers
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            i--;  // Decrease i to correct the extra increment in the while loop
            values.push(value);
        }
        // If the current character is an opening parenthesis
        else if (currentChar == '(') {
            ops.push(currentChar);
        }
        // If the current character is a closing parenthesis
        else if (currentChar == ')') {
            // Evaluate the expression inside the parenthesis
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOperation(val1, val2, op));
            }
            ops.pop(); // Remove '(' from the stack
        }
        // If the current character is an operator
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // While the top of ops has the same or higher precedence, apply the operator
            while (!ops.empty() && precedence(ops.top()) >= precedence(currentChar)) {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOperation(val1, val2, op));
            }
            ops.push(currentChar);
        }
    }

    // Apply the remaining operators in the ops stack
    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOperation(val1, val2, op));
    }

    // The final result is the top of the values stack
    return values.top();
}

int main() {
    string expression;

    // Take input expression from the user
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    try {
        int result = evaluateExpression(expression);
        cout << "The result is: " << result << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
