#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& nums, int val) {
    int sol = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) {
            ++sol;
        } else {
            nums[i] = 101;
            for (int n = nums.size() - 1; n > i; --n) {
                if (nums[n] != 101) {
                    nums[i] = nums[n];
                    nums[n] = 101;
                    --i;
                    --sol;
                    break;
                }
            }
        }
    }

    return sol;
}

int main() {
    vector<int> test{0, 9, 2, 3, 5, 5, 5, 6};

    int solution = removeElement(test, 5);

    sort(test.begin(), test.begin() + solution - 1);

    for (int i = 0; i < solution; ++i) {
        cout << test[i] << ", ";
    } cout << endl;

    return 0;
}