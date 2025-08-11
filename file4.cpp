#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class SimpleCompiler {
    string expr;
    size_t pos = 0;

    char peek() {
        return (pos < expr.length()) ? expr[pos] : '\0';
    }

    char get() {
        return (pos < expr.length()) ? expr[pos++] : '\0';
    }

    void skipSpaces() {
        while (isspace(peek())) get();
    }

    double number() {
        skipSpaces();
        double result = 0;
        while (isdigit(peek())) {
            result = result * 10 + (get() - '0');
        }

        if (peek() == '.') {
            get(); // skip '.'
            double frac = 0.1;
            while (isdigit(peek())) {
                result += (get() - '0') * frac;
                frac *= 0.1;
            }
        }

        return result;
    }

    double factor() {
        skipSpaces();
        if (peek() == '(') {
            get(); // consume '('
            double result = expression();
            skipSpaces();
            if (peek() == ')') get(); // consume ')'
            return result;
        } else {
            return number();
        }
    }

    double term() {
        double result = factor();
        while (true) {
            skipSpaces();
            if (peek() == '*') {
                get();
                result *= factor();
            } else if (peek() == '/') {
                get();
                result /= factor();
            } else {
                break;
            }
        }
        return result;
    }

    double expression() {
        double result = term();
        while (true) {
            skipSpaces();
            if (peek() == '+') {
                get();
                result += term();
            } else if (peek() == '-') {
                get();
                result -= term();
            } else {
                break;
            }
        }
        return result;
    }

public:
    double evaluate(const string& input) {
        expr = input;
        pos = 0;
        return expression();
    }
};

int main() {
    SimpleCompiler compiler;
    string input;

    cout << "Enter expression (or type 'exit'):\n";
    while (true) {
        cout << "> ";
        getline(cin, input);
        if (input == "exit") break;

        double result = compiler.evaluate(input);
        cout << "Result: " << result << endl;
    }

    return 0;
}
