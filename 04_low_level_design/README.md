# 04 — Low-Level System Design (Pillar P7)

> Replaces microservices/high-level-only design. Design *components*, not service meshes.
> See `../systems_roadmap.md` §P7.

For each problem, cover: **API · data structures · concurrency model · memory
strategy · failure modes · complexity.**

## Drill catalog
- [ ] LRU / LFU cache (bounded, thread-safe, sharded)
- [ ] Memory allocator / slab / arena / object pool
- [ ] Thread pool (with work-stealing)
- [ ] Lock-free SPSC / MPSC queue
- [ ] In-memory key-value store (concurrency + eviction + persistence)
- [ ] Rate limiter internals (token bucket, sliding window)
- [ ] Async low-latency logger
- [ ] Connection pool
- [ ] Bounded blocking queue

Keep some distributed here too (for infra roles): consistent hashing, distributed
cache, metrics pipeline, leader election, replication/consistency tradeoffs.

Each subfolder: `functional_spec.md` (structures + tradeoffs) and `whiteboard.png`.
