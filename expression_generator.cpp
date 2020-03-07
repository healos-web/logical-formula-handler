#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

string generateOperation() {
    string variationOptions[] = {"&", "|", "->", "~", "<>", "$$"};

    int variation = rand() % variationOptions->length();
    return variationOptions[variation];
}

string generateConstant() {
    string variations = "QWERTYUIOPASDFGHJKLZXCVBNM01yj;h@@$$";

    int num = rand() % variations.length();
    string constant = "";
    constant.push_back(variations[num]);
    return constant;
}

string generateSimpleGroup(string group) {
    return "(!" + group + ")";
}

string generateComplexGroup(string group1, string group2) {
   return "(" + group1 + generateOperation() + group2 + ")";
}

string generateGroup() {
    int groupType = rand() % 3;

    switch (groupType) {
        case 0: {
            return generateConstant();
        }
        case 1: {
            string group = generateGroup();
            return generateSimpleGroup(group);
        }
        case 2: {
            string group1 = generateGroup();
            string group2 = generateGroup();
            return generateComplexGroup(group1, group2);
        }
    }
}

