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

## [2026-07-05] Saturday — 🔀 PIVOT: Backend → C++ Systems Software Engineer
**Focus:** Career-track pivot. Retargeting prep from generic senior backend to **C++ Systems Software Engineer** (Sophos, Microsoft, NVIDIA, Cloudflare, Google Infra).
**Hours Logged:** —

* **The Decision:** 6 yrs experience (4 C++/MFC, 2 backend). On the backend path my short backend tenure risks an L4 down-level; on the systems path my C++ years count fully. Systems work also matches my instincts (the Java side project gravitated to concurrency/backpressure/lock-free naturally).
* **What changes:**
  * **Dropped:** Microservices design patterns. DataLemur SQL (`03_datalemur_sql` archived from core prep, kept strictly as a weekend hobby).
  * **Added pillars:** Modern C++ mastery (`05_cpp_mastery`), OS fundamentals (`06_os_systems`), concurrency/lock-free (`07_concurrency`), systems programming + networking (`08_systems_programming`), performance engineering (`09_performance`), low-level design (`04_low_level_design`).
  * **Kept:** DSA (now coded in **C++**, not Java) and high-level system design (still tested for infra roles).
  * **Side project:** freeze `micro-thingsboard` (Java) as a design/comparison artifact; new flagship = the same telemetry engine rebuilt in **modern C++** in its own repo (`micro-thingsboard-cpp`).
* **Biggest risk to close:** 4 yrs of C++ was MFC-era — must prove *modern* C++ (C++17/20). Modern-C++ mastery is front-loaded (Phase 0).
* **Reference:** full plan in `systems_roadmap.md`; revised cadence in `weekly_template.md`.

## [2026-07-13] Monday
**Focus:** DSA Patterns in C++ (Two Pointers)
**Hours Logged:** 1.5h

* **The Bug (API & Types):** Mutated caller's array by passing non-const reference `std::vector<int>&` into `std::sort()`. Triggered unsigned integer underflow (UB) by computing `arr.size() - 2` without checking if size < 2. Failed to cast to `long long` when subtracting from `targetSum`, risking standard integer overflow.
* **The Fix (API & Types):** Reverted signature to pass-by-value `std::vector<int> arr` to protect caller state. Added strict guard clause `if (arr.size() < 3) return 0;` to prevent `size_t` wrap-around. Casted `targetSum` to `long long` before sequential subtraction to guarantee mathematical safety.

## [2026-07-14] Tuesday
**Focus:** OS Fundamentals (OSTEP Intro)
**Hours Logged:** 1.5h

* **The Execution:** Completed core introductory reading on the Three Easy Pieces: Virtualization, Concurrency, and Persistence. Connected theoretical OS illusions (infinite CPUs, private address spaces) to real-world systems engineering (context switching, virtual memory mappings, and non-atomic instruction traps).
* **The Blindspot (OS/Memory):** Knew that processes do not share physical memory, but missed the *mechanism*: the OS maintains a **Page Table** for each process to map virtual addresses to physical frames via the hardware MMU.
* **The Blindspot (C++ Concurrency):** Forgot the `<atomic>` library. To safely increment a shared counter without a mutex, use `std::atomic<int>`, which relies on hardware-level atomic instructions (like Compare-And-Swap) to lock the cache line.

## [2026-07-15] Wednesday
**Focus:** DSA Patterns in C++ (Two Pointers)
**Hours Logged:** 1.5h

### Problem 1: Dutch National Flag
* **The Bug (Algorithmic & C++):** Got stuck trying to strictly use two pointers. Missed the need for a three-pointer partition (`low`, `high`, `i`). Also, initializing `int high = arr.size() - 1;` without checking for an empty array relies on dangerous unsigned-to-signed underflow truncation (`SIZE_MAX` truncating to `-1`).
* **The Fix (Algorithmic & C++):** Used a three-pointer approach with a `switch` statement. Passed `arr` as `const std::vector<int>&` to copy it locally without mutating the caller's array.

### Problem 2: Quadruple Sum to Target
* **The Bug (Integer Promotion):** Wrote `long long sum = arr[i] + arr[j] + arr[k] + arr[l];`. Because all operands are `int`, the addition is executed as a 32-bit `int` addition (which can overflow) *before* the result is assigned to the `long long`.
* **The Fix (Integer Promotion):** Explicitly cast the first operand to force 64-bit addition across the whole expression: `long long sum = static_cast<long long>(arr[i]) + arr[j] + arr[k] + arr[l];`.
* **The Process Win (Debugging):** Made classical loop/index typos (`i++` instead of `j++`, `j!=1` instead of `j!=i+1`). Instead of using print statements, successfully spun up `lldb` in the terminal to trace execution and isolate the bugs. Excellent systems engineering hygiene.

### Problem 3: Comparing Strings containing Backspaces
* **The Bug (Algorithmic):** Attempted to process backspaces directly in the main loop, failing to handle cascading backspaces (e.g., `a#c#`). Also risked an out-of-bounds segfault if one string was fully processed (`r1 < 0`) while the other wasn't.
* **The Fix (Algorithmic):** Refactored the core backspace logic into a dedicated helper function (`getNextValidCharIndex`) that properly counts and resolves cascading deletes. Explicitly handled negative index edge cases (`i1 < 0 || i2 < 0`) before making the array access comparison.

## [2026-07-16] Thursday
**Focus:** Modern C++ Mastery (Effective Modern C++)
**Hours Logged:** 1.5h

* **The Execution:** Read Items 1 & 2 (Template and `auto` type deduction). Mastered the three core deduction cases (Reference, Universal Reference, Pass-by-Value). 
* **The Process Win (Systems Safety):** Correctly identified the `auto` performance trap. Realized that `auto` strips reference and `const` qualifiers during pass-by-value deduction, which causes massive, unintentional heap allocations if large containers returned by `const&` are accidentally assigned to plain `auto` instead of `const auto&`.