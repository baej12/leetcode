#include <./stdc++11.h>

using namespace std;

int mostWordsFound(vector<string>& sentences) {
    int sol = 0;

    for (auto i : sentences) {
        int count = 1;

        for (auto c : i) {
            if (c == ' ')
                ++count;
        }

        sol = max(sol, count);
    }

    return sol;
}

int main() {
    return 0;
}