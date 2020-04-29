#include <string>
#include <vector>
#include <regex>
using namespace std;

// takes two strings that should be valid logical formulas,then search variables in these strings and returns vector
// that contains them in alphabetical order
vector<string> extractVariables(string formula_1, string formula_2) {
    vector<string> vec;

    regex rgx("[A-Z]");
    smatch match;

    while (regex_search(formula_1, match, rgx)) {
        vec.push_back(match.str(0));

        formula_1 = match.suffix().str();
    }

    while (regex_search(formula_2, match, rgx)) {
        vec.push_back(match.str(0));

        formula_2 = match.suffix().str();
    }

    sort(vec.begin(), vec.end());
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    return vec;
}

// returns 2-dimension matrix with provided size, values are all possible options of binary numbers with provided number
// of digits
vector<vector<int>> generateCases(int variablesNumber) {
    vector<vector<int>> vec;

    int n = 0;
    while(true) {
        vector<int> vector;

        int x = n;
        for(int i=0; x>0; i++)
        {
            vector.push_back(x%2);
            x = x/2;
        }

        if (vector.size() == variablesNumber + 1) {
            break;
        }

        while (vector.size() != variablesNumber) {
            vector.insert(vector.begin(), 0);
        }

        vec.push_back(vector);
        n++;
    }

    return vec;
}

// replace variables by possible cases in string logical formula, then calculate formula values and return results vector
vector<string> calculate(string formula, vector<vector<int>> cases, vector<string> variables) {
    vector<string> vec;

    for (int i = 0; i < cases.size(); i++) {
        // replace variables
        string str = formula;
        for(int j = 0; j < variables.size(); j++) {
            regex var(variables[j]);
            str = regex_replace(str, var, to_string(cases[i][j]));
        }

        // main cycle
        regex andOp("(1)(?=(&(?=(1|0))))&(1|0)|(0)(?=(&(?=(1|0))))&(1|0)");
        regex orOp("(1)(?=(\\|(?=(1|0))))\\|(1|0)|(0)(?=(\\|(?=(1|0))))\\|(1|0)");
        regex eqPosOp("(1~1)|(0~0)");
        regex eqNegOp("(1~0)|(0~1)");
        regex impPosOp("(1->1)|(0->1)|(0->0)");
        regex impNegOp("(1->0)");
        regex braces("\\((1|0)\\)");
        regex negPosOp("!0");
        regex negNegOp("!1");
        while(str.length() != 1) {
            // replace complex formules
            str = regex_replace(str, andOp, "$1$7");
            str = regex_replace(str, orOp, "$1$7");
            str = regex_replace(str, eqPosOp, "1");
            str = regex_replace(str, eqNegOp, "0");
            str = regex_replace(str, impPosOp, "1");
            str = regex_replace(str, impNegOp, "0");

            // replace braces
            str = regex_replace(str, braces, "$1");

            // replace negatives
            str = regex_replace(str, negPosOp, "1");
            str = regex_replace(str, negNegOp, "0");
        }

        // push back result
        vec.push_back(str);
    }

    return vec;
}

// checks is one formula is foll4owing from another; print all possible values that formulas can be calculated
bool isFollowing(string formula_1, string formula_2, bool showFinalResults) {
    vector<string> variables = extractVariables(formula_1, formula_2);
    vector<vector<int>> cases = generateCases(variables.size());
    vector<string> formulaValues_1 = calculate(formula_1, cases, variables);
    vector<string> formulaValues_2 = calculate(formula_2, cases, variables);

    if (showFinalResults) {
        cout << "See final values matrix:\n";
        for (int i = 0; i < formulaValues_1.size(); i++) {
            cout << formulaValues_1[i] << " --- " << formulaValues_2[i] << "\n";
        };
    }

    for(int i = 0; i < formulaValues_1.size(); i++) {
        if (formulaValues_1[i] == "1" && formulaValues_2[i] == "0") {
           return false;
        }
    }

    return true;
};



