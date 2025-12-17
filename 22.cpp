#include <iostream>
#include <vector>

using namespace std;

vector<string> generateParenthesis(int n) {
    vector<string> result;
    string current;
    
    function<void(int, int)> backtrack = [&](int open, int close) {
        if (open == n && close == n) {
            result.push_back(current);
            return;
        }
        if (open < n) {
            current.push_back('(');
            backtrack(open + 1, close);
            current.pop_back();
        }
        if (close < open) {
            current.push_back(')');
            backtrack(open, close + 1);
            current.pop_back();
        }
    };
    
    backtrack(0, 0);
    return result;
}

int main() {
    vector<string> result = generateParenthesis(3);
    for (const string& s : result) {
        cout << s << endl;
    }
    return 0;
}