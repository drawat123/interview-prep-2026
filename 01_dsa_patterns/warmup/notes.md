# Pattern: Warmup
**Problem:** Contains Duplicate

**Optimal Solution (Implemented):** * **Time:** O(N) - Single pass through the array.
* **Space:** O(N) - HashSet scales linearly with input size.
* **Why it works:** `HashSet.add()` returns `false` if the element already exists. Wrapping it in `if (!hashSet.add(num))` is extremely clean.

**Alternative (Space-Optimized):**
* If the interviewer says "O(1) memory only", we must sort the array first `Arrays.sort(nums)`, then check adjacent elements `nums[i] == nums[i+1]`. 
* **Trade-off:** Time complexity degrades from O(N) to O(N log N) due to sorting. Space becomes O(1).

## The Code Skeleton (Java)
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

---

**Problem:** Check if Sentence Is Pangram

**Optimal Solution (MTS Level - Bitmasking):** 
* **Time:** O(N) - Single pass through the string.
* **Space:** O(1) - Single 32-bit integer used for tracking.

**Why it works:** 
Instead of an array allocation (`boolean[26]`), use an `int` to store bits. For each char, set the corresponding bit `seen |= (1 << val)`. A complete pangram means the first 26 bits are set to 1, which equals `(1 << 26) - 1`.

## The Code Skeleton (Java)
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