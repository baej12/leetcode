/*
 * LeetCode Problem #42
 * Title: Trapping Rain Water
 * Difficulty: Hard
 * https://leetcode.com/problems/trapping-rain-water/
 *
 * Description:
 * 
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
 *  
 * Example 1:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
 * Example 2:
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *  
 * Constraints:
 * 	n == height.length
 * 	1 <= n <= 2 * 104
 * 	0 <= height[i] <= 105
 *
 * Example Test Cases:
 * [0,1,0,2,1,0,1,3,2,1,2,1]
 * [4,2,0,3,2,5]
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
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        
        vector<int> leftMax(n), rightMax(n);
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i-1], height[i]);
        }
        
        rightMax[n-1] = height[n-1];
        for (int i = n-2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i+1], height[i]);
        }
        
        int water = 0;
        for (int i = 0; i < n; i++) {
            water += min(leftMax[i], rightMax[i]) - height[i];
        }
        
        return water;
    }
};

int main() {
    Solution sol;
    
    // Read input array like [0,1,0,2,1,0,1,3,2,1,2,1]
    string line;
    getline(cin, line);
    
    // Parse array
    vector<int> height;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        stringstream ss(content);
        string num;
        while (getline(ss, num, ',')) {
            height.push_back(stoi(num));
        }
    }
    
    // Solve
    int result = sol.trap(height);
    
    // Output
    cout << result << endl;
    
    return 0;
}
