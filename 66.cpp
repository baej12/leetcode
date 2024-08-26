#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> plusOne(vector<int>& digits) {
    vector<int> solution;
    stack<int> sum;
    int carryOver = 0;
    int digit = 0;

    for (int i = digits.size() - 1; i >= 0; --i) {
        if (i == digits.size() - 1) {
            digit = digits[i] + 1;
        } else {
            digit = digits[i] + carryOver;
        }
        carryOver = digit / 10;
        digit = digit % 10;

        sum.push(digit);
    }   

    if (carryOver != 0) {
        solution.push_back(carryOver);
    }

    while (!sum.empty()) {
        solution.push_back(sum.top());
        sum.pop();
    }

    return solution;
}

int main() {
    vector<int> test1{9};
    vector<int> test2{4, 3, 2, 1};
    vector<int> test3{9, 9};
    auto solution = plusOne(test1);
    auto solution2 = plusOne(test2);
    auto solution3 = plusOne(test3);

    for (auto i : solution) {
        cout << i << ", ";
    } cout << endl;

    for (auto i : solution2) {
        cout << i << ", ";
    } cout << endl;

    for (auto i : solution3) {
        cout << i << ", ";
    } cout << endl;

    return 0;
}