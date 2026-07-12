# C++ Systems Software Engineer — Industry-Generic Roadmap

> Target roles: low-level / systems / infrastructure SWE at companies like
> **Sophos** (endpoint security), **Microsoft** (Windows/Azure/systems),
> **NVIDIA** (drivers/CUDA/runtime), **Cloudflare** (networking/edge),
> **Google Infrastructure**, and similar (Bloomberg, Databricks storage,
> ScyllaDB, Arm, Qualcomm, HFT shops).
>
> Author profile this is tuned for: ~6 yrs total — ~4 yrs C++/MFC (needs
> modernization), ~2 yrs backend. The #1 job of this plan is to convert
> "old C++" into "modern systems C++" and add the OS/concurrency/perf depth
> that systems loops actually test.
>
> **Status legend:** ⬜ not started · 🔄 in progress · ✅ done

---

## 0. How systems interviews differ from backend interviews

| Dimension | Backend loop (your old plan) | Systems loop (this plan) |
|---|---|---|
| Language | Java/Python, language is a vehicle | **C++ itself is tested** — move semantics, UB, memory model |
| Coding | LeetCode DS&A | DS&A **in C++**, plus "implement an allocator / lock-free queue / thread pool" |
| System design | Services, DBs, APIs, sagas | **Low-level**: caches, memory pools, KV internals, schedulers, + some distributed |
| Fundamentals | HTTP, REST, SQL | **OS, virtual memory, concurrency, cache coherence, networking internals** |
| Perf | "Add a cache/index" | Profiling, cache misses, branch prediction, SIMD, sanitizers |
| SQL | Heavy | **~Zero** |

**Takeaway:** SQL and microservices patterns are largely dropped. Modern C++,
OS, concurrency, and performance are added. DS&A and high-level system design
stay (infra roles still test them).

---

## 1. The Seven Pillars

Everything below maps to one of these. Rate yourself 1–5 now and re-rate monthly.

| # | Pillar | Why it's tested | Self-rating |
|---|---|---|---|
| P1 | **Modern C++ mastery** | The language IS the interview on this path | __ /5 |
| P2 | **OS & systems fundamentals** | Every systems loop probes this | __ /5 |
| P3 | **Concurrency & lock-free** | The differentiator for senior systems roles | __ /5 |
| P4 | **Systems programming (Linux/POSIX) + networking** | The daily job; Cloudflare/Google heavy | __ /5 |
| P5 | **Performance engineering** | "Make it fast, prove it" — the senior signal | __ /5 |
| P6 | **DS&A in C++** | Coding rounds don't disappear | __ /5 |
| P7 | **Low-level system design** | Replaces microservices design | __ /5 |

---

## P1 — Modern C++ Mastery  ⬜

**This is your highest-leverage pillar.** MFC-era C++ (raw `new`/`delete`,
`CString`, message pumps) is a red flag; C++17/20 fluency is the fix.

### Must-know
- **RAII** everywhere; rule of 0 / 3 / 5; why rule-of-0 is the goal
- **Move semantics**: rvalue refs, `std::move`, perfect forwarding, `std::forward`, copy elision / RVO/NRVO
- **Smart pointers**: `unique_ptr`, `shared_ptr` (control block, atomic refcount cost), `weak_ptr`, when raw pointers are still correct
- **Value categories**: lvalue/xvalue/prvalue (know why they exist)
- **Templates**: function/class templates, SFINAE, `if constexpr`, variadic templates, CRTP, concepts (C++20)
- **`constexpr` / `consteval`**, compile-time computation
- **STL internals & complexity**: `vector` growth & invalidation, `unordered_map` load factor & rehash, `map` (RB-tree), small-string optimization, `deque` block layout, when each container reallocates/invalidates
- **Undefined behavior**: signed overflow, strict aliasing, use-after-move, data races, dangling refs — be able to *spot* UB in a snippet (common interview drill)
- **The C++ memory model** (feeds into P3): `std::atomic`, memory orders
- **Modern features**: `std::optional`, `variant`, `string_view`, `span`, structured bindings, ranges (C++20), `std::expected` (C++23 awareness)
- **Error handling**: exceptions vs error codes vs `expected`, `noexcept` and why it matters for move
- **ABI / linkage basics**: `inline`, ODR, translation units, `extern "C"`

### Resources
- **Book:** *Effective Modern C++* — Scott Meyers (the core text; do all 42 items)
- **Book:** *C++ Concurrency in Action* — Anthony Williams (also covers P3)
- **Reference:** cppreference.com (live in it), C++ Core Guidelines
- **Talks:** CppCon — Klaus Iglberger "Back to Basics: Move Semantics", "The Rule of Five", Chandler Carruth performance talks
- **Practice:** rewrite an old MFC/C++ class of yours in modern C++; run it through clang-tidy

---

## P2 — OS & Systems Fundamentals  ⬜

### Must-know
- **Process vs thread**: address space, what's shared, cost of each
- **Virtual memory**: pages, page tables, TLB, page faults, `mmap` vs `brk`, demand paging, copy-on-write, huge pages
- **Memory allocation**: how `malloc`/`free` work (bins, arenas), fragmentation, why custom allocators exist, stack vs heap
- **Scheduling**: preemptive scheduling, context switch cost, CFS basics, priorities, CPU affinity
- **Syscalls**: user vs kernel mode, the trap mechanism, syscall cost, `strace`
- **Concurrency primitives at OS level**: futex, how mutexes are built
- **Signals**, process lifecycle (fork/exec/wait), zombies/orphans
- **IPC**: pipes, shared memory, message queues, sockets, semaphores
- **File systems / I/O**: buffered vs direct I/O, page cache, `fsync`, inodes (conceptual)
- **Caches & memory hierarchy**: L1/L2/L3, cache lines (64B), spatial/temporal locality, cache coherence (**MESI**), false sharing, NUMA

### Resources
- **Book:** *Operating Systems: Three Easy Pieces* (OSTEP) — free online, the best OS book
- **Book:** *Computer Systems: A Programmer's Perspective* (CS:APP) — chapters on memory, linking, exceptions
- **Reference:** *What Every Programmer Should Know About Memory* — Ulrich Drepper (the cache/NUMA bible)
- **Hands-on:** write a toy allocator; measure a cache-miss with `perf stat`

---

## P3 — Concurrency & Lock-Free  ⬜

**The senior systems differentiator.** Most candidates can use a mutex; few can
reason about memory ordering. This is where you separate from the pack.

### Must-know
- Threads, `std::thread`, `jthread`, thread lifecycle
- `mutex`, `shared_mutex`, `condition_variable`, spurious wakeups, the "wait predicate" idiom
- **`std::atomic`** and the **memory model**: `relaxed`, `acquire`, `release`, `acq_rel`, `seq_cst` — know a real use for each
- **Lock-free structures**: SPSC/MPSC ring buffers, Treiber stack, Michael-Scott queue, the **ABA problem** and how to defeat it (tagged pointers, hazard pointers, epoch/RCU at a conceptual level)
- **False sharing** and `alignas(64)` padding
- Thread pools, work-stealing, task queues
- Deadlock / livelock / priority inversion; lock ordering
- `std::async`, futures/promises, `std::latch`/`barrier`/`counting_semaphore` (C++20)
- Cost model: what an atomic actually costs vs a cache-line bounce

### Resources
- **Book:** *C++ Concurrency in Action* — Anthony Williams (the definitive text)
- **Talks:** Herb Sutter "atomic<> Weapons" (2-part), Fedor Pikus "C++ atomics" & "Live Lock-Free or Deadlock", CppCon lock-free talks
- **Reference:** Preshing on Programming (blog) — best intuition for memory ordering
- **Hands-on:** implement an SPSC lock-free ring buffer; verify with **TSan**

---

## P4 — Systems Programming (Linux/POSIX) + Networking  ⬜

### Systems programming
- POSIX file/process/thread APIs
- **I/O multiplexing**: `select` → `poll` → **`epoll`** → **`io_uring`** (know the evolution and why each exists)
- Non-blocking sockets, the reactor/proactor patterns
- `mmap` for files and shared memory, zero-copy (`sendfile`, `splice`)
- ELF basics, static vs dynamic linking, `LD_PRELOAD`, symbol resolution
- `/proc`, `/sys`, resource limits, `cgroups` (conceptual)

### Networking (Cloudflare/Google-critical)
- TCP/IP model, encapsulation
- **TCP internals**: 3-way handshake, flow control (window), congestion control (slow start, AIMD), Nagle's algorithm, TIME_WAIT/CLOSE_WAIT, head-of-line blocking
- UDP and when to prefer it
- Sockets API end-to-end (you've done raw TCP in the Java project — redo in C)
- HTTP/1.1 vs 2 vs 3/QUIC (high level), TLS handshake (high level)
- DNS resolution path

### Resources
- **Book:** *The Linux Programming Interface* — Michael Kerrisk (the POSIX bible; reference, not cover-to-cover)
- **Book:** *Beej's Guide to Network Programming* (free, fast on-ramp to sockets)
- **Book:** *TCP/IP Illustrated Vol. 1* — Stevens (reference for TCP internals)
- **Hands-on:** build an `epoll`-based echo server in C++; then an `io_uring` version

---

## P5 — Performance Engineering  ⬜

The "prove it's fast" pillar — turns claims into numbers (your L5 signal).

### Must-know
- **Profiling**: `perf` (stat/record/report), flamegraphs, `perf top`; VTune (Intel), `gprof` awareness
- **Benchmarking**: Google Benchmark, avoiding measurement pitfalls (warmup, `DoNotOptimize`, variance)
- **Sanitizers**: ASan, TSan, UBSan, MSan — run everything under them
- **Memory tooling**: valgrind/memcheck, massif (heap profiling), heaptrack
- **Cache-aware coding**: data-oriented design, SoA vs AoS, avoiding pointer chasing, prefetching
- **Branch prediction**, `[[likely]]`/`[[unlikely]]`, branchless techniques
- **SIMD** basics: auto-vectorization, intrinsics awareness (SSE/AVX at a conceptual level)
- Compiler: `-O2`/`-O3`, LTO, PGO, reading assembly on Compiler Explorer (godbolt)

### Resources
- **Talks:** Chandler Carruth "Tuning C++" & "Efficiency with Algorithms, Performance with Data Structures"; Fedor Pikus perf talks
- **Site:** Compiler Explorer (godbolt.org), quick-bench.com
- **Book:** *Systems Performance* — Brendan Gregg (methodology + tools)
- **Hands-on:** take a hot loop, profile it, make it 5× faster, write up why

---

## P6 — DS&A in C++  🔄 (repoint existing prep)

Coding rounds still happen. Keep your Grokking-patterns habit, but:
- **Code in C++**, not Java — build STL fluency (`vector`, `unordered_map`, `priority_queue`, `set`, iterators, `<algorithm>`)
- Talk **memory** out loud: copies vs moves, where a container reallocates, `reserve()`
- Add **systems-flavored** coding: LRU cache (`list` + `unordered_map`), implement a thread-safe queue, a memory pool, bit manipulation, string parsers
- Patterns to keep: sliding window, two pointers, heaps, graphs/BFS-DFS, DP, binary search, intervals

Resources: Grokking Coding Patterns (you have it), NeetCode, LeetCode tagged "C++".

---

## P7 — Low-Level System Design  ⬜ (replaces microservices)

Practice designing *components*, not service meshes. For each: API, data
structures, concurrency model, memory strategy, failure modes, complexity.

**Core catalog (drill these):**
- LRU / LFU cache (bounded, thread-safe, sharded)
- Memory allocator / slab / arena / object pool
- Thread pool with work-stealing
- Lock-free SPSC/MPSC queue
- In-memory key-value store (concurrency + eviction + persistence)
- Rate limiter internals (token bucket, sliding window log/counter)
- A logger (async, lock-free, low-latency)
- Connection pool
- A bounded blocking queue

**Keep some distributed (for infra roles):** consistent hashing, a distributed
cache, a metrics ingestion pipeline (your telemetry project!), leader election
basics, replication/consistency tradeoffs.

Resources: *Grokking System Design* (keep for the distributed half), "Low Level
Design" problem sets, and reverse-engineer real systems (Redis, memcached,
LMAX Disruptor, folly, abseil).

---

## The Flagship Project — C++ Telemetry Engine  🔄

Port `micro-thingsboard`'s proven design into modern C++. Design is already
solved, so spend 100% on systems concerns. This is your portfolio centerpiece
and neutralizes the "MFC is stale" concern by being demonstrably modern C++.

**Build order:**
1. **Edge agent in C++20** — collect OS metrics (parse `/proc`), RAII everywhere, smart pointers, `std::chrono` sampling
2. **Wire format** — reuse Protobuf (C++ codegen) or hand-roll a binary framing (great systems exercise); length-prefix framing
3. **`epoll`-based ingestion server** — non-blocking sockets, reactor pattern; then add an **`io_uring`** variant and benchmark the difference
4. **Lock-free SPSC/MPSC queue** between the network thread and worker pool (not a `BlockingQueue`)
5. **Custom memory pool / arena** for the hot path; measure allocation reduction
6. **Instrumentation** — latency percentiles (p50/p99/p999), throughput; run under ASan/TSan; profile with `perf` + flamegraph
7. **Write-up** — "Java design → C++ hot-path reimplementation," with numbers and a hard tradeoff (e.g., queue design, allocator choice)

**Tooling:** CMake, clang/gcc, gdb, sanitizers, clang-tidy, Google Benchmark,
GoogleTest. Keep it Linux-first.

Keep the frozen Java version as the "design + comparison" artifact.

---

## Company flavor matrix (tune the last mile)

Generic core gets you 80%. These are the deltas to emphasize per target:

| Company | Extra emphasis |
|---|---|
| **Sophos** | Security: endpoints, malware/sandboxing concepts, Windows internals, secure coding, low-overhead agents |
| **Microsoft** | Windows internals (in addition to Linux), Azure systems, C++ + sometimes C#, large-codebase reasoning |
| **NVIDIA** | GPU architecture, CUDA basics, parallelism, driver/runtime concerns, extreme perf, C++ templates |
| **Cloudflare** | Networking deep (TCP/HTTP/TLS/QUIC), edge/proxy internals, Rust-adjacent (worth sampling Rust), DDoS/perf at scale |
| **Google Infra** | Distributed systems + strong coding bar, abseil-style C++, scale/reliability, design rigor |
| **HFT / Bloomberg** | Ultra-low latency, lock-free, cache/NUMA, kernel bypass, deterministic C++ |

Pick **1–2 flavors** ~6 weeks before applying and layer them on top.

---

## Phased timeline (~6 months, ~14 h/week)

Overlapping, not strictly serial — language + fundamentals run in parallel.

| Phase | Weeks | Focus | Exit criteria |
|---|---|---|---|
| **0. Modern C++ resurrection** | 1–6 | P1 heavy + start P6 in C++ | Can spot UB, explain move/RAII/smart ptrs cold; *Effective Modern C++* done |
| **1. OS + memory foundations** | 4–12 | P2 + continue P1 | OSTEP core done; wrote a toy allocator; understand VM/cache/MESI |
| **2. Concurrency & lock-free** | 8–16 | P3 + P6 | Implemented SPSC/MPSC queue, TSan-clean; explain all 6 memory orders |
| **3. Systems programming + net** | 12–20 | P4 + flagship build | `epoll` + `io_uring` server working; TCP internals solid |
| **4. Performance engineering** | 16–22 | P5 + flagship perf | Profiled & 5×'d a hot path; sanitizers integrated; benchmark suite |
| **5. Design + company targeting** | 20–26 | P7 + flavor matrix + mocks | 10+ low-level designs drilled; flagship write-up done; mock-ready |

DS&A (P6), low-level design (P7), and mocks run **continuously** from week 1.

---

## Revised weekly template

```text
Monday    1.5h — DS&A patterns in C++ + STL fluency drill
Tuesday   1.5h — Rotating fundamentals: OS (P2) / Concurrency (P3) — per current phase
Wednesday 1.5h — DS&A patterns in C++
Thursday  1.5h — Modern C++ mastery (P1) — Effective Modern C++ items + godbolt
Friday    1.5h — Systems programming / networking (P4) OR Perf (P5) — per phase
Saturday  4.0h — C++ flagship (2.5h) + Mock/Review (1.5h)
Sunday    4.0h — C++ flagship (2.5h) + Mock/Review (1.5h)

Mock rotation (Sat/Sun 1.5h block), alternate weekly:
  - Low-level design mock (allocator / cache / queue / thread pool) — talk out loud
  - C++ coding mock (2 mediums in C++, narrate memory & complexity)
  - UB/code-review mock (spot the bug: data race, UAF, aliasing) — a systems staple
```

vs. the old plan: **SQL dropped**, microservices → low-level design, Java →
C++, backend project → C++ flagship, added modern-C++ and OS/perf/networking.

---

## Repo structure

```text
interview-prep-2026/
├── 01_dsa_cpp/                 # patterns, coded in C++
├── 02_low_level_design/        # allocator, LRU, thread pool, lock-free queue...
├── 03_cpp_mastery/             # Effective Modern C++ notes, UB drills, godbolt links
├── 04_os_systems/              # OSTEP notes, toy allocator, syscall experiments
├── 05_concurrency/             # memory-model notes, SPSC/MPSC implementations
├── 06_systems_programming/     # epoll/io_uring servers, socket exercises
├── 07_performance/             # perf writeups, flamegraphs, benchmarks
└── daily_log.md                # engineering changelog for your brain
```

---

## Master resource list (don't buy all at once — pull as phases hit)

**Books**
- *Effective Modern C++* — Meyers  ⭐ start here
- *C++ Concurrency in Action* — Williams  ⭐
- *Operating Systems: Three Easy Pieces* (free)  ⭐
- *Computer Systems: A Programmer's Perspective* (CS:APP)
- *The Linux Programming Interface* — Kerrisk (reference)
- *Systems Performance* — Brendan Gregg
- *TCP/IP Illustrated Vol. 1* — Stevens (reference)
- *What Every Programmer Should Know About Memory* — Drepper (free PDF)

**Sites / tools**
- cppreference.com, C++ Core Guidelines
- Compiler Explorer (godbolt.org), quick-bench.com
- Preshing on Programming (memory model)
- CppCon YouTube (Carruth, Sutter, Pikus, Iglberger)
- NeetCode / LeetCode (C++)

**Codebases to read**
- Redis, memcached (clean C systems code)
- LMAX Disruptor (lock-free design)
- folly, abseil (modern C++ at scale)
- seastar / ScyllaDB (shard-per-core, io_uring)

---

## First two weeks (concrete kickoff)

1. Rate yourself on the 7 pillars (table in §1).
2. Start *Effective Modern C++* — 3 items/session (P1).
3. Re-solve 4–5 past LeetCode mediums **in C++** to rebuild STL muscle (P6).
4. Rewrite one old MFC/C++ class in modern C++ (rule-of-0, smart ptrs, RAII); run clang-tidy + ASan.
5. Freeze `micro-thingsboard` (finish the DLQ bean), then scaffold the C++ flagship repo with CMake + GoogleTest + sanitizers wired in.
6. Skim OSTEP intro + start the virtualization (memory) section (P2).

---

*Living document — re-rate the pillars monthly, move phases as reality dictates.*
