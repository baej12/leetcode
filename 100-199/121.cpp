/*
 * LeetCode Problem #121
 * Title: Best Time to Buy and Sell Stock
 * Difficulty: Easy
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 *
 * Description:
 * 
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 *  
 * Example 1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 * Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
 * Example 2:
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transactions are done and the max profit = 0.
 *  
 * Constraints:
 * 	1 <= prices.length <= 105
 * 	0 <= prices[i] <= 104
 *
 * Example Test Cases:
 * [7,1,5,3,6,4]
 * [7,6,4,3,1]
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
    int maxProfit(vector<int>& prices) {
        
    }
};

int main() {
    Solution sol;
    
    // Read input
    string line;
    getline(cin, line);
    
    // Parse input (modify based on problem requirements)
    vector<int> nums;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        stringstream ss(content);
        string num;
        while (getline(ss, num, ',')) {
            nums.push_back(stoi(num));
        }
    }
    
    // Call solution and output result
    // TODO: Modify based on function signature
    // cout << sol.functionName(args) << endl;
    
    return 0;
}
