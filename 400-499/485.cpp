#include <./stdc++11.h>

using namespace std;

int findMaxConsecutiveOnes(vector<int>& nums) {
    int solution = 0, currMax = 0; 

    for (auto i : nums) {
        if (i == 0) {
            solution = max(currMax, solution);
            currMax = 0;
        } else {
            ++currMax;
        }
    }

    return max(solution, currMax);
}

int main () {


    return 0;
}