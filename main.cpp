#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include "./expression_generator.cpp"
using namespace std;

void showCommands() {
    cout << "Type command\n"
         << "1 -------- Check is logic expression valid\n"
         << "2 -------- Start quiz\n"
         << "3 -------- Show commands list\n"
         << "4 -------- Exit\n";
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
                exitFlag = true;
                break;
            }
            default: {
                cout << "Command " << command << "doesn't exist\n";
            }
        }
    }
}