#include <./stdc++11.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* rotateRight(ListNode* head, int k) {
    queue<ListNode*> q;
    queue<ListNode*> firstHalf;
    queue<ListNode*> secondHalf;
    ListNode * retNode;
    ListNode * solution;

    //Base case
    if (k == 0 || head == NULL) {
        return head;
    }

    //Add the nodes into a queue
    for (ListNode * itr = head; itr != NULL; itr = itr->next) {
        q.push(itr);
    }

    //If k = 4 and the list size is 3, the resulting list is equivalent to if k = 1
    if (k > (int)q.size()) {
        k %= q.size();
    }

    //q.size() will keep changing as we pop
    size_t originalQ = q.size();

    //Split the first n - k into firstHalf. Put the remaining k into secondHalf
    for (size_t i = 0; i < originalQ; ++i) {
        if (i < originalQ - k) {
            secondHalf.push(q.front());
        } else {
            firstHalf.push(q.front());
        }

        q.pop();
    }

    //We should have at least something in firstHalf since we checked for empty list
    solution = new ListNode();
    //retNode points to the first node that will be in solution
    retNode = solution;

    //Keep creating nodes with values from the queue
    while (!firstHalf.empty()) {
        solution->val = firstHalf.front()->val;
        firstHalf.pop();

        //Keeps appending next nodes unless firstHalf is empty
        //Once we empty firstHalf, we append one more node is secondHalf is not empty
        if (!firstHalf.empty() || !secondHalf.empty()) {
            solution->next = new ListNode();
            solution = solution->next;
        }
    }

    //Do the same as above 
    while (!secondHalf.empty()) {
        solution->val = secondHalf.front()->val;
        secondHalf.pop();

        if (!secondHalf.empty()) {
            solution->next = new ListNode();
            solution = solution->next;
        }
    }

    return retNode;
}

int main() {
    ListNode * test1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    ListNode * solution = rotateRight(test1, 2);

    while (solution != NULL) {
        cout << solution->val << " -> ";
        solution = solution->next;
    } cout << endl;

    ListNode * test2 = new ListNode(2);
    ListNode * solution2 = rotateRight(test2, 1);

    while (solution2 != NULL) {
        cout << solution2->val << " -> ";
        solution2 = solution2->next;
    } cout << endl;

    ListNode * test3 = new ListNode(1, new ListNode(2, new ListNode(3)));
    ListNode * solution3 = rotateRight(test3, 2000000000);

    while (solution3 != NULL) {
        cout << solution3->val << " -> ";
        solution3 = solution3->next;
    } cout << endl;


    return 0;
}