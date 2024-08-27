#include <./stdc++11.h>

using namespace std;

vector<int> sortedSquares(vector<int>& nums) {
    priority_queue<int> pq;

    for (size_t i = 0; i < nums.size(); ++i) {
        pq.push(pow(nums[i], 2));
    }

    for (size_t i = 0; i < nums.size(); ++i) {
        nums[nums.size() - i - 1] = pq.top();
        pq.pop();
    }

    return nums;
}

int main () {
    vector<int> nums{-4,-1,0,3,10};

    sortedSquares(nums);

    for (auto i : nums) {
        cout << i << ", ";
    }

    return 0;
}