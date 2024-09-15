#include <./stdc++11.h>

using namespace std;

string convertDateToBinary(string date) {
    string year = bitset<12>{(unsigned long long)stoi(date.substr(0, 4))}.to_string();
    string month = bitset<4>{(unsigned long long)stoi(date.substr(5, 7))}.to_string();
    string day = bitset<5>{(unsigned long long)stoi(date.substr(8, 10))}.to_string();

    year.erase(0, year.find_first_not_of('0'));
    month.erase(0, month.find_first_not_of('0'));
    day.erase(0, day.find_first_not_of('0'));

    return year + "-" + month + "-" + day;
}

int main() {
    cout << convertDateToBinary("2080-02-29") << endl;

    return 0;
}