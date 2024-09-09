#include <./stdc++11.h>

using namespace std;

int sumOfMultiples(int n) {
    int solution = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
            solution += i;
        }
    }
    return solution;
}

int main() {

    return 0;
}