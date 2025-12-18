/*
 * LeetCode Problem #21
 * Title: Merge Two Sorted Lists
 * Difficulty: Easy
 * https://leetcode.com/problems/merge-two-sorted-lists/
 *
 * Description:
 * 
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
 * Return the head of the merged linked list.
 *  
 * Example 1:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 * Example 2:
 * Input: list1 = [], list2 = []
 * Output: []
 * Example 3:
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 *  
 * Constraints:
 * 	The number of nodes in both lists is in the range [0, 50].
 * 	-100 <= Node.val <= 100
 * 	Both list1 and list2 are sorted in non-decreasing order.
 *
 * Example Test Cases:
 * [1,2,4]
 * [1,3,4]
 * []
 * []
 * []
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

// Data structure definition(s)
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
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
