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