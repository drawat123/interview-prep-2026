# Pattern: Two Pointers

## Problem: Pair with Target Sum
**Optimal Solution:**
* **Time:** O(N)
* **Space:** O(1)

**The Code Skeleton (Java)**
```java
int l = 0, r = arr.length - 1;
while (l < r) {
    int currentSum = arr[l] + arr[r];
    if (currentSum == targetSum) {
        return new int[] { l, r }; // Or return the values
    }
    if (targetSum > currentSum) {
        l++;
    } else {
        r--;
    }
}
return new int[] { -1, -1 };
```

## Problem: Remove Duplicates (In-Place)
**Optimal Solution:**
* **Time:** O(N)
* **Space:** O(1)

**Why it works:**
Using a two-pointer approach where one pointer (`i`) scans the array, and the other (`nextNonDuplicate`) tracks the write index. A critical Senior-level practice is to include the guard clause for empty arrays to prevent `ArrayIndexOutOfBoundsException`.

**The Code Skeleton (Java)**
```java
if (arr == null || arr.length == 0) return 0;

int nextNonDuplicate = 1;
for (int i = 1; i < arr.length; i++) {
    if (arr[nextNonDuplicate - 1] != arr[i]) {
        arr[nextNonDuplicate] = arr[i];
        nextNonDuplicate++;
    }
}
return nextNonDuplicate;
```

## Problem: Squaring a Sorted Array
**Optimal Solution (MTS Level):**
* **Time:** O(N)
* **Space:** O(N) for output array

**Why it works:**
Over-engineering trap: Avoid binary searching for the zero-crossing. Because the array is sorted, the squares of the numbers at both extreme ends will always be the largest. Use two pointers starting at the outermost edges and write the larger square to the end of the new array, moving inward.

**The Code Skeleton (Java)**
```java
int n = arr.length;
int[] squares = new int[n];
int l = 0, r = n - 1;
int writeIdx = n - 1;

while (l <= r) {
    int leftSquare = arr[l] * arr[l];
    int rightSquare = arr[r] * arr[r];
    
    if (leftSquare > rightSquare) {
        squares[writeIdx--] = leftSquare;
        l++;
    } else {
        squares[writeIdx--] = rightSquare;
        r--;
    }
}
return squares;
```

## Problem: Triplet Sum to Zero
**Optimal Solution (MTS Level):**
* **Time:** O(N^2)
* **Space:** O(N) for sorting

**Why it works:**
Fix one number (`arr[i]`), then use standard Two Pointers to find if the remaining two numbers sum to `-arr[i]`. Crucially, when a triplet is found, both the left and right pointers must be moved, and duplicates must be aggressively skipped to save CPU cycles and prevent duplicate triplets.

**The Code Skeleton (Java)**
```java
Arrays.sort(arr);
List<List<Integer>> triplets = new ArrayList<>();

for (int i = 0; i < arr.length - 2; i++) {
    // Skip duplicate for the fixed number
    if (i > 0 && arr[i] == arr[i - 1]) continue;

    int j = i + 1, k = arr.length - 1;
    while (j < k) {
        int currSum = arr[i] + arr[j] + arr[k];
        if (currSum == 0) {
            triplets.add(List.of(arr[i], arr[j], arr[k]));
            j++;
            k--;
            // Skip duplicates for both pointers
            while (j < k && arr[j] == arr[j - 1]) j++;
            while (j < k && arr[k] == arr[k + 1]) k--;
        } else if (currSum < 0) {
            j++;
        } else {
            k--;
        }
    }
}
return triplets;
```

## Problem: Dutch National Flag
**The Core Concept**
* **The Trick:** Use 3 pointers (`low`, `high`, and an iterator `i`). `low` tracks where the next `0` should go, `high` tracks where the next `2` should go. `switch` on `arr[i]` to swap and advance.
* **Data Structure Used:** In-place Array/Vector manipulation.

**Complexity**
* **Time:** `O(N)` — Single pass through the array.
* **Space:** `O(1)` — No extra structures used.

**Memory / Perf note**
* Pass the container as `std::vector<int>&` to mutate in-place without triggering a deep copy. Using `std::swap` is highly optimized in C++.

**The Code Skeleton (C++)**
```cpp
void sortColors(std::vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    for (int i = 0; i <= high;) {
        switch (arr[i]) {
            case 0:
                std::swap(arr[i++], arr[low++]);
                break;
            case 1:
                i++;
                break;
            case 2:
                std::swap(arr[i], arr[high--]);
                // Don't increment i here, the swapped element needs evaluation
                break;
        }
    }
}
```

## Problem: Quadruple Sum to Target
**The Core Concept**
* **The Trick:** Sort the array. Use two outer `for` loops (`i` and `j`) to lock in two numbers, then use standard Two Pointers (`l` and `r`) for the remaining two. Skip duplicates for all 4 pointers.
* **Data Structure Used:** Array/Vector.

**Complexity**
* **Time:** `O(N^3)` — Two nested loops + one `O(N)` two-pointer sweep.
* **Space:** `O(N)` — Required for `std::sort` under the hood.

**Memory / Perf note**
* **UB Risk:** Integer Promotion. Adding four 32-bit `int`s can cause signed integer overflow. You must cast to `long long` (e.g., `static_cast<long long>(arr[i])`) *before* the addition occurs.

**The Code Skeleton (C++)**
```cpp
// Skip boilerplate duplicates...
int l = j + 1, r = arr.size() - 1;
while (l < r) {
    // Systems nuance: cast to 64-bit to prevent overflow
    long long sum = static_cast<long long>(arr[i]) + arr[j] + arr[l] + arr[r];
    if (sum == target) {
        quadruplets.push_back({arr[i], arr[j], arr[l], arr[r]});
        l++; r--;
        while(l < r && arr[l] == arr[l-1]) l++;
        while(l < r && arr[r] == arr[r+1]) r--;
    } else if (sum < target) {
        l++;
    } else {
        r--;
    }
}
```

## Problem: Comparing Strings containing Backspaces
**The Core Concept**
* **The Trick:** Traverse both strings *backwards* (right to left). Extract the backspace logic into a dedicated helper function `getNextValidCharIndex` to cleanly handle cascading `#` characters.
* **Data Structure Used:** Strings / Pointers.

**Complexity**
* **Time:** `O(N)` — Single pass backwards.
* **Space:** `O(1)` — Evaluated in place.

**Memory / Perf note**
* By traversing backwards, you avoid allocating a brand new `std::string` on the heap (which would take `O(N)` space and cause massive allocator overhead). Always pass the input strings as `const std::string&` to guarantee no copies are made.

**The Code Skeleton (C++)**
```cpp
int getNextValidCharIndex(const std::string& str, int index) {
    int backspaceCount = 0;
    while (index >= 0) {
        if (str[index] == '#') {
            backspaceCount++;
        } else if (backspaceCount > 0) {
            backspaceCount--;
        } else {
            break;
        }
        index--;
    }
    return index;
}
```

## Problem: Triplet Sum Close to Target
**The Core Concept**
* **The Trick:** Sort the array. Use an outer loop `i` and standard Two Pointers (`left`, `right`). Maintain a `smallestDifference` variable. If absolute differences are equal, prioritize the one that results in the smaller sum.
* **Data Structure Used:** Array/Vector.

**Complexity**
* **Time:** `O(N^2)` — Sorting `O(N log N)` + nested loop sweep `O(N^2)`.
* **Space:** `O(N)` — Required for `std::sort`.

**Memory / Perf note**
* **Pass by Value vs Reference:** The function signature accepts `std::vector<int> arr` (pass-by-value) instead of a reference. This is a deliberate systems choice because the array must be sorted. If you passed by reference, you would mutate and corrupt the caller's underlying data!

**The Code Skeleton**
```cpp
long long smallestDifference = std::numeric_limits<long long>::max();
// ... inside the two-pointer while loop:
long long targetDiff = static_cast<long long>(targetSum) - arr[i] - arr[left] - arr[right];

if (targetDiff == 0) return targetSum;

if (std::abs(targetDiff) < std::abs(smallestDifference) ||
    (std::abs(targetDiff) == std::abs(smallestDifference) && targetDiff > smallestDifference)) {
    smallestDifference = targetDiff;
}
```

## Problem: Triplets with Smaller Sum
**The Core Concept**
* **The Trick:** Sort the array. Lock in `i`, then use `left` and `right`. If the sum is strictly less than the target, it means the current `left` pointer can be paired with *every single element* between `left` and `right` and still be under the target. Instead of iterating, just do math: `count += right - left`.
* **Data Structure Used:** Array/Vector.

**Complexity**
* **Time:** `O(N^2)` — Despite the math shortcut, the nested loop `O(N^2)` dominates sorting.
* **Space:** `O(N)` — Required for `std::sort`.

**Memory / Perf note**
* **The `size_t` Underflow Trap:** Before writing a `for` loop that goes to `arr.size() - 2`, you *must* have a guard clause checking `if (arr.size() < 3) return 0;`. Because `size()` returns an unsigned `size_t`, if the array length is 0, `0 - 2` will underflow into `SIZE_MAX` (a massive positive integer), causing an immediate segfault when looping.

**The Code Skeleton**
```cpp
if (arr.size() < 3) return 0; // Guard clause prevents size_t underflow!

// ... inside the two-pointer while loop:
int s = arr[i] + arr[left] + arr[right];
if (s < target) {
    count += right - left; // Math shortcut!
    left++;
} else {
    right--;
}
```
