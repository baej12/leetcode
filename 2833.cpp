#include <iostream>

using namespace std;

int furthestDistanceFromOrigin(string moves) {
    int leftDist = 0, rightDist = 0, freeDist = 0;

    for (int i = 0; i < moves.length(); ++i) {
        char c = moves[i];
        if (c == 'L') {
            ++leftDist;
        } else if (c == 'R') {
            ++rightDist;
        } else {
            ++freeDist;
        }
    }   

    return max(leftDist, rightDist) - min(leftDist, rightDist) + freeDist;
}

int main () {
    string moves = "L_RL__R";

    cout << furthestDistanceFromOrigin(moves) << endl;

    return 0;
}