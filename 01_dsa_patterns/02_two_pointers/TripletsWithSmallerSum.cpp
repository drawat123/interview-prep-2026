#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
public:
  int searchTriplets(std::vector<int> &arr, int target) {
    if (arr.size() < 3) {
      return 0;
    }

    int count = 0;

    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < arr.size() - 2; i++) {
      size_t left = i + 1, right = arr.size() - 1;
      while (left < right) {
        int s = arr[i] + arr[left] + arr[right];
        if (s < target) {
          count += right - left;
          left++;
        } else {
          right--;
        }
      }
    }

    return count;
  }
};