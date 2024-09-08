#include <./stdc++11.h>

using namespace std;

int finalValueAfterOperations(vector<string>& operations) {
    int solution = 0;

    for (int i = 0; i < operations.size(); ++i) {
        if (operations[i] == "--X" || operations[i] == "X--") {
            --solution;
        } else {
            ++solution;
        }
    }

    return solution;
}

int main() {

    return 0;
}