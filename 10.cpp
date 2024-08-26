#include <iostream>
#include <assert.h>
#include <vector>
#include <stack>

using namespace std;

bool isMatch(string s, string p) {
    int si = s.length() - 1;

    for (int i = p.length() - 1; i >= 0; --i) {
      char reg = p[i];
      char str = s[i];

      if (si <= 0)
        return true;

      if (reg == '*') {
        char pre = p[i-1];
        for (; si >= 0; --si)
          if (s[si] != pre && pre != '.')
            break;
        --i;
      } else if (reg == '.') {
        --si;
      } else {
        if (s[si] != p[i])
          return false;
      }
    }
    
    return si <= 0;
}

int main () {
  cout << isMatch("aa", "a") << endl;
  cout << isMatch("aa", "a*") << endl;
  cout << isMatch("ab", ".*") << endl;
  cout << isMatch("aab", "c*a*b") << endl;

  return 0; 
}