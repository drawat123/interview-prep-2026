#include <cstddef>
#include <string>

class Solution {
public:
  static bool compare(const std::string &str1, const std::string &str2) {
    int r1 = str1.length() - 1, r2 = str2.length() - 1;
    while (r1 >= 0 || r2 >= 0) {
      int i1 = getNextValidCharIndex(str1, r1);
      int i2 = getNextValidCharIndex(str2, r2);

      if (i1 < 0 && i2 < 0) { // reached the end of both the strings
        return true;
      }

      if (i1 < 0 || i2 < 0) { // reached the end of one of the strings
        return false;
      }

      if (str1[i1] != str2[i2]) { // check if the characters are equal
        return false;
      }

      r1 = i1 - 1;
      r2 = i2 - 1;
    }

    return true;
  }

private:
  static int getNextValidCharIndex(const std::string &str, int index) {
    int backspaceCount = 0;
    while (index >= 0) {
      if (str[index] == '#') { // found a backspace character
        backspaceCount++;
      } else if (backspaceCount > 0) { // a non-backspace character
        backspaceCount--;
      } else {
        break;
      }

      index--; // skip a backspace or a valid character
    }
    return index;
  }
};

/*
Input: str1="xy#z", str2="xzz#"
Output: true
Explanation: After applying backspaces the strings become "xz" and "xz"
respectively.

Input: str1="xy#z", str2="xyz#"
Output: false
Explanation: After applying backspaces the strings become "xz" and "xy"
respectively.

Input: str1="xp#", str2="xyz##"
Output: true
Explanation: After applying backspaces the strings become "x" and "x"
respectively. In "xyz##", the first '#' removes the character 'z' and the second
'#' removes the character 'y'.
*/