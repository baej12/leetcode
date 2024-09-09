#include <./stdc++11.h>

using namespace std;

int minimumOperations(vector<int>& nums) {
    int solution = 0;
    for (int i = 0; i < nums.size(); ++i) 
        if (nums[i] % 3 != 0)
            ++solution;
    return solution;
}

int main () {
    return 0;
}