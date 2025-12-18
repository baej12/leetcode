#include <./stdc++11.h>

using namespace std;

string decodeMessage(string key, string message) {
    map<char, char> decoder;
    string sol = "";
    char alpha = 'a';

    for (auto c : key) {
        if (c != ' ' && decoder.find(c) == decoder.end()) {
            decoder[c] = alpha++;
        }
    }

    for (auto c : message) {
        sol += c == ' ' ? ' ' : decoder[c];
    }

    return sol;
}

int main() {
    string key1 = "the quick brown fox jumps over the lazy dog";
    string msg1 = "vkbs bs t suepuv";

    cout << decodeMessage(key1, msg1) << endl;

    return 0;
}