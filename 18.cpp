#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> solution;
    map<vector<int>, bool> dupCheck;
    map<int, bool> firstFor;

    if (nums.size() < 4) {
        return solution;   
    }

    for (int i = 0; i < nums.size() - 3; ++i) {
        if (firstFor[nums[i]] == true) {
            continue;
        }

        firstFor[nums[i]] = true;

        for (int n = i + 1; n < nums.size() - 2; ++n) { 
            for (int y = n + 1; y < nums.size() - 1; ++y) {
                for (int x = y + 1; x < nums.size(); ++x) {
                    if ((double)nums[i] + (double)nums[n] + (double)nums[y] + (double)nums[x] == (double)target) {
                        vector<int> potSol{nums[i], nums[n], nums[y], nums[x]};
                        sort(potSol.begin(), potSol.end());

                        if (dupCheck[potSol] == false) {
                            dupCheck[potSol] = true;
                            solution.push_back(potSol);
                        }
                    }
                }
            }
        }
    }

    return solution;
}

int main() {
    vector<int> test{1,0,-1,0,-2,2};

    auto solution = fourSum(test, 0);

    for (auto i : solution) {
        for (auto n : i) {
            cout << n << " ";
        }
        cout << endl;
    }

    return 0;
}