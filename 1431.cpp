#include <./stdc++11.h>

using namespace std;

vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    vector<bool> sol;
    int maxN = candies[0];

    for (auto i : candies) {
        maxN = max(maxN, i);
    }   

    for (auto i : candies) {
        sol.push_back(i + extraCandies >= maxN);
    }

    return sol;
}

int main() {
    return 0;
}