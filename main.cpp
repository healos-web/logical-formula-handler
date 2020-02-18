#include <iostream>
#include <string>
#include <boost/regex.hpp>
using namespace std;

int main() {
    string string_to_match;

    while (true) {
        cout << "Enter the expression to match\n";
        cin >> string_to_match;

        if (string_to_match == "STOP") {
            break;
        };

        boost::regex expression("(([A-Z10])|(\\(\\!(?1)\\))|(\\(((?1)([&|~]|(->))(?1))\\)))");

        if (regex_match(string_to_match, expression)) {
            cout << "Valid expression";
        } else {
            cout << "Error, your expression is not a valid logic formula";
        }
    }
}