#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (n == 0) {
        return;
    } 
    
    if  (m == 0) {
        nums1[n - 1] = nums2[n - 1];
        merge(nums1, m, nums2, n - 1);
        return;
    }

    if (nums1[m - 1] < nums2[n - 1]) {
        nums1[m + n - 1] = nums2[n-1];
        merge(nums1, m, nums2, n-1);
    } else {
        nums1[m + n - 1] = nums1[m - 1];
        nums1[m - 1] = nums2[n - 1];
        merge(nums1, m - 1, nums2, n);
    }
}

int main () {
    vector<int> testA1{1,2,3,0,0,0};
    vector<int> testB1{2,5,6};
    vector<int> testA2{1,3,4,0,0,0};
    vector<int> testB2{2,5,6};

    merge(testA1, 3, testB1, 3);

    for (int i = 0; i < testA1.size(); ++i) {
        cout << testA1[i] << ", ";
    } cout << endl;

    merge(testA2, 3, testB2, 3);
    
    for (int i = 0; i < testA2.size(); ++i) {
        cout << testA2[i] << ", ";
    } cout << endl;

    return 0;
}