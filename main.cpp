#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Function to evaluate logical expressions
bool eval(const string &expression) {
    stack<char> operators;
    stack<bool> operands;

    // Iterate through each character in the expression
    for (char c: expression) {
        if (c == ' ') {
            continue;  // Ignore spaces
        } else if (c == '0' || c == '1') {
            operands.push(c - '0');  // Convert '0' and '1' to boolean and push onto operand stack
        } else if (c == '(') {
            operators.push(c);  // Push opening parenthesis onto operator stack
        } else if (c == ')') {
            // Process operators until matching opening parenthesis is found
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                // Handle unary operator '!'
                if (op == '!') {
                    if (operands.empty()) {
                        cerr << "Error: No operand for operator " << op << endl;
                        return false;
                    }
                    bool operand = operands.top();
                    operands.pop();
                    operands.push(!operand);
                } else {
                    // Handle binary operators
                    if (operands.size() < 2) {
                        cerr << "Error: Insufficient operands for operator " << op << endl;
                        return false;
                    }
                    bool operand2 = operands.top();
                    operands.pop();
                    bool operand1 = operands.top();
                    operands.pop();

                    // Perform the operation based on the operator
                    if (op == '&') {
                        operands.push(operand1 && operand2);
                    } else if (op == '|') {
                        operands.push(operand1 || operand2);
                    } else if (op == '^') {
                        operands.push(operand1 != operand2);
                    } else if (op == '=') {
                        operands.push(operand1 == operand2);
                    }
                }
            }
            if (!operators.empty()) {
                operators.pop();  // Pop the opening parenthesis from the operator stack
            }
        } else if (c == '&' || c == '|' || c == '^' || c == '!' || c == '=') {
            // Process operators based on precedence and associativity
            while (!operators.empty() && operators.top() != '(' &&
                   ((c == '&' && operators.top() == '|') ||
                    (c == '&' && operators.top() == '^') ||
                    (c == '|' && operators.top() == '^') ||
                    (c == '!' && (operators.top() == '&' || operators.top() == '|' || operators.top() == '^')) ||
                    (c == '=' && (operators.top() == '&' || operators.top() == '|' || operators.top() == '^' ||
                                  operators.top() == '!')))) {
                char op = operators.top();
                operators.pop();
                // Handle unary operator '!'
                if (op == '!') {
                    if (operands.empty()) {
                        cerr << "Error: No operand for operator " << op << endl;
                        return false;
                    }
                    bool operand = operands.top();
                    operands.pop();
                    operands.push(!operand);
                } else {
                    // Handle binary operators
                    if (operands.size() < 2) {
                        cerr << "Error: Insufficient operands for operator " << op << endl;
                        return false;
                    }
                    bool operand2 = operands.top();
                    operands.pop();
                    bool operand1 = operands.top();
                    operands.pop();

                    // Perform the operation based on the operator
                    if (op == '&') {
                        operands.push(operand1 && operand2);
                    } else if (op == '|') {
                        operands.push(operand1 || operand2);
                    } else if (op == '^') {
                        operands.push(operand1 != operand2);
                    } else if (op == '=') {
                        operands.push(operand1 == operand2);
                    }
                }
            }
            // Push the current operator onto the operator stack
            operators.push(c);
        } else {
            cerr << "Error: Unknown character in expression" << endl;
            return false;
        }
    }

    // Process any remaining operators
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        // Handle unary operator '!'
        if (op == '!') {
            if (operands.empty()) {
                cerr << "Error: No operand for operator " << op << endl;
                return false;
            }
            bool operand = operands.top();
            operands.pop();
            operands.push(!operand);
        } else {
            // Handle binary operators
            if (operands.size() < 2) {
                cerr << "Error: Insufficient operands for operator " << op << endl;
                return false;
            }
            bool operand2 = operands.top();
            operands.pop();
            bool operand1 = operands.top();
            operands.pop();

            // Perform the operation based on the operator
            if (op == '&') {
                operands.push(operand1 && operand2);
            } else if (op == '|') {
                operands.push(operand1 || operand2);
            } else if (op == '^') {
                operands.push(operand1 != operand2);
            } else if (op == '=') {
                operands.push(operand1 == operand2);
            }
        }
    }

    // The final result should be on the top of the operand stack
    if (operands.size() == 1) {
        return operands.top();
    } else {
        cerr << "Error: Incorrect expression" << endl;
        return false;
    }
}

bool evaluateExpression(string expression, int *values, int n) {
    for (int i = 0; i < n; ++i) {
        char variable = 'A' + i;
        size_t pos = expression.find(variable);
        while (pos != string::npos) {
            expression.replace(pos, 1, values[i] == 1 ? "1" : "0");
            pos = expression.find(variable);
        }
    }

    return eval(expression);
}

void TruthTable(int numberOfOperators, string operation) {
    //------------------------------------
    printf("%c", 201);
    for (int i = 0; i < numberOfOperators; i++) {
        printf("%c%c%c%c", 205, 205, 205, 209);
    }
    for (int i = 0; i < operation.size() + 2; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    //------------------------------------
    printf("%c", 186);
    int op = 65;
    for (int i = 0; i < numberOfOperators; i++) {
        printf(" %c %c", op, 179);
        op++;
    }
    printf(" %s %c\n", operation.c_str(), 186);
    //------------------------------------
    printf("%c", 199);
    for (int i = 0; i < numberOfOperators; i++) {
        printf("%c%c%c%c", 196, 196, 196, 197);
    }
    for (int i = 0; i < operation.size() + 2; i++) {
        printf("%c", 196);
    }
    printf("%c\n", 182);
    //------------------------------------
    int rowCount = 1 << numberOfOperators;
    int colCount = numberOfOperators;
    int lines[rowCount][colCount];
    for (int i = 0; i < (1 << numberOfOperators); ++i) {
        printf("%c", 186);
        int z = 0;
        for (int j = numberOfOperators - 1; j >= 0; --j) {
            int bit = (i >> j) & 1;
            printf(" %d %c", bit, 179);
            lines[i][z] = bit;
            z++;
        }

        int spaces = operation.size() % 2 == 0 ? operation.size() / 2 : operation.size() / 2 + 1;

        for (int c = 0; c < spaces; c++) {
            cout << " ";
        }

        cout << evaluateExpression(operation, lines[i], numberOfOperators);

        for (int x = 0; x < operation.size() / 2 + 1; x++) {
            cout << " ";
        }

        printf("%c\n", 186);
    }
    //------------------------------------
    printf("%c", 200);
    for (int i = 0; i < numberOfOperators; i++) {
        printf("%c%c%c%c", 205, 205, 205, 207);
    }
    for (int i = 0; i < operation.size() + 2; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}

int main() {
    cout << "Negatie (NOT):\n";
    TruthTable(1, "!A");
    cout << "\nConjunctie (AND):\n";
    TruthTable(2, "A & B");
    cout << "\nDisjunctie (OR):\n";
    TruthTable(2, "A | B");
    cout << "\nDiferenta (XOR):\n";
    TruthTable(2, "A & (!B)");
    cout << "\nDiferenta simetrica (XNOR):\n";
    TruthTable(2, "A ^ B");
    cout << "\n (NOR):\n";
    TruthTable(2, "!(A | B)");
    cout << "\n (NAND):\n";
    TruthTable(2, "!(A & B)");
    cout << "\nImplicatia (A -> B):\n";
    TruthTable(2, "((!A) | B)");
    cout << "\nEchivalenta (A <=> B):\n";
    TruthTable(2, "(A = B)");

    TruthTable(3, "A & B | (!C)");

    TruthTable(4, "!(A & B ^ (!C) | D)");
    return 0;
}