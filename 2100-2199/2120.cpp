#include <iostream>
#include <vector>

using namespace std;

vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
    vector<int> solution;

    while (s != "") {
        int botY = startPos[0], botX = startPos[1];
        bool validInstructions = true;
        int numOfValidInstructions = 0;

        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];
            
            if (c == 'U') {
                --botY;
            } else if (c == 'D') {
                ++botY;
            } else if (c == 'R') {
                ++botX;
            } else if (c == 'L') {
                --botX;
            }

            if (botY >= n || botY < 0 || botX >= n || botX < 0) {
                break;
            }

            ++numOfValidInstructions;
        }

        solution.push_back(numOfValidInstructions);

        s = s.substr(1, s.length());
    }

    return solution;
}

int main() {
    vector<int> startPos{0,1};
    int n = 3;
    string s = "RRDDLU";

    vector<int> solution = executeInstructions(n, startPos, s);

    for (auto i : solution) {
        cout << i << " ";
    } cout << endl;

    return 0;
}