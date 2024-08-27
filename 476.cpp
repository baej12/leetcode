#include <./stdc++11.h>

using namespace std;

map<char, char> flip{{'0', '1'}, {'1', '0'}};

int findComplement(int num) {
    string binaryNum = bitset<32>(num).to_string();
    binaryNum.erase(0, binaryNum.find_first_not_of('0'));
    for (size_t i = 0; i < binaryNum.length(); ++i) {
        binaryNum[i] = flip[binaryNum[i]];
    }
    return bitset<32>("0" + binaryNum).to_ulong();
}

int main() {
    cout << findComplement(5) << endl;
    cout << findComplement(1) << endl;

    return 0;
}