#include <./stdc++11.h>

using namespace std;

int singleNumber(vector<int>& nums) {
    if (nums.size() == 1) {
        return nums[0];
    }
    int result = 0;

    for (int i = 0; i < nums.size(); ++i) {
        result ^= nums[i];
    }
    return result;
}

int main() {
    return 0;
}