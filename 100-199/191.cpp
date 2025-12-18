#include <./stdc++11.h>

using namespace std;

int hammingWeight(int n) {
    string solution = bitset<64>(n).to_string();
    solution.erase(remove(solution.begin(), solution.end(), '0'), solution.end());
    return solution.size();
}

int main() {
    cout << hammingWeight(2147483645) << endl;
    cout << hammingWeight(128) << endl;

    return 0;
}