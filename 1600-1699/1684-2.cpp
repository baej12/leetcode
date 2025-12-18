#include <./stdc++11.h>

using namespace std;

int countConsistentStrings(string allowed, vector<string>& words) {
    map<char, bool> validChar;
    int solution = words.size();

    for (auto i : allowed)
        validChar[i] = true;

    for (auto i : words) {
        for (auto c : i) {
            if (!validChar[c]) {
                --solution;
                break;
            }
        }
    }

    return solution;
}

int main() {
    return 0;
}