#include <./stdc++11.h>

using namespace std;

vector<vector<int>> findMatrix(vector<int>& nums) {
    vector<vector<int>> sol{nums.size(), vector<int>{}};
    map<int, int> dup;
    int maxRow = 0;

    for (auto i : nums) {
        sol[dup[i]++].push_back(i);
        maxRow = max(dup[i], maxRow);
    }

    sol.erase(sol.begin() + maxRow, sol.end());

    return sol; 
}

int main() {
    vector<int> test1{1,3,4,1,2,3,1};
    auto sol1 = findMatrix(test1);

    for (auto i : sol1) {
        for (auto n : i)
            cout << n << ", ";
        cout << endl;
    }

    return 0;
}