#include <./stdc++11.h>

int smallestEvenMultiple(int n) {
    if (n % 2 == 0) {
        return n;
    } else {
        return n * 2;
    }
}

int main () {
    std::cout << smallestEvenMultiple(5) << std::endl;

    return 0;
}