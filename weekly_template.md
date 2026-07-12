### **The Uniform Weekly Template — C++ Systems Track**

> Retargeted 2026-07-05 from backend to **C++ Systems Software Engineer**.
> Full plan: `systems_roadmap.md`. Old backend cadence is in git history.

* **Monday:** 1.5h — DS&A patterns **in C++** + STL fluency drill (P6)
* **Tuesday:** 1.5h — Rotating fundamentals: OS (P2) / Concurrency (P3), per current phase
* **Wednesday:** 1.5h — DS&A patterns **in C++** (P6)
* **Thursday:** 1.5h — Modern C++ mastery (P1) — *Effective Modern C++* items + godbolt
* **Friday:** 1.5h — Systems programming / networking (P4) **or** Performance (P5), per phase
* **Saturday:** 4.0h — C++ flagship project (2.5h) + Mock/Review (1.5h)
* **Sunday:** 4.0h — C++ flagship project (2.5h) + Mock/Review (1.5h)

> **What changed vs. the old plan:** SQL dropped; microservices → low-level
> design; Java → C++; backend side project → C++ flagship. High-level system
> design folded into the Tuesday rotation (kept for infra roles).

---

### **Mock Rotation (the Sat/Sun 1.5h block) — alternate weekly**

Pick one per weekend and cycle through all three:

1. **Low-Level Design Mock** (allocator / LRU cache / thread pool / lock-free queue)
2. **C++ Coding Mock** (2 mediums in C++, narrate memory & complexity)
3. **UB / Code-Review Mock** (spot the data race / use-after-move / aliasing bug)

---

### **Mock 1: The Low-Level Design Mock (90 Minutes)**

For systems loops, your ability to reason about data structures, concurrency, and
memory under the hood is graded as heavily as the design itself. Practice out loud.

* **Minute 0–45 (The Performance):**
  * Pick a component from `04_low_level_design/` (e.g., "Design a thread-safe LRU cache" or "Design an object pool allocator").
  * Blank whiteboard (Excalidraw or physical). Timer 45 min.
  * **Talk out loud.** Walk the systems 6: **Requirements/constraints → API → Data structures → Concurrency model → Memory strategy → Failure modes & complexity.** When stuck (e.g., how to shard for concurrency), force a decision and justify it aloud.

* **Minute 45–90 (The Tear-Down):**
  * Compare against a reference (Redis/memcached/folly/Disruptor internals, or a known writeup).
  * Did you miss false sharing? An allocation on the hot path? A lock you could make lock-free? An eviction edge case?
  * Write exact blind spots into `daily_log` so you know what to review.

### **Mock 2: The C++ Coding Mock (90 Minutes)**

Write bug-free **C++** without IDE crutches, and reason about memory as you go.

* **Minute 0–60 (The Execution):**
  * Pick 2 unseen "Medium" pattern questions (or 1 medium + 1 systems-flavored: LRU cache, thread-safe queue, memory pool, bit manipulation, a parser).
  * Raw editor / LeetCode with the run button **hidden**. Timer on.
  * Talk out loud: state space/time complexity **and memory** — copies vs moves, where a `std::vector` reallocates, when to `reserve()`, whether a `string_view` avoids a copy.
  * Finish writing before the timer hits zero.

* **Minute 60–90 (The Debugging):**
  * Run it. On failure, don't peek — spend 15 min with gdb/prints tracing it yourself.
  * Review the optimal: did you make an unnecessary copy, an `O(N)` alloc, or miss a move?

### **Mock 3: The UB / Code-Review Mock (60–90 Minutes)**

A systems-interview staple with no backend equivalent — you'll be handed a snippet
and asked "what's wrong with this?"

* Pull a snippet from `05_cpp_mastery/ub_drills/` (build this set over time).
* Find the defect **by eye first**: data race, use-after-move, dangling reference,
  strict-aliasing violation, signed overflow, iterator invalidation, missing `noexcept`.
* Then confirm with tools: compile with `-Wall -Wextra`, run under **ASan/UBSan/TSan**.
* Log the class of bug and the tell that reveals it.

### **The Golden Rules of the Mock Block**

1. **Never pause the timer.** If you freeze in a real interview, the clock keeps ticking. Learn to manage the panic.
2. **Talk to the wall.** Speaking technical thoughts clearly is a separate muscle from writing code. Train it.
3. **No looking up syntax.** Forget the exact STL method or `std::atomic` memory order? Write a placeholder (`// assume acquire load here`) and keep moving.
4. **Always reason about memory.** On this path, "it's correct" isn't enough — say where it allocates, copies, moves, and where a cache line bounces.

---

### The GitHub Repository Strategy

```text
interview-prep-2026/                 # PREP ONLY (exercises, notes, log)
│
├── 01_dsa_patterns/                 # now coded in C++ (Java history kept)
├── 02_system_design/                # high-level (kept for infra roles)
├── 03_datalemur_sql/                # ARCHIVED (backend track)
├── 04_low_level_design/             # P7 — allocator, LRU, thread pool, lock-free queue
├── 05_cpp_mastery/                  # P1 — Effective Modern C++ notes, UB drills, godbolt
├── 06_os_systems/                   # P2 — OSTEP notes, toy allocator, syscall experiments
├── 07_concurrency/                  # P3 — memory-model notes, SPSC/MPSC implementations
├── 08_systems_programming/          # P4 — epoll/io_uring servers, socket exercises
├── 09_performance/                  # P5 — perf writeups, flamegraphs, benchmarks
├── systems_roadmap.md               # the master plan
├── weekly_template.md               # this file
└── README.md                        # daily_log (engineering changelog for your brain)

# The C++ FLAGSHIP lives in its OWN repo (portfolio, not prep):
#   ~/Documents/Study/micro-thingsboard-cpp/
```

---

### 1. The Micro Template: notes.md

### [Topic / Pattern Name]

### The Core Concept
* **The Trick:** [Main intuition in 1–2 sentences.]
* **Data Structure Used:** [e.g., intrusive list, min-heap, ring buffer]

### Complexity
* **Time:** `O(?)` — [why]
* **Space:** `O(?)` — [why]

### Memory / Perf note   ← systems-specific field
* [Where it allocates/copies/moves; cache behavior; any UB risk; move vs copy.]

### The Code Skeleton (C++)
```cpp
// Paste ONLY the crucial logic, not boilerplate.
// Highlight the specific lines you struggled to remember.
```

### 2. The Macro Template: `daily_log.md` (this repo's README.md)

An engineering changelog for your brain — treat it like commit history. Append a
new block at the bottom every day.

```markdown
# 🚀 2026 Interview Prep Master Log

### [YYYY-MM-DD] - [Day of Week]
**Focus:** [e.g., Modern C++: move semantics | Low-Level Design: LRU cache]
**Hours Logged:** [e.g., 1.5h]

* **The Bug / Blindspot:** [Be specific. e.g., "Returned a std::string by value in a hot loop — unnecessary copy; didn't mention it aloud."]
* **The Fix:** [Actionable. e.g., "Return string_view when the buffer outlives the call; reserve() before the append loop."]
```

---
