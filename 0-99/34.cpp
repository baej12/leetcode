/*
 * LeetCode Problem #34
 * Title: Find First and Last Position of Element in Sorted Array
 * Difficulty: Medium
 * https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * Description:
 * 
 * Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
 * If target is not found in the array, return [-1, -1].
 * You must write an algorithm with O(log n) runtime complexity.
 *  
 * Example 1:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 * Example 2:
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 * Example 3:
 * Input: nums = [], target = 0
 * Output: [-1,-1]
 *  
 * Constraints:
 * 	0 <= nums.length <= 105
 * 	-109 <= nums[i] <= 109
 * 	nums is a non-decreasing array.
 * 	-109 <= target <= 109
 *
 * Example Test Cases:
 * [5,7,7,8,8,10]
 * 8
 * [5,7,7,8,8,10]
 * 6
 * []
 * 0
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
    vector<int> searchRange(vector<int>& nums, int target) {
        // Binary search for the first occurence of target
        int left = 0, right = nums.size() - 1;
        int first = -1, last = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                first = mid;
                right = mid - 1; // Continue searching in the left half
            }
        }

        // Binary search for the last occurence of target
        left = 0;
        right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                last = mid;
                left = mid + 1; // Continue searching in the right half
            }
        }

        return {first, last};
    }
};

int main() {
    Solution sol;
    string line;

    // Parse vector<int>
    vector<int> nums;
    getline(cin, line);
    {
        size_t start = line.find('[');
        size_t end = line.find(']');
        if (start != string::npos && end != string::npos) {
            string content = line.substr(start + 1, end - start - 1);
            if (!content.empty()) {
                stringstream ss(content);
                string num;
                while (getline(ss, num, ',')) {
                    nums.push_back(stoi(num));
                }
            }
        }
    }

    int target;
    getline(cin, line);
    target = stoi(line);

    // Call solution and output result
    vector<int> result = sol.searchRange(nums, target);
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        if (i > 0) cout << ",";
        cout << result[i];
    }
    cout << "]" << endl;
    
    return 0;
}

