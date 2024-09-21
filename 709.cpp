#include <./stdc++11.h>

using namespace std;

string toLowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return std::tolower(c); });
    return s;
}

int main() {
    return 0;
}