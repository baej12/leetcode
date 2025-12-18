/*
 * LeetCode Problem #231
 * Title: Power of Two
 * Difficulty: Easy
 * https://leetcode.com/problems/power-of-two/
 *
 * Description:
 * 
 * Given an integer n, return true if it is a power of two. Otherwise, return false.
 * An integer n is a power of two, if there exists an integer x such that n == 2x.
 *  
 * Example 1:
 * Input: n = 1
 * Output: true
 * Explanation: 20 = 1
 * Example 2:
 * Input: n = 16
 * Output: true
 * Explanation: 24 = 16
 * Example 3:
 * Input: n = 3
 * Output: false
 *  
 * Constraints:
 * 	-231 <= n <= 231 - 1
 *  
 * Follow up: Could you solve it without loops/recursion?
 *
 * Example Test Cases:
 * 1
 * 16
 * 3
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        
    }
};

int main() {
    Solution sol;
    string line;

    // Example input (uncomment #define to test directly):
    // #define USE_EXAMPLE_INPUT

#ifdef USE_EXAMPLE_INPUT
    int n = 1;
#else
    getline(cin, line);
    int n = stoi(line);
#endif

    auto result = sol.isPowerOfTwo(n);
    cout << (result ? "true" : "false") << endl;
    return 0;
}
