#include <./stdc++11.h>

using namespace std;

vector<int> findWordsContaining(vector<string>& words, char x) {
    vector<int> sol;

    for (size_t i = 0; i < words.size(); ++i) {
        for (size_t n = 0; n < words[i].size(); ++n) {
            if (words[i][n] == x) {
                sol.push_back(i);
                break;
            }
        }
    }

    return sol;
}

int main() {
    return 0;
}