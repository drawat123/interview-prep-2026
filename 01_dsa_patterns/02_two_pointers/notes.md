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
