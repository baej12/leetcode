#include <./stdc++11.h>

using namespace std;

int countConsistentStrings(string allowed, vector<string>& words) {
    map<char, bool> validChar;
    int solution = 0;

    for (auto i : allowed)
        validChar[i] = true;

    for (auto i : words) {
        bool valid = true;

        for (auto c : i) {
            if (!validChar[c]) {
                valid = false;
                break;
            }
        }

        if (valid)
            ++solution;
    }

    return solution;
}

int main() {
    return 0;
}