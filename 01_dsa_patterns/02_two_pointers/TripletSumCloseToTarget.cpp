#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
public:
  int searchTriplet(std::vector<int> arr, int targetSum) {
    // 1. Guard clause: prevents unsigned underflow of arr.size() - 2
    if (arr.size() < 3) {
      return 0;
    }

    // 2. Passed by value (std::vector<int> arr) instead of reference
    // so sorting it doesn't mutate the caller's array.
    std::sort(arr.begin(), arr.end());

    long long smallestDifference = std::numeric_limits<long long>::max();

    for (size_t i = 0; i < arr.size() - 2; i++) {
      size_t left = i + 1, right = arr.size() - 1;
      while (left < right) {
        // 3. Cast to long long to prevent any possible integer overflow
        long long targetDiff =
            static_cast<long long>(targetSum) - arr[i] - arr[left] - arr[right];

        if (targetDiff == 0) {
          return targetSum;
        }

        if (std::abs(targetDiff) < std::abs(smallestDifference) ||
            (std::abs(targetDiff) == std::abs(smallestDifference) &&
             targetDiff > smallestDifference)) {
          smallestDifference = targetDiff;
        }

        if (targetDiff > 0) {
          left++;
        } else {
          right--;
        }
      }
    }
    return static_cast<int>(targetSum - smallestDifference);
  }
};

int main(int argc, char *argv[]) {
  Solution sol;
  std::vector<int> vec = {-1, 0, 2, 3};
  std::cout << sol.searchTriplet(vec, 3) << std::endl;
}