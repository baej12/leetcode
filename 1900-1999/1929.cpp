#include <./stdc++11.h>

using namespace std;

vector<int> getConcatenation(vector<int>& nums) {
    vector<int> solution(nums.size() * 2, 0);

    for (int i = 0; i < nums.size(); ++i) {
        solution[i] = nums[i];
        solution[nums.size() + i] = nums[i];
    }

    return solution;
}

int main() {
    return 0;
}