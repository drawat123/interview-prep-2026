#include <utility>
#include <vector>

class Solution {
public:
  std::vector<int> sort(const std::vector<int> &arr) {
    if (arr.empty()) {
      return {};
    }

    std::vector<int> res = arr;
    int low = 0, high = arr.size() - 1, i = 0;

    while (i <= high) {
      switch (res[i]) {
      case 0:
        std::swap(res[i], res[low]);
        low++;
        i++;
        break;
      case 1:
        i++;
        break;
      case 2:
        std::swap(res[i], res[high]);
        high--;
        break;
      }
    }

    return res;
  }
};