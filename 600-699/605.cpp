#include <./stdc++11.h>

using namespace std;

bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if (n == 0)
        return true;

    for (int i = 0; i < flowerbed.size(); ++i) {
        if (flowerbed[i] == 0) {
            if(i - 1 >= 0 && flowerbed[i - 1] == 1)
                continue;
            if (i + 1 < flowerbed.size() && flowerbed[i + 1] == 1)
                continue;

            flowerbed[i] = 1;
            --n;
            ++i;
        } else if (flowerbed[i] == 1) {
            ++i;
        }
    }

    return n <= 0;
}

int main() {
    vector<int> test1{1,0,0,0,1};
    vector<int> test2{1,0,0,0,0,1};
    cout << canPlaceFlowers(test1, 1) << endl;
    cout << canPlaceFlowers(test2, 2) << endl;

    return 0;
}