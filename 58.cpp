#include <iostream>

using namespace std;

int lengthOfLastWord(string s) {
    int solution = 0;

    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] != ' ') {
            for (int n = i; n >= 0 && s[n] != ' '; --n, ++solution){}
            break;
        }
    }

    return solution;
}

int main () {
    string s = "Hello World";

    cout << lengthOfLastWord(s) << endl;

    return 0;
}