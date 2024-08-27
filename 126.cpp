#include <./stdc++11.h>

using namespace std;

bool isPalindrome(string s) {
    string cleanStr = "";
    stack<char> reverseStr;

    for (size_t i = 0; i < s.length(); ++i) {
        if ((s[i] >= 97 && s[i] <= 122) || (s[i] >= 48 && s[i] <= 57) || (s[i] >= 65 && s[i] <= 90)) {
            cleanStr += tolower(s[i]);
            reverseStr.push(tolower(s[i]));
        }
    }

    for (size_t i = 0; i < cleanStr.length(); ++i, reverseStr.pop()) {
        if (cleanStr[i] != reverseStr.top()) {
            return false;
        }
    }

    return true;
}

int main () {
    cout << isPalindrome("race a car") << endl;
    cout << isPalindrome("A man, a plan, a canal: Panama") << endl;
    cout << isPalindrome("0P") << endl;
    cout << isPalindrome("ab_a") << endl;

    return 0;
}