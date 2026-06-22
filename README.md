# 🚀 2026 Interview Prep Master Log

## [2026-06-21] Sunday
**Focus:** Repository Setup, Java Syntax Warmup & DSA Patterns (Pangram Validation)
**Hours Logged:** 2.5h

* **The Bug (Warmup):** Was initially rusty on the exact Java `HashSet` import syntax after focusing heavily on system design and C++ over the last few years.
* **The Fix (Warmup):** Rely on memory muscle. The `.add()` method returning a boolean is a great shortcut to avoid doing `.contains()` followed by `.add()`, saving a double-hash lookup.
* **The Bug (DSA):** Used `String.toCharArray()` for string traversal, allocating unnecessary `O(N)` auxiliary space. Missed edge-case guard clauses for impossible lengths.
* **The Fix (DSA):** Used `String.charAt(i)` for strict `O(1)` space traversing. Implemented Bitmasking using a 32-bit `int` instead of a `boolean[26]` array for extreme memory optimization and CPU caching. Added immediate guard clause `if (sentence == null || sentence.length() < 26) return false;`.

## [2026-06-22] Monday
**Focus:** DSA Patterns - Two Pointers
**Hours Logged:** 1.5h

* **The Bug (Valid Palindrome):** Aggressively cast characters to lowercase before checking if they were alphanumeric. Failed to use nested `while` loops, forcing unnecessary iterations.
* **The Fix (Valid Palindrome):** Used tight inner `while (l < r && !Character.isLetterOrDigit(s.charAt(l)))` loops to skip invalid characters efficiently. Deferred lowercase casting until the direct comparison step.
* **The Bug (Reverse Vowels):** Instantiated a `HashSet<Character>` inside the method, causing severe boxing/unboxing overhead and garbage collection pressure on every call. Erroneously used `StringBuilder` when mutating a string, masking an `O(N)` space allocation behind method overhead.
* **The Fix (Reverse Vowels):** Eliminated the `HashSet` entirely by using a `static boolean isVowel(char)` method powered by an enhanced `switch` expression for `O(1)` lookup with zero boxing. Switched to a raw `char[]` array for direct `O(1)` index swaps instead of using `StringBuilder`.