#include <./stdc++11.h>

using namespace std;

vector<int> shuffle(vector<int>& nums, int n) {
    vector<int> solution(n + n, 0);

    for (int i = 0; i < n; ++i) {
        solution[i * 2] = nums[i];
        solution[(i * 2) + 1] = nums[n + i];
    }

    return solution;   
}

int main() {
    vector<int> test1{2,5,1,3,4,7};
    vector<int> solution = shuffle(test1, 3);

    for (auto i : solution)
        cout << i << ", ";
    cout <<endl;

    return 0;
}