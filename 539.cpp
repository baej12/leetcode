#include <./stdc++11.h>

using namespace std;

#define FULLDAY 1440

int add(int addend, int sum) {
    return (FULLDAY - addend) + sum;
}

int checkDiff(int a, int b) {
    return min(abs(a - b), add(max(a,b), min(a,b)));
}

int findMinDifference(vector<string>& timePoints) {
    vector<int> t;
    int sol = 25 * 60;

    for (auto i : timePoints) {
        t.push_back((stoi(i.substr(0, 2)) * 60) + stoi(i.substr(3, 5)));
    }

    sort(t.begin(), t.end());
    sol = min(checkDiff(t[0], t[1]), checkDiff(t[0], t[t.size() - 1]));

    for (size_t i = 1; i < t.size() - 1; ++i) {
        sol = min(sol, (abs(t[i] - t[i + 1])));
    }

    return sol;
}

int main () {
    vector<string> test{"23:59","00:00"};
    cout << findMinDifference(test) << endl;
    vector<string> test2{"00:00","23:59","00:00"};
    cout << findMinDifference(test2) << endl;
    vector<string> test3{"01:01","02:01","03:00"};
    cout << findMinDifference(test3) << endl;
    vector<string> test4{"05:31","22:08","00:35"};
    cout << findMinDifference(test4) << endl;

    return 0;
}