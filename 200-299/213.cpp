#include <./stdc++11.h>

using namespace std;

int rob(vector<int>& nums) {
    vector<int> firstChoice(nums.begin(), nums.end() - 1);
    vector<int> secondChoice(nums.begin() + 1, nums.end());

    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    if (nums.size() == 2) return max(nums[0], nums[1]);

    vector<int> dpOne(firstChoice.size(), 0);
    vector<int> dpTwo(secondChoice.size(), 0);


    dpOne[0] = firstChoice[0];
    dpOne[1] = max(firstChoice[0], firstChoice[1]);

    dpTwo[0] = secondChoice[0];
    dpTwo[1] = max(secondChoice[0], secondChoice[1]);

    for (int i = 2; i < firstChoice.size(); ++i) {
        dpOne[i] = max(dpOne[i - 1], dpOne[i - 2] + firstChoice[i]);
    }

    for (int i = 2; i < secondChoice.size(); ++i) {
        dpTwo[i] = max(dpTwo[i - 1], dpTwo[i - 2] + secondChoice[i]);
    }

    return max(dpOne[firstChoice.size() - 1], dpTwo[secondChoice.size() - 1]);
}

int main() {

    return 0;
}