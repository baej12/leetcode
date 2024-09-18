#include <./stdc++11.h>

using namespace std;

double minimumAverage(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    double smallestDouble = nums[nums.size() - 1];

    while (nums.size() > 0) {
        smallestDouble = min(smallestDouble, (double)(nums[0] + nums[nums.size() - 1]) / 2);
        nums.erase(nums.end());
        nums.erase(nums.begin());
    }

    return smallestDouble;
}

int main() {
    return 0;
}