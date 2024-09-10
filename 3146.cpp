#include <./stdc++11.h>

using namespace std;

int findPermutationDifference(string s, string t) {
    int solution = 0;
    map<int, int> charIndex;

    for (int i = 0; i < s.length(); ++i) {
        charIndex[s[i]] = i;
    }

    for (int i = 0; i < t.length(); ++i) {
        solution += abs(i - charIndex[t[i]]);
    }

    return solution;
}

int main() {
    cout << findPermutationDifference("abc", "bac") << endl;

    return 0;
}