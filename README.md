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
* **The Bug (Number of Good Pairs):** Used a `HashMap` despite constrained inputs, introducing severe boxing and hashing overhead.
* **The Fix (Number of Good Pairs):** Leveraged an `int[] counts = new int[101]` and compressed the logic using a postfix increment `pairCount += counts[n]++;` to elegantly sum and increment simultaneously.
* **The Bug (Shortest Word Distance):** Placed the distance calculation `Math.min()` outside the pointer-check branches, causing redundant executions on irrelevant words.
* **The Fix (Shortest Word Distance):** Moved the calculation inside the `if` branches and eliminated `Math.abs()` since the current index `i` is guaranteed to be the larger value.
* **The Fix (Square Root / Valid Anagram):** Flawless execution. Guarded overflow correctly with `left + (right - left) / 2` and `(long) mid * mid`, and avoided `HashMap` with an `int[26]` frequency array.

## [2026-06-28] Tuesday
**Focus:** High-Level System Design (Grokking Vol I / Vol II)
**Hours Logged:** 1.5h

* **The Bug (Engineering Hygiene):** Created a markdown file with a `?` character in the filename (`02_back-of-the-envelope_estimations?.md`). Special characters in filenames break shell scripts, build pipelines, and CI/CD tools.
* **The Fix (Engineering Hygiene):** Renamed the file to strip the `?`.
* **System Design Check-In (Load Balancing):** Successfully documented core load balancing algorithms. Faced Senior/MTS level pushback. Identified knowledge gaps in HTTP/2 Multiplexing, Stateless Architecture (Redis/Thundering Herd mitigation), and L4 vs L7 routing profiles. Created advanced Q&A notes to bridge these gaps.

## [2026-07-01] Wednesday
**Focus:** DSA Patterns - Two Pointers (Advanced)
**Hours Logged:** 1.5h

* **The Bug (Squaring Sorted Array):** Massively over-engineered the solution by using Binary Search to find the zero-crossing, followed by an outward-moving merge with 3 separate `while` loops.
* **The Fix (Squaring Sorted Array):** Leveraged the mathematical property of sorted arrays (largest squares are always at the outermost edges). Used Inward-Moving Pointers to compare the absolute ends and write directly to the end of the new array. Reduced `O(log N) + O(N)` complexity to a strict, elegant `O(N)` single pass.
* **The Bug (Triplet Sum to Zero):** Created inefficient routing logic by combining `currSum < 0` and `currSum == 0`. Failed to eagerly decrement the right pointer when a match was found, causing wasted loop iterations.
* **The Fix (Triplet Sum to Zero):** Explicitly branched logic. Aggressively incremented/decremented both pointers and aggressively skipped duplicates on both ends the moment a valid triplet was added to the list, maximizing CPU efficiency.
* **The Bug (Remove Duplicates):** Wrote perfect `O(N)` logic but failed to include a guard clause for empty arrays, risking an `ArrayIndexOutOfBoundsException` at `arr[0]`.
* **The Fix (Remove Duplicates):** Added immediate guard clause `if (arr == null || arr.length == 0) return 0;` (MTS baseline standard).