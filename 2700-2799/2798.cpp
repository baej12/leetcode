#include <./stdc++11.h>

using namespace std;

int numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {
    int solution = 0;

    for (auto i : hours)
        if (i >= target)
            ++solution;

    return solution;
}

int main() {
    return 0;
}