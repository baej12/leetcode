/*
 * LeetCode Problem #206
 * Title: Reverse Linked List
 * Difficulty: Easy
 * https://leetcode.com/problems/reverse-linked-list/
 *
 * Description:
 * 
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 *  
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 * Example 2:
 * Input: head = [1,2]
 * Output: [2,1]
 * Example 3:
 * Input: head = []
 * Output: []
 *  
 * Constraints:
 * 	The number of nodes in the list is the range [0, 5000].
 * 	-5000 <= Node.val <= 5000
 *  
 * Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
 *
 * Example Test Cases:
 * [1,2,3,4,5]
 * [1,2]
 * []
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
    ListNode* reverseList(ListNode* head) {
        
    }
};

int main() {
    Solution sol;
    
    // Read input - linked list format: [1,2,3,4,5]
    string line;
    getline(cin, line);
    
    // Parse array
    vector<int> values;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        if (!content.empty()) {
            stringstream ss(content);
            string num;
            while (getline(ss, num, ',')) {
                values.push_back(stoi(num));
            }
        }
    }
    
    // Build linked list
    ListNode* head = nullptr;
    if (!values.empty()) {
        head = new ListNode(values[0]);
        ListNode* current = head;
        for (size_t i = 1; i < values.size(); i++) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
    }
    
    // Call solution
    // TODO: Modify based on function signature
    // ListNode* result = sol.functionName(head);
    
    // Output result
    // TODO: Print result in correct format
    
    // Cleanup
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}
