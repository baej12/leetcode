#include <./stdc++11.h>

using namespace std;

struct Person {
    string name;
    int height;
    Person(string n, int h) {
        name = n;
        height = h;
    }
};

static bool compareByHeight(const Person p1, const Person p2) {
    return p1.height > p2.height;
}

vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
    if (heights.size() == 1) {
        return names;
    }

    vector<Person> list;

    for (int i = 0; i < names.size(); ++i) {
        list.push_back(Person(names[i], heights[i]));
    }

    sort(list.begin(), list.end(), compareByHeight);

    for (int i = 0; i < list.size(); ++i) {
        names[i] = list[i].name;
    }

    return names;
}

int main() {


    return 0;
}