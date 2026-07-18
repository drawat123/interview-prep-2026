#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  static std::vector<std::vector<int>> searchQuadruplets(std::vector<int> arr,
                                                         int target) {
    size_t n = arr.size();
    if (n < 4) {
      return {};
    }

    std::vector<std::vector<int>> quadruplets;

    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < n - 3; i++) {
      if (i != 0 && arr[i] == arr[i - 1]) {
        continue;
      }
      for (size_t j = i + 1; j < n - 2; j++) {
        if (j != i + 1 && arr[j] == arr[j - 1]) {
          continue;
        }

        size_t k = j + 1, l = n - 1;
        while (k < l) {
          long long sum =
              static_cast<long long>(arr[i]) + arr[j] + arr[k] + arr[l];
          if (sum == target) {
            quadruplets.push_back({arr[i], arr[j], arr[k], arr[l]});

            k++;
            l--;
            while (k < l && arr[k] == arr[k - 1]) {
              k++;
            }
            while (k < l && arr[l] == arr[l + 1]) {
              l--;
            }
          } else if (sum < target) {
            k++;
          } else {
            l--;
          }
        }
      }
    }

    return quadruplets;
  }
};

int main() {
  std::vector<int> arr{-2, -2, -1, -1, 0, 1, 2, 2};
  int target = -1;

  auto quadruplets = Solution::searchQuadruplets(arr, target);

  for (const auto &vec : quadruplets) {
    for (const auto &ele : vec) {
      std::cout << ele << ", ";
    }
    std::cout << std::endl;
  }

  return 0;
}
