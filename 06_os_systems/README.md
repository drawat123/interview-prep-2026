# 06 — OS & Systems Fundamentals (Pillar P2)

> See `../systems_roadmap.md` §P2.

## Track
- [ ] Process vs thread (address space, sharing, cost)
- [ ] Virtual memory: pages, page tables, TLB, faults, `mmap` vs `brk`, COW, huge pages
- [ ] Memory allocation: malloc/free internals, arenas, fragmentation
- [ ] Scheduling: preemption, context-switch cost, CFS, affinity
- [ ] Syscalls: user/kernel mode, the trap, cost, `strace`
- [ ] Signals, fork/exec/wait, zombies/orphans
- [ ] IPC: pipes, shared memory, message queues, sockets, semaphores
- [ ] File systems / I/O: buffered vs direct, page cache, `fsync`
- [ ] Caches & memory hierarchy: L1/L2/L3, cache lines, MESI, false sharing, NUMA

## Resources
- OSTEP (free), CS:APP (memory/linking/exceptions chapters)
- Drepper — *What Every Programmer Should Know About Memory*

## Hands-on
- [ ] Toy allocator
- [ ] Measure a cache miss with `perf stat`
