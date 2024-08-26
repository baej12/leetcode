#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    stack<ListNode*> nodes;
    ListNode * itr = head;
    ListNode * forward = NULL;

    for (ListNode * itr = head; itr != NULL; itr = itr->next) {
        nodes.push(itr);
    }

    for (int i = 1; i < n; ++i) {
        forward = nodes.top();
        nodes.pop();
    }

    if (!nodes.empty()) {
        nodes.pop();
        if (!nodes.empty()) {
            nodes.top()->next = forward;
        } else {
            head = forward;
        }
    }

    return head;
}

int main() {
    ListNode * test = new ListNode(0, new ListNode(1, new ListNode(2, new ListNode(3))));
    ListNode * sol = removeNthFromEnd(test, 4);

    for (ListNode * itr = sol; itr != NULL; itr = itr->next) {
        cout << itr->val << " -> ";
    } cout << endl;

    return 0;
}