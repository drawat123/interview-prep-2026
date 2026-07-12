# 07 — Concurrency & Lock-Free (Pillar P3)

> The senior systems differentiator. See `../systems_roadmap.md` §P3.

## Track
- [ ] Threads, `jthread`, lifecycle
- [ ] `mutex`, `shared_mutex`, `condition_variable`, wait-predicate idiom
- [ ] `std::atomic` + memory model: relaxed / acquire / release / acq_rel / seq_cst (a real use for each)
- [ ] Lock-free: SPSC/MPSC ring buffer, Treiber stack, Michael-Scott queue
- [ ] ABA problem + defenses (tagged ptrs, hazard pointers, epoch/RCU)
- [ ] False sharing, `alignas(64)`
- [ ] Thread pools, work-stealing
- [ ] Deadlock / livelock / priority inversion, lock ordering
- [ ] `async`, futures, latch/barrier/semaphore (C++20)
- [ ] Cost model: atomic vs cache-line bounce

## Resources
- *C++ Concurrency in Action* (Williams)
- Herb Sutter "atomic<> Weapons"; Fedor Pikus lock-free talks; Preshing blog

## Hands-on
- [ ] SPSC lock-free ring buffer — **TSan-clean**
