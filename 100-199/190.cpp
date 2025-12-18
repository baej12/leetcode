#include <iostream>

using namespace std;

uint32_t reverseBits(uint32_t n) {
    string converted = bitset<32>(n).to_string();
    reverse(converted.begin(), converted.end());
    return bitset<32>(converted).to_ulong();
}

int main () {
    cout << reverseBits(bitset<32>("00000010100101000001111010011100").to_ulong()) << endl;

    return 0;
}