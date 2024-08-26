#include <iostream>
#include <vector>
#include <map>

using namespace std;

int solve(int a...) {
    vector<int> input;

    

    return 0;
}

//Has to be in place algo
int removeDuplicates(vector<int>& nums) 
{
    map<int, int> dup;
    int dupCount = 0;

    for (int i = 0; i < nums.size(); ++i) {
        dup[nums[i]]++;
        if (nums[i] != 101 && dup[nums[i]] > 1) {
            ++dupCount;
            for (int n = i + 1; n < nums.size(); ++n) {
                nums[n - 1] = nums[n];
            }
            nums[nums.size() - 1] = 101;
            --i;
        }
    }

    return nums.size() - dupCount;
}

int main () 
{
    // vector<int> input{0,0,1,1,1,2,2,3,3,4};
    vector<int> input;

    input.push_back(0);
    input.push_back(0);
    input.push_back(1);
    input.push_back(1);
    input.push_back(1);
    input.push_back(2);
    input.push_back(2);
    input.push_back(3);
    input.push_back(3);
    input.push_back(4);

    // input.push_back(1);
    // input.push_back(1);
    // input.push_back(2);

    cout << "k: " << removeDuplicates(input) << endl;

    for (int i = 0; i < input.size(); ++i) {
        cout << input[i] << " ";
    }

    cout << endl;

    return 0;
}