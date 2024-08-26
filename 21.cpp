#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode * min (ListNode * val1, ListNode * val2) {
    ListNode * minNum;

    if (val1 == NULL) {
        return val2;
    } else if (val2 == NULL) {
        return val1;
    }

    if (val1->val < val2->val) {
        return val1;
    } else {
        return val2;
    }

    return val1;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode * sol = new ListNode();
    ListNode * baseSol = sol;

    if (list1 == NULL && list2 == NULL) {
        return NULL;
    } else if (list1 == NULL && list2 != NULL) {
        return list2;
    } else if (list1 != NULL && list2 == NULL) {
        return list1;
    }

    while (list1 != NULL || list2 != NULL) {
        sol->val = min(list1, list2)->val;

        if (list1 != NULL && sol->val == list1->val) {
            list1 = list1->next;
        } else {
            list2 = list2->next;
        }

        if (list1 != NULL || list2 != NULL) {
            sol->next = new ListNode();
            sol = sol->next;
        } else {break;}
    }

    return baseSol;       
}

int main () {
    ListNode * list1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode * list2 = new ListNode(3, new ListNode(4, new ListNode(5)));

    ListNode * solution = mergeTwoLists(list1, list2);

    while (solution != NULL) {
        cout << solution->val << " -> ";
        solution = solution->next;
    }

    cout << endl;

    return 0;
}