# 05 — Modern C++ Mastery (Pillar P1)

> Highest-leverage pillar: converts MFC-era C++ into hireable modern C++.
> See `../systems_roadmap.md` §P1.

## Track
- [ ] *Effective Modern C++* (Meyers) — all 42 items, ~3/session
- [ ] RAII, rule of 0/3/5
- [ ] Move semantics: rvalue refs, `std::move`, perfect forwarding, RVO/NRVO
- [ ] Smart pointers: `unique_ptr` / `shared_ptr` (control block cost) / `weak_ptr`
- [ ] Templates: SFINAE, `if constexpr`, variadics, CRTP, concepts (C++20)
- [ ] `constexpr` / `consteval`
- [ ] STL internals & complexity (vector growth, unordered_map rehash, SSO...)
- [ ] **UB drills**: spot signed overflow, strict aliasing, use-after-move, data races
- [ ] Modern features: `optional`, `variant`, `string_view`, `span`, ranges
- [ ] Error handling: exceptions vs codes vs `expected`, `noexcept`

## Contents
- `notes.md` per topic — include a **Memory/Perf note** field
- `ub_drills/` — "spot the bug" snippets + explanations
- godbolt links for anything non-obvious

Tools: cppreference, C++ Core Guidelines, Compiler Explorer, clang-tidy.
