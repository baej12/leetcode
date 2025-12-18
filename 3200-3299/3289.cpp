#include <./stdc++11.h>

using namespace std;

vector<int> getSneakyNumbers(vector<int>& nums) {
    map<int, bool> dupCheck;
    vector<int> sol;

    for (size_t i = 0; i < nums.size(); ++i) {
        if (dupCheck[nums[i]])
            sol.push_back(nums[i]);
        dupCheck[nums[i]] = true;
    }   

    return sol;
}

int main() {

    return 0;
}