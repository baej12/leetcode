#include <./stdc++11.h>

using namespace std;

int solve(int m, int n, vector<vector<int>> & memo) {
    if (m == 1 || n == 1) {
        return memo[m][n] = 1;
    }

    if (memo[m][n] == 0) {
        memo[m][n] = solve(m - 1, n, memo) + solve(m, n - 1, memo);
    }

    return memo[m][n];
}

int uniquePaths(int m, int n) {
    // if (m == 1 || n == 1) {
    //     return 1;
    // }

    // return uniquePaths(m-1, n) + uniquePaths(m, n - 1);
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, 0));
    return solve(m, n, memo);
}

int main() {

    return 0;
}