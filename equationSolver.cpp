#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <cctype> 
using namespace std;
int precedence(char c) {
    switch (c)
    {
    case '+':return 1;
    case '-': return 1;
    case '*':return 2;
    case '/': return 2;
    default:return -1;
    }
}
double operationExe(double val1, double val2, char opertr) {

    if (opertr == '+') {
        return (val1 + val2);
    }
    else if (opertr == '-') {
        return (val1 - val2);
    }
    else if (opertr == '*') {
        return (val1 * val2);
    }
    else if (opertr == '/') {
        if (val2 == 0) {
            cout << "division by Zero";
            return 0;
        }
        return(val1 / val2);
    }


}
bool isOpter(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    else
        return false;
}
bool isClosingBracket(char c) {
    if (c == ')' || c == ']' || c == '}')
        return true;
    else
        return false;
}
bool isOpeningBracket(char c) {
    if (c == '(' || c == '[' || c == '{')
        return true;
    else
        return false;
}
bool CompareBrackets(char close, char open) {

    if (close == ')' && open == '(') {
        return true;
    }
    else if (close == '}' && open == '{') {
        return true;
    }
    else if (close == ']' && open == '[') {
        return true;
    }
    else {
        return false;
    }

}
double evaluate(string exp) {
    int pos = 0;
    stack <double> values;
    stack <char> op;
    for (pos = 0; pos < exp.length(); pos++) {
        char st = exp[pos];
        if (isOpeningBracket(st)) {
            op.push(st);
        }
        else if (isdigit(st)) {

            double val = 0;
            if (isdigit(exp[pos + 1])) {
                while (pos < exp.length() && isdigit(exp[pos])) {

                    val = (val * 10.0) + (double)(exp[pos] - '0');
                    pos++;

                }

                pos--;
            }
            else {
                val = (double)(exp[pos] - '0');
            }

            values.push(val);
        }
        else if (isOpter(st)) {
            if (!(op.empty())) {
                if (precedence(st) < precedence(op.top())) {
                    double val1 = values.top();
                    values.pop();
                    double val2 = values.top();
                    values.pop();
                    char opter = op.top();
                    op.pop();
                    values.push(operationExe(val1, val2, opter));
                    op.push(st);
                }
                else {
                    op.push(st);
                }
            }
            else {
                op.push(st);

            }

        }
        else if (isClosingBracket(st)) {
            if (!op.empty()) {
                while (!isOpeningBracket((op.top()))) {
                    double val2 = values.top();
                    values.pop();
                    double val1 = values.top();
                    values.pop();
                    char opter = op.top();
                    if (isOpter(opter)) {
                        values.push(operationExe(val1, val2, opter));
                        op.pop();
                    }

                }
                if (isOpeningBracket(op.top()) && CompareBrackets(st, op.top())) {
                    op.pop();
                }
                else {
                    cout << "Imbalance bracket ";
                    return 0;
                }
            }
            else {
                cout << " Imbalance bracket ";
                return 0;
            }
        }
    }

    return values.top();

}


int main() {
    string exp;
    cout << "enter math expression " << endl;
    cin >> exp;
    string f = "(" + exp + ")";
    double res = evaluate(f);
    cout << "Result: " << res << endl;



}