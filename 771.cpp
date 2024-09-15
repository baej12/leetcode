#include <./stdc++11.h>

using namespace std;

int numJewelsInStones(string jewels, string stones) {
    map<char, bool> jewelChar;
    int solution = 0;

    for (auto i : jewels)
        jewelChar[i] = true;

    for (auto i : stones)
        if (jewelChar[i])
            ++solution;

    return solution;   
}

int main () {

    return 0;
}