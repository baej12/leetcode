#include <iostream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

vector<string> letterCombinations(string);
void solve(vector<string>&, int, string, string);

map<char, string> combinations{
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}
};

vector<string> letterCombinations(string digits) {

    vector<string> solution;
    vector<string> allPossibleChar;

    for (auto i : digits) {
        allPossibleChar.push_back(combinations[i]);
    }

    solve(solution, 0, "", digits);

    return solution;
}

void solve(vector<string>& solutions, int i, string currentStr, string digits) {
    if (currentStr.length() == digits.length()) {
        if (currentStr != "")
            solutions.push_back(currentStr);
        return;
    }

    for (auto c : combinations[digits[i]]) {
        solve(solutions, i + 1, currentStr + c, digits);
    }
}


int main () {
    vector<string> solution = letterCombinations("23");

    for (int i = 0; i < solution.size(); ++i) {
        cout << solution[i] << endl;
    }

    return 0;
}