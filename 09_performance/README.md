# 09 — Performance Engineering (Pillar P5)

> "Prove it's fast" — turns claims into numbers (the L5 signal).
> See `../systems_roadmap.md` §P5.

## Track
- [ ] Profiling: `perf` (stat/record/report), flamegraphs, `perf top`; VTune awareness
- [ ] Benchmarking: Google Benchmark, avoiding pitfalls (warmup, `DoNotOptimize`, variance)
- [ ] Sanitizers: ASan, TSan, UBSan, MSan — run everything under them
- [ ] Memory tooling: valgrind/memcheck, massif, heaptrack
- [ ] Cache-aware coding: data-oriented design, SoA vs AoS, avoid pointer chasing, prefetch
- [ ] Branch prediction, `[[likely]]`/`[[unlikely]]`, branchless
- [ ] SIMD basics: auto-vectorization, intrinsics awareness
- [ ] Compiler: `-O2/-O3`, LTO, PGO, reading asm on godbolt

## Resources
- Chandler Carruth "Tuning C++" & data-structures talk; Fedor Pikus perf talks
- Brendan Gregg *Systems Performance*; godbolt.org; quick-bench.com

## Contents
- `writeups/` — "profiled X, made it Ns faster, here's why" (+ flamegraphs)
