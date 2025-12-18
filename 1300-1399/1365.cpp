#include <./stdc++11.h>

using namespace std;

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> solution(nums.size(), 0);

    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t n = 0; n < nums.size(); ++n) {
            if (i == n)
                continue;

            if (nums[i] > nums[n])
                ++solution[i];
        }
    }

    return solution;
}

int main() {
    return 0;
}