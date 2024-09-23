#include <./stdc++11.h>

using namespace std;

int sumIndicesWithKSetBits(vector<int>& nums, int k) {
    int solution = 0;

    for (size_t i = 0; i < nums.size(); ++i) {
        string bits = bitset<17>(i).to_string();
        if (count_if(bits.begin(), bits.end(), [](char c){return c == '1';}) == k) {
            solution += nums[i];
        }
    }

    return solution;
}

int main() {
    return 0;
}