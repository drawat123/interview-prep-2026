# 08 — Systems Programming (Linux/POSIX) + Networking (Pillar P4)

> See `../systems_roadmap.md` §P4.

## Systems programming
- [ ] POSIX file/process/thread APIs
- [ ] I/O multiplexing: `select` → `poll` → **`epoll`** → **`io_uring`** (why each)
- [ ] Non-blocking sockets; reactor / proactor patterns
- [ ] `mmap`, zero-copy (`sendfile`, `splice`)
- [ ] ELF, static vs dynamic linking, `LD_PRELOAD`
- [ ] `/proc`, `/sys`, rlimits, cgroups (conceptual)

## Networking
- [ ] TCP/IP model, encapsulation
- [ ] TCP internals: handshake, flow control, congestion (slow start/AIMD), Nagle, TIME_WAIT/CLOSE_WAIT, HOL blocking
- [ ] UDP and when to prefer it
- [ ] Sockets API end-to-end (redo the Java raw-TCP work in C)
- [ ] HTTP/1.1 vs 2 vs 3/QUIC (high level), TLS handshake (high level), DNS

## Resources
- Kerrisk *TLPI* (reference), Beej's Guide, Stevens *TCP/IP Illustrated Vol.1*

## Hands-on
- [ ] `epoll` echo server in C++
- [ ] `io_uring` variant + benchmark vs epoll
