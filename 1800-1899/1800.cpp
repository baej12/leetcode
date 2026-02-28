/*
 * LeetCode Problem #1800
 * Title: Concatenation of Consecutive Binary Numbers
 * Difficulty: Medium
 * https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
 *
 * Description:
 * 
 * Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.
 *  
 * Example 1:
 * Input: n = 1
 * Output: 1
 * Explanation: "1" in binary corresponds to the decimal value 1. 
 * Example 2:
 * Input: n = 3
 * Output: 27
 * Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
 * After concatenating them, we have "11011", which corresponds to the decimal value 27.
 * Example 3:
 * Input: n = 12
 * Output: 505379714
 * Explanation: The concatenation results in "1101110010111011110001001101010111100".
 * The decimal value of that is 118505380540.
 * After modulo 109 + 7, the result is 505379714.
 *  
 * Constraints:
 * 	1 <= n <= 105
 *
 * Example Test Cases:
 * 1
 * 3
 * 12
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
#include <bitset>
#include <cmath>

using namespace std;

class Solution {
public:
    int concatenatedBinary(int n) {
        const long long MOD = 1000000007;
        long long result = 0;
        int bitsNeeded = 0;  // Track current bit length
        
        // Process each number from 1 to n
        for (int i = 1; i <= n; ++i) {
            // Optimization: Only increment bits when we hit a power of 2
            // Powers of 2 have exactly one 1 bit: 1, 10, 100, 1000, etc.
            // The trick: i & (i-1) removes the rightmost 1 bit
            // For powers of 2, this gives 0 (e.g., 8=1000 & 7=0111 = 0)
            // Examples: 1→1 bit, 2-3→2 bits, 4-7→3 bits, 8-15→4 bits
            if ((i & (i - 1)) == 0) {
                bitsNeeded++;
            }
            
            // Shift left to make space, then OR to append, then apply modulo
            // Example: if result=5 (binary: 101), i=3 (binary: 11), bitsNeeded=2:
            //   Step: result << 2 = 10100 (shift left)
            //   Step: 10100 | 11 = 10111 (OR in the new number)
            //   Step: 10111 % MOD (apply modulo to keep number manageable)
            result = ((result << bitsNeeded) | i) % MOD;
        }
        
        return result;
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

    auto result = sol.concatenatedBinary(n);
    cout << result << endl;
    return 0;
}
