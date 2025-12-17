/*
 * LeetCode Problem #53
 * Title: Maximum Subarray
 * Difficulty: Medium
 * https://leetcode.com/problems/maximum-subarray/
 *
 * Description:
 * 
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 *  
 * Example 1:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 * Example 2:
 * Input: nums = [1]
 * Output: 1
 * Explanation: The subarray [1] has the largest sum 1.
 * Example 3:
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 * Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 *  
 * Constraints:
 * 	1 <= nums.length <= 105
 * 	-104 <= nums[i] <= 104
 *  
 * Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
 *
 * Example Test Cases:
 * [-2,1,-3,4,-1,2,1,-5,4]
 * [1]
 * [5,4,-1,7,8]
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
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        } else if (nums.size() == 1) {
            return nums[0];
        }

        int currMax = nums[0];

        for (int y = 0; y < nums.size(); ++y) {
            int currSum = nums[y];
            for (int x = y + 1; x < nums.size(); ++x) {
                currSum += nums[x];
                currMax = max(currSum, currMax);
            }
        }

        return currMax;
    }
};

int main() {
    Solution sol;
    
    // Read input array
    string line;
    getline(cin, line);
    
    // Parse array from format like [-2,1,-3,4,-1,2,1,-5,4]
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
    
    // Solve and output
    int result = sol.maxSubArray(nums);
    cout << result << endl;
    
    return 0;
}
