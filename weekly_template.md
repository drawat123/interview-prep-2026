### **The Uniform Weekly Template**

* **Monday:** 1.5h — Grokking the Coding Interview: Patterns for Coding Questions
* **Tuesday:** 1.5h — High-Level System Design (*Grokking the System Design Interview* Volume I or II)
* **Wednesday:** 1.5h — Grokking the Coding Interview: Patterns for Coding Questions
* **Thursday:** 1.5h — Specialized System Design (*Grokking Microservices Design Patterns*)
* **Friday:** 1.5h — DataLemur SQL
* **Saturday:** 4.0h — Micro-Thingsboard Side Project (2.5h) + Mock/Review (1.5h)
* **Sunday:** 4.0h — Micro-Thingsboard Side Project (2.5h) + Mock/Review (1.5h)

---

### **Option 1: The System Design Mock (90 Minutes)**

For Senior and MTS loops, your ability to communicate trade-offs is graded just as heavily as your actual architecture. You cannot practice this silently.

* **Minute 0–45 (The Performance):** * Pick a case study you read earlier in the week (e.g., "Design a Rate Limiter" or "Design a URL Shortener").
* Close all books and browser tabs. Open a blank digital whiteboard (like Excalidraw) or stand at a physical whiteboard.
* Set a timer for 45 minutes.
* **Talk out loud** to an imaginary interviewer. Walk through the 5 steps: Requirements, Estimations, API Design, High-Level Architecture, and Deep Dive. If you get stuck on how to partition the database, force yourself to make a decision and justify it out loud.


* **Minute 45–90 (The Tear-Down):** * Stop the timer. Open the DesignGurus playbook.
* Compare your drawing to their solution. Did you forget a cache? Did you put a load balancer in the wrong place?
* Write down your exact blind spots so you know what to review on Tuesday.

### **Option 2: The DSA / SQL Coding Mock (90 Minutes)**

You need to practice writing bug-free code without the crutch of IDE auto-complete or syntax highlighting.

* **Minute 0–60 (The Execution):**
* Pick 2 "Medium" algorithmic pattern questions you haven't seen before, or 2 "Hard" DataLemur SQL questions.
* Open a raw text editor or a platform like LeetCode/DataLemur, but **hide the run button**.
* Set a timer. For algorithms, talk out loud while you type, explaining your space/time complexity as you go. For SQL, explain your `JOIN` and `GROUP BY` logic before you type it.
* You must finish writing the code before the timer hits zero.


* **Minute 60–90 (The Debugging):**
* Now, run your code.
* If it fails, do not look at the solution immediately. Spend 15 minutes trying to trace the stack or print variables to find the bug yourself.
* Review the optimal solution and figure out if you used an unnecessary `O(N)` memory allocation or a less efficient table join.

### **The Golden Rules of the Mock Block**

1. **Never pause the timer.** If you freeze up in a real interview, the clock keeps ticking. Learn to manage the panic.
2. **Talk to the wall.** The physical act of speaking your technical thoughts clearly is a separate muscle from writing code. Train it.
3. **No looking up syntax.** If you forget the exact Java Spring annotation or C++ STL method, write a placeholder comment (e.g., `// assume helper function returns X`) and keep moving.

---

### The GitHub Code Repository Strategy

```text
interview-prep-2026/
│
├── 01_dsa_patterns/
│   ├── 01_sliding_window/
│   │   ├── max_subarray_sum.cpp (or .java)
│   │   └── notes.md (Write down tricky edge cases or failures here)
│   └── 02_two_pointers/
│
├── 02_system_design/
│   ├── 01_url_shortener/
│   │   ├── functional_spec.md (Your scale math, API designs, schema)
│   │   └── whiteboard.png (Screenshot of your Saturday mock drawings)
│   └── 02_rate_limiter/
│
└── 03_datalemur_sql/
    ├── week_1_intermediates.sql
    └── window_functions_practice.sql

```

---

### 1. The Micro Template: notes.md

### [Topic / Pattern Name]

### The Core Concept
* **The Trick:** [Explain the main intuition in 1-2 sentences. e.g., "Use a sliding window because the array is contiguous and we need a sub-range."]
* **Data Structure Used:** [e.g., Deque, Min-Heap, HashSet]

### Complexity
* **Time:** `O(?)` - [Brief reason why]
* **Space:** `O(?)` - [Brief reason why]

### The Code Skeleton (Java)
```java
// Paste ONLY the crucial logic here, not the whole class boilerplate.
// Highlight the specific lines you struggled to remember.
```

### 2. The Macro Template: `daily_log.md`
This file lives at the root of `interview-prep-2026`. Do not write long paragraphs here. This is an engineering changelog for your brain. Treat it like a commit history. 

Paste this at the top of the file, and just append a new entry block to the bottom every day.

```markdown
# 🚀 2026 Interview Prep Master Log

### [YYYY-MM-DD] - [Day of Week]
**Focus:** [e.g., DSA: Sliding Window | System Design: URL Shortener]
**Hours Logged:** [e.g., 1.5h]

* **The Bug / Blindspot:** * [Be specific. e.g., "I forgot that resizing a Java HashMap takes O(N) time and didn't mention it to the imaginary interviewer."]
* **The Fix:** * [The actionable correction. e.g., "Always state the load factor trade-off when bringing up HashMaps in system design mocks."]

```

---