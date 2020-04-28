#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

// returns random formula operation;
// if parameter 'withNoise' is set to True, it might return wrong symbols
string generateOperation(bool withNoise) {
    vector<string> variationOptions = {"&", "|", "->", "~"};

    if (withNoise) {
        variationOptions.push_back("<>");
        variationOptions.push_back("$$");
    }
    int variation = rand() % variationOptions.size();
    return variationOptions[variation];
}

// returns random variable letter or constant;
// if parameter `withNoise` is set to True, it might return wrong symbols
string generateConstant(bool withNoise) {
    string variations = "QWERTYUIOPASDFGHJKLZXCVBNM01";

    if (withNoise) {
       variations += "yj;h@@$$";
    }

    int num = rand() % variations.length();
    string constant = "";
    constant.push_back(variations[num]);
    return constant;
}

// returns string that is represent simple logical formula group
string generateSimpleGroup(string group) {
    return "(!" + group + ")";
}

// returns string that is represent complex logical formula group
string generateComplexGroup(string group1, string group2, bool withNoise) {
   return "(" + group1 + generateOperation(withNoise) + group2 + ")";
}

// returns string that is represent logical formula;
// if parameter 'withNoise' is set to True, it might return formula with incorrect syntax
string generateGroup(bool withNoise) {
    int groupType = rand() % 3;

    switch (groupType) {
        case 0: {
            return generateConstant(withNoise);
        }
        case 1: {
            string group = generateGroup(withNoise);
            return generateSimpleGroup(group);
        }
        case 2: {
            string group1 = generateGroup(withNoise);
            string group2 = generateGroup(withNoise);
            return generateComplexGroup(group1, group2, withNoise);
        }
    }
}

