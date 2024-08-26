#include <iostream>

class Solution {
public:
//Memoization
    int * dp;

    Solution() {
        this->dp = new int[38];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;
        for (int i = 3; i < 38; ++i) {
            dp[i] = -1;
        }
    }

    int tribonacci(int n) {
        if (dp[n] != -1)
            return dp[n];

        dp[n-1] = tribonacci(n-1);
        dp[n-2] = tribonacci(n-2);
        dp[n-3] = tribonacci(n-3);

        return dp[n-1] + dp[n-2] + dp[n-3];
    }
};

int main () {
    using namespace std;

    Solution * test = new Solution();

    cout << test->tribonacci(4) << endl;

    return 0;
}