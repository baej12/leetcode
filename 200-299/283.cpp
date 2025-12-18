/*
 * LeetCode Problem #283
 * Title: Move Zeroes
 * Difficulty: Easy
 * https://leetcode.com/problems/move-zeroes/
 *
 * Description:
 * 
 * Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
 * Note that you must do this in-place without making a copy of the array.
 *  
 * Example 1:
 * Input: nums = [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 * Example 2:
 * Input: nums = [0]
 * Output: [0]
 * Example 3:
 * Input: nums = [4,2,4,0,0,3,0,5,1,0]
 * Output: [4,2,4,3,5,1,0,0,0,0]
 *  
 * Constraints:
 * 	1 <= nums.length <= 104
 * 	-231 <= nums[i] <= 231 - 1
 *  
 * Follow up: Could you minimize the total number of operations done?
 *
 * Example Test Cases:
 * [0,1,0,3,12]
 * [0]
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
    void moveZeroes(vector<int>& nums) {
        for (int i = 0, n = i + 1; i < nums.size() && n < nums.size(); ++i) {
            if (nums[i] == 0) {
                for (n = n > i ? n : i + 1; n < nums.size(); ++n) {
                    if (nums[n] != 0) {
                        nums[i] = nums[n];
                        nums[n] = 0;
                        break;
                    }
                }
            }
        }
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
    sol.moveZeroes(nums);
    // Print out nums
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0) cout << ",";
        cout << nums[i];
    }
    cout << "]" << endl;
    
    return 0;
}
