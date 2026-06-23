# Pattern: Warmup
## Problem: Contains Duplicate

**Optimal Solution (Implemented):** * **Time:** O(N) - Single pass through the array.
* **Space:** O(N) - HashSet scales linearly with input size.
* **Why it works:** `HashSet.add()` returns `false` if the element already exists. Wrapping it in `if (!hashSet.add(num))` is extremely clean.

**Alternative (Space-Optimized):**
* If the interviewer says "O(1) memory only", we must sort the array first `Arrays.sort(nums)`, then check adjacent elements `nums[i] == nums[i+1]`. 
* **Trade-off:** Time complexity degrades from O(N) to O(N log N) due to sorting. Space becomes O(1).

**The Code Skeleton (Java)**
```java
Set<Integer> seen = new HashSet<>();

for (int num : nums) {
    // CRITICAL: .add() returns false if the element is already in the set.
    // This saves us from doing a separate .contains() check first.
    if (!seen.add(num)) { 
        return true;
    }
}
return false;
```

## Problem: Check if Sentence Is Pangram

**Optimal Solution (MTS Level - Bitmasking):** 
* **Time:** O(N) - Single pass through the string.
* **Space:** O(1) - Single 32-bit integer used for tracking.

**Why it works:** 
Instead of an array allocation (`boolean[26]`), use an `int` to store bits. For each char, set the corresponding bit `seen |= (1 << val)`. A complete pangram means the first 26 bits are set to 1, which equals `(1 << 26) - 1`.

**The Code Skeleton (Java)**
```java
if (sentence == null || sentence.length() < 26) return false;

int seen = 0;
for (int i = 0; i < sentence.length(); i++) {
    int val = Character.toLowerCase(sentence.charAt(i)) - 'a';
    if (val >= 0 && val <= 25) {
        seen |= (1 << val);
    }
    // 67108863 == (1 << 26) - 1
    if (seen == (1 << 26) - 1) {
        return true;
    }
}
return false;
```

## Problem: Valid Palindrome (Two Pointers)

**Optimal Solution (MTS Level):**
* **Time:** O(N) - Single pass inwards.
* **Space:** O(1) - Two integer pointers.

**Why it works:**
Using tight, nested `while` loops to skip non-alphanumeric characters instantly prevents redundant checks and unnecessary bounds evaluations on the outer loop. Characters are only converted to lowercase exactly when they need to be compared.

**The Code Skeleton (Java)**
```java
int l = 0, r = s.length() - 1;

while (l < r) {
    while (l < r && !Character.isLetterOrDigit(s.charAt(l))) l++;
    while (l < r && !Character.isLetterOrDigit(s.charAt(r))) r--;
    
    if (Character.toLowerCase(s.charAt(l)) != Character.toLowerCase(s.charAt(r))) {
        return false;
    }
    l++;
    r--;
}
return true;
```

## Problem: Reverse Vowels of a String (Two Pointers)

**Optimal Solution (MTS Level):**
* **Time:** O(N)
* **Space:** O(N) - Array allocation is strictly required to mutate a string in Java.

**Why it works:**
Using a static helper with a `switch` expression compiles to an `O(1)` bytecode table lookup, completely bypassing the boxing/unboxing overhead and memory bloat of a `HashSet<Character>`. Directly manipulating a `char[]` exposes the true `O(N)` cost clearly, avoiding the `StringBuilder` synchronization and bounds-checking penalties.

**The Code Skeleton (Java)**
```java
private static boolean isVowel(char c) {
    return switch (c) {
        case 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' -> true;
        default -> false;
    };
}

public String reverseVowels(String s) {
    char[] arr = s.toCharArray();
    int l = 0, r = arr.length - 1;

    while (l < r) {
        while (l < r && !isVowel(arr[l])) l++;
        while (l < r && !isVowel(arr[r])) r--;

        if (l < r) {
            char temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    }
    return new String(arr);
}
```

## Problem: Number of Good Pairs (Hashing/Array Lookup)

**Optimal Solution (MTS Level):**
* **Time:** O(N)
* **Space:** O(1) assuming the constraints are fixed (e.g., `1 <= nums[i] <= 100`). Otherwise O(N) with HashMap.

**Why it works:**
Using a fixed-size `int[]` array based on the problem constraints completely eliminates the hashing overhead, object boxing (`int` to `Integer`), and garbage collection footprint of a generic `HashMap`. The postfix increment (`counts[n]++`) elegantly accumulates pairs and increments the frequency map in a single atomic-like operation.

**The Code Skeleton (Java)**
```java
int[] counts = new int[101]; // Assuming constraints 1 <= nums[i] <= 100
int pairCount = 0;
for (int n : nums) {
    pairCount += counts[n]++; // Adds current count to pairs, THEN increments the count.
}
return pairCount;
```

## Problem: Shortest Word Distance (Two Pointers)

**Optimal Solution (MTS Level):**
* **Time:** O(N * L) where L is string length.
* **Space:** O(1)

**Why it works:**
Only recalculate the shortest distance *when one of the pointers actually moves*. Placing the distance calculation inside the `if/else` block prevents redundant `Math.min()` executions. Since `i` is guaranteed to be the larger position at that moment, `Math.abs()` is entirely unnecessary.

**The Code Skeleton (Java)**
```java
int shortestDistance = words.length;
int position1 = -1, position2 = -1; 

for (int i = 0; i < words.length; i++) {
    if (words[i].equals(word1)) {
        position1 = i;
        if (position2 != -1) shortestDistance = Math.min(shortestDistance, i - position2);
    } else if (words[i].equals(word2)) {
        position2 = i;
        if (position1 != -1) shortestDistance = Math.min(shortestDistance, i - position1);
    }
}
return shortestDistance;
```

## Problem: Square Root (Binary Search)

**Optimal Solution (MTS Level):**
* **Time:** O(log X)
* **Space:** O(1)

**Why it works:**
The critical aspect of this pattern is explicitly guarding against integer overflow. Using `left + (right - left) / 2` calculates the mid safely. Casting `(long) mid * mid` guarantees the square does not overflow a 32-bit signed integer before the comparison.

**The Code Skeleton (Java)**
```java
int left = 0, right = x, res = 0;
while (left <= right) {
    int mid = left + (right - left) / 2;
    if ((long) mid * mid <= x) {
        res = mid;
        left = mid + 1;
    } else {
        right = mid - 1;
    }
}
return res;
```

## Problem: Valid Anagram (Frequency Array)

**Optimal Solution (MTS Level):**
* **Time:** O(N)
* **Space:** O(1)

**Why it works:**
Since the character set is restricted to lowercase English letters, a fixed `int[26]` frequency array completely circumvents the `O(N log N)` penalty of sorting and the memory overhead of a `HashMap`. One pass increments counts for `s` and decrements for `t`.

**The Code Skeleton (Java)**
```java
if (s.length() != t.length()) return false;

int[] characters = new int[26];
for (int i = 0; i < s.length(); i++) {
    characters[s.charAt(i) - 'a']++;
    characters[t.charAt(i) - 'a']--;
}

for (int val : characters) {
    if (val != 0) return false;
}
return true;
```