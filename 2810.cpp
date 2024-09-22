#include <./stdc++11.h>

using namespace std;

string finalString(string s) {
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == 'i') {
            reverse(s.begin(), s.begin() + i);
            s.erase(i--, 1);
        }
    }

    return s;
}

int main() {
    cout << finalString("poiinter") << endl;
    cout << finalString("string") << endl;

    return 0;
}