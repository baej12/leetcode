#include <iostream>
#include <bitset>
#include <string>
#include <stack>

using namespace std;

#define ullong unsigned long long

void addBits(char * bit1, char * bit2, char & sumChar, int & sumInt, bool & carryOver) {
    if (bit1 != NULL && bit2 != NULL) {
        if (*bit1 == *bit2) {
            sumChar = carryOver ? '1' : '0';
            sumInt = carryOver ? 1 : 0;
            carryOver = *bit1 == '1';   //Look at how I calculate whether carryOver is correct
        } else {
            sumChar = carryOver ? '0' : '1';
            sumInt = carryOver ? 0 : 1;
            carryOver = sumChar == '0' && carryOver;
        }
    } else if (bit1 != NULL) {
        if (carryOver) {
            sumChar = *bit1 == '1' ? '0' : '1';
            sumInt = *bit1 == '1' ? 0 : 1;
            carryOver = *bit1 == '1';
        } else {
            sumChar = *bit1;
            sumInt = *bit1 == 0 ? 0 : 1;
            carryOver = false;
        }
    } else if (bit2 != NULL) {
        if (carryOver) {
            sumChar = *bit2 == '1' ? '0' : '1';
            sumInt = *bit2 == '1' ? 0 : 1;
            carryOver = *bit2 == '1';
        } else {
            sumChar = *bit2;
            sumInt = *bit2 == 0 ? 0 : 1;
            carryOver = false;
        }
    }
}

string addBinary(string a, string b) {
    string solution = "";
    stack<char> buildStr;
    char * ac = &a[a.size() - 1];
    char * bc = &b[b.size() - 1];
    bool carryOver = false;

    for (int i = max(a.size(), b.size()) - 1; i >= 0 ; --i) {
        char sumChar = '0';
        int sumInt = 0;
        addBits(ac, bc, sumChar, sumInt, carryOver);
        
        if (ac == &a[0]) {
            ac = NULL;
        } else {
            if (ac != NULL) {
                ac--;
            }
        }

        if (bc == &b[0]) {
            bc = NULL;
        } else {
            if (bc != NULL) {
                bc--;
            }
        }

        buildStr.push(sumChar);
    }

    if (carryOver) {
        buildStr.push('1');   
    }

    while (!buildStr.empty()) {
        solution += buildStr.top();
        buildStr.pop();
    }
    
    return solution;
}

int main() {
    cout << addBinary("1010", "1011") << endl;
    cout << addBinary("1110001", "110100100") << endl;
    cout << (addBinary(
        "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101", 
        "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011"
    ) == "110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000") << endl;

    return 0;
}