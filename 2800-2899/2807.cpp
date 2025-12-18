#include <./stdc++11.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* insertGreatestCommonDivisors(ListNode* head) {
    for (ListNode * itr = head; itr != nullptr; itr = itr->next) {
        if (itr->next != nullptr) {
            ListNode * tempNext = itr->next;
            int gcd = 1;

            for (int n = 1; n <= min(itr->val, itr->next->val); ++n) {
                gcd = itr->val % n == 0 && itr->next->val % n == 0 ? n : gcd;
            }

            itr->next = new ListNode(gcd, tempNext);
            itr = itr->next;
        }
    }

    return head;
}

int main() {
    return 0;
}