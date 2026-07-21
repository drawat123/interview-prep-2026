# 🚀 C++ Systems Software Engineer — Master Prep Document

> Target roles: low-level / systems / infrastructure SWE at companies like **Sophos**, **Microsoft**, **NVIDIA**, **Cloudflare**, and **Google Infrastructure**.
> 
> *This single document acts as your Roadmap, Weekly Schedule, and Daily Engineering Log.*

---

## 📅 The Uniform Weekly Schedule

* **Monday:** 1.5h — DS&A patterns in C++ + STL fluency drill (P6)
* **Tuesday:** 1.5h — Rotating fundamentals: OS (P2) / Concurrency (P3) / High-Level System Design (infra roles)
* **Wednesday:** 1.5h — DS&A patterns in C++ (P6)
* **Thursday:** 1.5h — Modern C++ mastery (P1) — Effective Modern C++ items + godbolt
* **Friday:** 1.5h — Systems programming / networking (P4) OR Perf (P5)
* **Saturday:** 4.0h — C++ flagship (`micro-redis`) (2.5h) + Mock/Review (1.5h)
* **Sunday:** 4.0h — C++ flagship (`micro-redis`) (2.5h) + Mock/Review (1.5h)

### Mock Rotation (Sat/Sun 1.5h block) — alternate weekly
1. **Low-Level Design Mock:** allocator / LRU cache / thread pool / lock-free queue
2. **C++ Coding Mock:** 2 unseen mediums in C++, narrate memory & complexity
3. **UB / Code-Review Mock:** spot the data race, use-after-move, aliasing bug
4. **High-Level System Design Mock:** design Twitter / rate limiter / a system at scale — the `02_system_design` folder (kept for infra-heavy loops: Google Infra, Cloudflare, Microsoft)

---

## 🗺️ The Systems Roadmap (7 Pillars)

| # | Pillar | Why it's tested |
|---|---|---|
| P1 | **Modern C++ mastery** | The language IS the interview on this path |
| P2 | **OS & systems fundamentals** | Every systems loop probes this |
| P3 | **Concurrency & lock-free** | The differentiator for senior systems roles |
| P4 | **Systems programming (Linux/POSIX) + net** | The daily job; Cloudflare/Google heavy |
| P5 | **Performance engineering** | "Make it fast, prove it" — the senior signal |
| P6 | **DS&A in C++** | Coding rounds don't disappear |
| P7 | **Low-level system design** | Replaces microservices design |

### 📚 The Detailed Study Tracks
<details>
<summary><b>P1 — Modern C++ Mastery</b></summary>

**Must-know:**
- **RAII** everywhere; rule of 0 / 3 / 5; why rule-of-0 is the goal
- **Move semantics**: rvalue refs, `std::move`, perfect forwarding, `std::forward`, copy elision / RVO/NRVO
- **Smart pointers**: `unique_ptr`, `shared_ptr` (control block, atomic refcount cost), `weak_ptr`
- **Value categories**: lvalue/xvalue/prvalue
- **Templates**: function/class templates, SFINAE, `if constexpr`, concepts
- **STL internals & complexity**: `vector` growth, `unordered_map` rehash, `map` (RB-tree), SSO
- **Undefined behavior**: signed overflow, strict aliasing, use-after-move, data races
- **The C++ memory model**: `std::atomic`, memory orders
- **Modern features**: `std::optional`, `variant`, `string_view`, `span`

**Resources:**
- *Effective Modern C++* (Scott Meyers)
- CppCon Talks (Klaus Iglberger, Chandler Carruth)
</details>

<details>
<summary><b>P2 — OS & Systems Fundamentals</b></summary>

**Must-know:**
- **Virtual memory**: pages, page tables, TLB, page faults, `mmap` vs `brk`
- **Memory allocation**: `malloc`/`free` internals, arenas, fragmentation
- **Scheduling**: context switch cost, CFS basics, priorities
- **Syscalls**: user vs kernel mode, trap mechanism, `strace`
- **IPC**: pipes, shared memory, message queues, sockets
- **Caches**: L1/L2/L3, cache lines (64B), spatial/temporal locality, cache coherence (MESI)

**Resources:**
- *Operating Systems: Three Easy Pieces* (OSTEP)
- *What Every Programmer Should Know About Memory* (Ulrich Drepper)
</details>

<details>
<summary><b>P3 — Concurrency & Lock-Free</b></summary>

**Must-know:**
- `mutex`, `condition_variable`, spurious wakeups
- **`std::atomic`** and memory orders: `relaxed`, `acquire`, `release`, `acq_rel`, `seq_cst`
- **Lock-free structures**: SPSC/MPSC ring buffers, Treiber stack, ABA problem
- **False sharing** and `alignas(64)` padding
- Thread pools, work-stealing, task queues

**Resources:**
- *C++ Concurrency in Action* (Anthony Williams)
- Preshing on Programming (blog)
</details>

<details>
<summary><b>P4 — Systems Programming (Linux/POSIX) + Networking</b></summary>

**Must-know:**
- **I/O multiplexing**: `select` → `poll` → `epoll` → `io_uring`
- Non-blocking sockets, reactor/proactor patterns
- `mmap`, zero-copy (`sendfile`, `splice`)
- **TCP internals**: 3-way handshake, congestion control, TIME_WAIT
- UDP, DNS resolution path

**Resources:**
- *The Linux Programming Interface* (Michael Kerrisk)
- *Beej's Guide to Network Programming*
</details>

<details>
<summary><b>P5 — Performance Engineering</b></summary>

**Must-know:**
- **Profiling**: `perf` (stat/record/report), flamegraphs
- **Benchmarking**: Google Benchmark
- **Sanitizers**: ASan, TSan, UBSan, MSan
- **Cache-aware coding**: data-oriented design, SoA vs AoS
- **Branch prediction**, auto-vectorization (SIMD)

**Resources:**
- Chandler Carruth performance talks
- Compiler Explorer (godbolt.org)
</details>

<details>
<summary><b>P6 — DS&A in C++</b></summary>

**Must-know:**
- Code in C++, not Java. Build STL fluency (`vector`, `unordered_map`, `priority_queue`)
- Talk **memory** out loud: copies vs moves, allocations
- Systems-flavored coding: LRU cache, thread-safe queue, memory pool, bit manipulation

**Resources:**
- Grokking Coding Patterns
- LeetCode tagged "C++"
</details>

<details>
<summary><b>P7 — Low-Level System Design</b></summary>

**Core catalog to drill:**
- LRU / LFU cache (bounded, thread-safe, sharded)
- Memory allocator / slab / arena / object pool
- Thread pool with work-stealing
- Lock-free SPSC/MPSC queue
- In-memory key-value store (concurrency + eviction + persistence)
- Rate limiter internals
</details>

### The Flagship Project — C++ `micro-redis`  🔄
A from-scratch, Redis-protocol-compatible in-memory key–value server in modern
C++20 — the portfolio centerpiece (neutralizes the "MFC is stale" concern with
demonstrably modern systems engineering). Real `redis-cli` / `redis-benchmark`
talk to it unmodified. Repo: <https://github.com/drawat123/micro-redis>

Built rung by rung, each with documented design notes (`docs/notes/`):

| Rung | Focus | Status |
|---|---|---|
| 0 | non-blocking `epoll` reactor (edge-triggered) + RAII `Fd` | ✅ |
| 1 | pure/unit-tested RESP parser + streaming buffers + dispatcher (`SET/GET/DEL/EXISTS/PING`) | ✅ |
| 2 | TTL expiration — lazy + active sweep, `steady_clock`, injectable time for tests | ✅ |
| 3 | bounded **LRU eviction** — O(1) list + hash map (`--maxkeys`, `DBSIZE`) | ✅ |
| 4 | **performance** — `TCP_NODELAY` (fixed a 19× Nagle stall), reply batching, `EPOLLOUT` write buffer, C++20 heterogeneous lookup | ✅ |
| 6 | **persistence** — snapshot via `fork()` + Copy-On-Write | 🔄 |
| 7 | concurrency / thread pool | ⏳ |

**Measured (Release, vs real Redis on the same host):** ~290k rps non-pipelined
(≈ Redis, both syscall-bound); **3.7M/4.0M rps SET/GET pipelined** (`-P 16`) —
exceeds Redis on the microbenchmark *because it does far less per command*
(simpler, not better). Key skills shown: reactor pattern, TCP internals
(Nagle/backpressure/`EPOLLOUT`), O(1) LRU, dependency-injected time for testing,
RAII/move semantics, and evidence-driven perf engineering.

---

## 📂 Simplified Repository Structure

```text
interview-prep-2026/
├── 01_dsa_patterns/                 # now coded in C++ (Java history kept)
│   ├── 01_warmup_notes.md           # Flatted notes for easy access
│   ├── 02_two_pointers_notes.md     # Systems-focused complexity cheat sheets
│   └── ...
├── 02_system_design/                # high-level (kept for infra roles)
├── 04_low_level_design/             # P7 — allocator, LRU, thread pool, lock-free queue
├── 05_cpp_mastery/                  # P1 — Effective Modern C++ notes, UB drills
├── 06_os_systems/                   # P2 — OSTEP notes, toy allocator, syscalls
├── 07_concurrency/                  # P3 — memory-model notes, SPSC/MPSC
├── 08_systems_programming/          # P4 — epoll/io_uring servers, socket exercises
├── 09_performance/                  # P5 — perf writeups, flamegraphs, benchmarks
└── README.md                        # THIS FILE (Roadmap + Schedule + Daily Log)

# The C++ FLAGSHIP lives in its OWN repo (portfolio, not prep):
#   ~/Documents/Study/micro-redis/
```

---

## 📝 Daily Engineering Log

### [2026-06-21] Sunday
**Focus:** Repository Setup, Java Syntax Warmup & DSA Patterns (Pangram Validation)
**Hours Logged:** 2.5h

* **The Bug (Warmup):** Was initially rusty on the exact Java `HashSet` import syntax after focusing heavily on system design and C++ over the last few years.
* **The Fix (Warmup):** Rely on memory muscle. The `.add()` method returning a boolean is a great shortcut to avoid doing `.contains()` followed by `.add()`, saving a double-hash lookup.
* **The Bug (DSA):** Used `String.toCharArray()` for string traversal, allocating unnecessary `O(N)` auxiliary space. Missed edge-case guard clauses for impossible lengths.
* **The Fix (DSA):** Used `String.charAt(i)` for strict `O(1)` space traversing. Implemented Bitmasking using a 32-bit `int` instead of a `boolean[26]` array for extreme memory optimization and CPU caching. Added immediate guard clause `if (sentence == null || sentence.length() < 26) return false;`.

### [2026-06-22] Monday
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

### [2026-06-28] Tuesday
**Focus:** High-Level System Design (Grokking Vol I / Vol II)
**Hours Logged:** 1.5h

* **The Bug (Engineering Hygiene):** Created a markdown file with a `?` character in the filename (`02_back-of-the-envelope_estimations?.md`). Special characters in filenames break shell scripts, build pipelines, and CI/CD tools.
* **The Fix (Engineering Hygiene):** Renamed the file to strip the `?`.
* **System Design Check-In (Load Balancing):** Successfully documented core load balancing algorithms. Faced Senior/MTS level pushback. Identified knowledge gaps in HTTP/2 Multiplexing, Stateless Architecture (Redis/Thundering Herd mitigation), and L4 vs L7 routing profiles. Created advanced Q&A notes to bridge these gaps.

### [2026-07-01] Wednesday
**Focus:** DSA Patterns - Two Pointers (Advanced)
**Hours Logged:** 1.5h

* **The Bug (Squaring Sorted Array):** Massively over-engineered the solution by using Binary Search to find the zero-crossing, followed by an outward-moving merge with 3 separate `while` loops.
* **The Fix (Squaring Sorted Array):** Leveraged the mathematical property of sorted arrays (largest squares are always at the outermost edges). Used Inward-Moving Pointers to compare the absolute ends and write directly to the end of the new array. Reduced `O(log N) + O(N)` complexity to a strict, elegant `O(N)` single pass.
* **The Bug (Triplet Sum to Zero):** Created inefficient routing logic by combining `currSum < 0` and `currSum == 0`. Failed to eagerly decrement the right pointer when a match was found, causing wasted loop iterations.
* **The Fix (Triplet Sum to Zero):** Explicitly branched logic. Aggressively incremented/decremented both pointers and aggressively skipped duplicates on both ends the moment a valid triplet was added to the list, maximizing CPU efficiency.
* **The Bug (Remove Duplicates):** Wrote perfect `O(N)` logic but failed to include a guard clause for empty arrays, risking an `ArrayIndexOutOfBoundsException` at `arr[0]`.
* **The Fix (Remove Duplicates):** Added immediate guard clause `if (arr == null || arr.length == 0) return 0;` (MTS baseline standard).

### [2026-07-05] Saturday — 🔀 PIVOT: Backend → C++ Systems Software Engineer
**Focus:** Career-track pivot. Retargeting prep from generic senior backend to **C++ Systems Software Engineer** (Sophos, Microsoft, NVIDIA, Cloudflare, Google Infra).
**Hours Logged:** —

* **The Decision:** 6 yrs experience (4 C++/MFC, 2 backend). On the backend path my short backend tenure risks an L4 down-level; on the systems path my C++ years count fully. Systems work also matches my instincts (the Java side project gravitated to concurrency/backpressure/lock-free naturally).
* **What changes:**
  * **Dropped:** Microservices design patterns. DataLemur SQL (`03_datalemur_sql` archived from core prep, kept strictly as a weekend hobby).
  * **Added pillars:** Modern C++ mastery (`05_cpp_mastery`), OS fundamentals (`06_os_systems`), concurrency/lock-free (`07_concurrency`), systems programming + networking (`08_systems_programming`), performance engineering (`09_performance`), low-level design (`04_low_level_design`).
  * **Kept:** DSA (now coded in **C++**, not Java) and high-level system design (still tested for infra roles).
  * **Side project:** freeze backend projects as design/comparison artifacts; new flagship = an in-memory KV store rebuilt in **modern C++** in its own repo (`micro-redis`).
* **Biggest risk to close:** 4 yrs of C++ was MFC-era — must prove *modern* C++ (C++17/20). Modern-C++ mastery is front-loaded (Phase 0).

### [2026-07-13] Monday
**Focus:** DSA Patterns in C++ (Two Pointers)
**Hours Logged:** 1.5h

* **The Bug (API & Types):** Mutated caller's array by passing non-const reference `std::vector<int>&` into `std::sort()`. Triggered unsigned integer underflow (UB) by computing `arr.size() - 2` without checking if size < 2. Failed to cast to `long long` when subtracting from `targetSum`, risking standard integer overflow.
* **The Fix (API & Types):** Reverted signature to pass-by-value `std::vector<int> arr` to protect caller state. Added strict guard clause `if (arr.size() < 3) return 0;` to prevent `size_t` wrap-around. Casted `targetSum` to `long long` before sequential subtraction to guarantee mathematical safety.

### [2026-07-14] Tuesday
**Focus:** OS Fundamentals (OSTEP Intro)
**Hours Logged:** 1.5h

* **The Execution:** Completed core introductory reading on the Three Easy Pieces: Virtualization, Concurrency, and Persistence. Connected theoretical OS illusions (infinite CPUs, private address spaces) to real-world systems engineering (context switching, virtual memory mappings, and non-atomic instruction traps).
* **The Blindspot (OS/Memory):** Knew that processes do not share physical memory, but missed the *mechanism*: the OS maintains a **Page Table** for each process to map virtual addresses to physical frames via the hardware MMU.
* **The Blindspot (C++ Concurrency):** Forgot the `<atomic>` library. To safely increment a shared counter without a mutex, use `std::atomic<int>`, which relies on hardware-level atomic instructions (like Compare-And-Swap) to lock the cache line.

### [2026-07-15] Wednesday
**Focus:** DSA Patterns in C++ (Two Pointers)
**Hours Logged:** 1.5h

* **The Bug (Algorithmic & C++):** Got stuck trying to strictly use two pointers. Missed the need for a three-pointer partition (`low`, `high`, `i`). Also, initializing `int high = arr.size() - 1;` without checking for an empty array relies on dangerous unsigned-to-signed underflow truncation (`SIZE_MAX` truncating to `-1`).
* **The Fix (Algorithmic & C++):** Used a three-pointer approach with a `switch` statement. Passed `arr` as `const std::vector<int>&` to copy it locally without mutating the caller's array.

### [2026-07-16] Thursday
**Focus:** Modern C++ Mastery (Effective Modern C++)
**Hours Logged:** 1.5h

* **The Execution:** Read Items 1 & 2 (Template and `auto` type deduction). Mastered the three core deduction cases (Reference, Universal Reference, Pass-by-Value). 
* **The Process Win (Systems Safety):** Correctly identified the `auto` performance trap. Realized that `auto` strips reference and `const` qualifiers during pass-by-value deduction, which causes massive, unintentional heap allocations if large containers returned by `const&` are accidentally assigned to plain `auto` instead of `const auto&`.

### [2026-07-17] Friday
**Focus:** Performance Engineering (Cache Locality)
**Hours Logged:** 1.5h

* **The Execution:** Ran a C++ sandbox comparing Row-by-Row vs Column-by-Column matrix traversals. Measured a massive >4x performance degradation despite identical `O(N)` theoretical time complexity.
* **The Blindspot (Hardware Architecture):** Didn't understand how CPU Cache Lines work under the hood. Learned that CPUs fetch RAM in 64-byte chunks. Column-major traversal destroys spatial locality, causing a hardware "Cache Miss" on every single iteration and forcing the CPU to sit idle waiting for RAM.