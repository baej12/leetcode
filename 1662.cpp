#include <./stdc++11.h>

using namespace std;

bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
    string cs = "";
    string cs2 = "";

    for (auto s : word1)
        cs += s;

    for (auto s : word2)
        cs2 += s;

    return cs == cs2;
}

int main() {
    return 0;
}