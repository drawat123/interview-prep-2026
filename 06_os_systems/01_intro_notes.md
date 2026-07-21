# OSTEP Chapter 2: Introduction to Operating Systems

## 1. Virtualization of the CPU
- **The Illusion:** The OS turns a single CPU into a seemingly infinite number of virtual CPUs.
- **The Mechanism:** Time-sharing. The OS pauses one program and resumes another (context switching).
- **The Systems Reality:** A program executes instructions sequentially (Fetch-Decode-Execute). The OS interrupts this loop millions of times a second so that many programs appear to run at once.

## 2. Virtualization of Memory
- **The Illusion:** Every process believes it has a massive, private, and contiguous chunk of physical memory all to itself.
- **The Mechanism:** The OS maps virtual address spaces to actual physical memory locations under the hood. 
- **The Systems Reality:** If two programs try to access pointer `0x1000`, they are accessing their own *virtual* `0x1000`, which the OS maps to completely different *physical* RAM addresses. A process cannot affect another process's memory (isolation).

## 3. Concurrency
- **The Problem:** Modern programs run multiple threads within the same memory space. High-level instructions (like `counter++`) are **not atomic**. They translate into three separate hardware instructions:
  1. Load value from memory into a register.
  2. Increment the register.
  3. Store the value back into memory.
- **The Systems Reality:** If a context switch happens between the load and store, a race condition occurs, resulting in "strange things" (data corruption). This requires hardware and OS mechanisms (locks, atomic CPU instructions like Compare-And-Swap) to solve safely.

## 4. Persistence
- **The Problem:** System memory (DRAM) is volatile. If the machine crashes or loses power, the data vanishes.
- **The Solution:** The OS provides a filesystem to manage data persistently on non-volatile hardware (Hard Drives, SSDs), handling I/O operations seamlessly.

## 5. Key Interview Retention Notes

### Memory Isolation (The "Why")
If two processes access the identical virtual address `0x1000`, they are perfectly isolated because of the **Page Table** and the hardware **MMU (Memory Management Unit)**. The OS maintains a unique Page Table for *each* process. When a process accesses a virtual address, the MMU intercepts it, looks up that specific process's Page Table, and translates it to a completely different physical RAM frame (e.g., `0x5000` for Process A and `0x9000` for Process B).

### C++ Concurrency Without Mutexes
To safely increment a shared counter across multiple threads without a heavy OS-level mutex, use the `<atomic>` library, specifically **`std::atomic<int>`**. When compiled, this emits a special hardware instruction (like `LOCK XADD` on x86). This physically locks the CPU's cache line for that specific memory address, ensuring that the *Load-Increment-Store* cycle executes atomically in a single, uninterruptible hardware step.

---
*Notes extracted and synthesized from OSTEP Chapter 2 (Introduction).*
