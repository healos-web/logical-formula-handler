#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include "./expression_generator.cpp"
#include "./formula_calculator.cpp"
#include <vector>
using namespace std;

void showCommands() {
    cout << "Type command\n"
         << "1 -------- Check is logic expression valid\n"
         << "2 -------- Start quiz\n"
         << "3 -------- Show commands list\n"
         << "4 -------- Check is one formula follows from another\n"
         << "5 -------- Exit\n";
}

int main() {
    int command;
    int taskNumber;
    boost::regex expression("(([A-Z10])|(\\(\\!(?1)\\))|(\\(((?1)([&|~]|(->))(?1))\\)))");
    string string_to_match;
    bool exitFlag = false;

    srand (time(NULL));
    showCommands();

    while (!exitFlag) {
        cin >> command;

        switch (command) {
            case 1: {
                cout << "Enter the expression to match\n";
                cin >> string_to_match;

                if (regex_match(string_to_match, expression)) {
                    cout << "Valid expression\n";
                } else {
                    cout << "Error, your expression is not a valid logic formula\n";
                }
                break;
            }
            case 2: {
                cout << "Enter the number of tasks\n";
                cin >> taskNumber;
                cout << "QUIZ STARTED\n";

                int score = 0;
                for (int i = 0; i < taskNumber; i++) {

                    cout << "Progress " << i + 1 << " from " << taskNumber << "\n";
                    string task = generateGroup();
                    cout << "Does this expression correct?\n";
                    cout << task << "\n";

                    string answer;
                    cin >> answer;

                    bool isCorrectExp = regex_match(task, expression);

                    if (isCorrectExp) {
                        if (answer == "yes") {
                            cout << "You are right!";
                            score++;
                        } else {
                            cout << "Sorry, but you've made a mistake";
                        }
                    } else {
                        if (answer == "no") {
                            cout << "You are right!";
                            score++;
                        } else {
                            cout << "Sorry, but you've made a mistake";
                        }
                    }
                    cout << "\n\n";
                }

                cout << "Your final score is " << score << " right answers from " << taskNumber << "\n";
                break;
            }
            case 3: {
                showCommands();
                break;
            }
            case 4: {
                string formula_1;
                string formula_2;

                cout << "Enter first formula\n";

                while (true) {
                    cin >> formula_1;

                    if (!regex_match(formula_1, expression)) {
                        cout << "Formula 1 doesn't follow logical formula syntax please try again";
                        continue;
                    } else {
                        break;
                    }
                };

                while (true) {
                    cin >> formula_2;

                    if (!regex_match(formula_2, expression)) {
                        cout << "Formula 2 doesn't follow logical formula syntax please try again";
                        continue;
                    } else {
                        break;
                    }
                };

                vector<char> variables = extractVariables(formula_1, formula_2);
                vector<vector<int>> cases = generateCases(variables.size());
                vector<int> formulaValues_1 = calculate(formula_1, cases);
                vector<int> formulaValues_2 = calculate(formula_2, cases);

                if (isFollowing(formulaValues_1, formulaValues_2)) {
                    cout << "Formula 2 follows from Formula 1\n";
                } else {
                    cout << "Formula 2 doesn't follow from Formula 1\n";
                }

                cout << "See final values matrix:\n";
                for(int i; i < formulaValues_1.size(); i++) {
                    cout << formulaValues_1[i] << " --- " << formulaValues_2[i] << "\n";
                };

                break;
            }
            case 5: {
                exitFlag = true;
                break;
            }
            default: {
                cout << "Command " << command << "doesn't exist\n";
            }
        }
    }
}