#include <iostream>

using namespace std;

bool judgeCircle(string moves) {
    int y = 0, x = 0;

    for (char c : moves) {
        if (c == 'U') {
            ++y;
        } else if (c == 'D') {
            --y;
        } else if (c == 'L') {
            --x;
        } else {
            ++x;
        }
    }

    return y == 0 && x == 0;
}

int main () {
    return 0;
}