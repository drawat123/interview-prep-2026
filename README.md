# 🚀 2026 Interview Prep Master Log

## [2026-06-21] Sunday
**Focus:** Repository Setup, Java Syntax Warmup & DSA Patterns (Pangram Validation)
**Hours Logged:** 2.5h

* **The Bug (Warmup):** Was initially rusty on the exact Java `HashSet` import syntax after focusing heavily on system design and C++ over the last few years.
* **The Fix (Warmup):** Rely on memory muscle. The `.add()` method returning a boolean is a great shortcut to avoid doing `.contains()` followed by `.add()`, saving a double-hash lookup.
* **The Bug (DSA):** Used `String.toCharArray()` for string traversal, allocating unnecessary `O(N)` auxiliary space. Missed edge-case guard clauses for impossible lengths.
* **The Fix (DSA):** Used `String.charAt(i)` for strict `O(1)` space traversing. Implemented Bitmasking using a 32-bit `int` instead of a `boolean[26]` array for extreme memory optimization and CPU caching. Added immediate guard clause `if (sentence == null || sentence.length() < 26) return false;`.