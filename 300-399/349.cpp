/*
 * LeetCode Problem #349
 * Title: Intersection of Two Arrays
 * Difficulty: Easy
 * https://leetcode.com/problems/intersection-of-two-arrays/
 *
 * Description:
 * 
 * Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
 *  
 * Example 1:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * Example 2:
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 * Explanation: [4,9] is also accepted.
 *  
 * Constraints:
 * 	1 <= nums1.length, nums2.length <= 1000
 * 	0 <= nums1[i], nums2[i] <= 1000
 *
 * Example Test Cases:
 * [1,2,2,1]
 * [2,2]
 * [4,9,5]
 * [9,4,9,8,4]
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
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> resultSet;
        
        for (int num : nums2) {
            if (set1.count(num)) {
                resultSet.insert(num);
            }
        }
        
        return vector<int>(resultSet.begin(), resultSet.end());
    }
};

int main() {
    Solution sol;
    string line;

    // Parse vector<int>
    vector<int> nums1;
    getline(cin, line);
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        if (!content.empty()) {
            stringstream ss(content);
            string num;
            while (getline(ss, num, ',')) {
                nums1.push_back(stoi(num));
            }
        }
    }

    vector<int> nums2;
    getline(cin, line);
    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        if (!content.empty()) {
            stringstream ss(content);
            string num;
            while (getline(ss, num, ',')) {
                nums2.push_back(stoi(num));
            }
        }
    }

    // Call solution and output result
    vector<int> result = sol.intersection(nums1, nums2);
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        if (i > 0) cout << ",";
        cout << result[i];
    }
    cout << "]" << endl;
    
    return 0;
}

