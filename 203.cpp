#include <./stdc++11.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* removeElements(ListNode* head, int val) {
    if (head == NULL) {
        return NULL;
    }

    if (head->val == val) {
        while (head != NULL && head->val == val) {
            head = head->next;
        }

        if (head == NULL) {
            return NULL;
        }
    }

    ListNode * previous = head;

    for (ListNode * itr = head->next; itr != NULL; itr = itr->next) {
        if (itr->val == val) {
            previous->next = itr->next;
            continue;
        }

        previous = itr;
    }

    return head;
}

int main () {
    ListNode * solution1 = removeElements(new ListNode(7, new ListNode(7, new ListNode(7, new ListNode(7)))), 7);

    while (solution1 != NULL) {
        cout << solution1->val << ", ";
        solution1 = solution1->next;
    } cout << endl;

    ListNode * solution2 = removeElements(new ListNode(1, new ListNode(2, new ListNode(3))), 2);

    while (solution2 != NULL) {
        cout << solution2->val << ", ";
        solution2 = solution2->next;
    } cout << endl;

    return 0;
}