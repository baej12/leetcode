#include <./stdc++11.h>

using namespace std;

bool isStrictlyPalindromic(int n) {
    string binary = bitset<64>(n).to_string();
    binary.substr(binary.find_first_not_of('0'), 65);

    for (int i = 0, n = binary.size() - 1; i != n; ++i, --n) {
        if (binary[i] != binary[n])
            return false;
    }

    return true;
}

int main() {
    return 0;
}