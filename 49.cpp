#include <./stdc++11.h>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    if (strs.size() == 0) {
        return vector<vector<string>>{};
    } else if (strs.size() == 1) {
        return vector<vector<string>>{strs};
    }

    map<string, vector<string>> solMap;
    vector<vector<string>> solution;

    for (size_t i = 0; i < strs.size(); ++i) {
        string currStr = strs[i];
        sort(currStr.begin(), currStr.end());
        vector<string> vec = solMap[currStr];

        vec.push_back(strs[i]);
        solMap[currStr] = vec;
    }

    for (map<string, vector<string>>::iterator itr = solMap.begin(); itr != solMap.end(); ++itr) {
        solution.push_back(itr->second);
    }

    return solution;
}

int main() {
    vector<string> test1 = {"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> solution = groupAnagrams(test1);

    for (auto i : solution) {
        for (auto n : i) {
            cout << n << ", ";
        } cout << endl;
    }

    return 0;
}