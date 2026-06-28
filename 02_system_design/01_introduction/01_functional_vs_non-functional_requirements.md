1. Functional Requirements

Definition:
These are the requirements that define what a system is supposed to do. They describe the various functions that the system must perform.

Examples:
* A user authentication system must validate user credentials and provide access levels.
* An e-commerce website should allow users to browse products, add them to a cart, and complete purchases.

Importance in Interviews:
* Demonstrates understanding of core features
* Functional requirements often form he backbone of your system design

2. Non-Functional Requirements

Definition:
These requirements describe how the system performs a task, rather than what tasks it performs. They are related to the quality attributes of the system.

Examples:
* Scalability: The system should handle growth in users or data.
* Performance: The system should process transactions within a specified time.
* Availability: The system should be up and running a defined percentage of time.
* Security: The system must protect sensitive and resist unauthorised access.

Importance in Interviews:
* Showcases depth of design knowledge
* Highlights System Robustness and Quality

3. Integrating Both in Interviews
* When presented with a scenario, identify both the functional and non-functional requirements
* Exhibit your ability to balance both types of requirements.

4. In system Design Interviews

When you’re in a system design interview, here’s how you can handle these requirements:

* Clarify Requirements
* Prioritise requirements
* Discuss trade-off related to different architectural decisions, especially concerning non-functional requirements.
* Use real-world example
* Balance all requirements

5. Stopwatch Requirements Example

Functional Requirements (What the system should do)
* Start the stopwatch from 0.
* Pause and resume the stopwatch.
* Reset the stopwatch to 0.
* Display the current elapsed time.
* Record lap times.
* Display the list of recorded laps.

Non-Functional Requirements (How well the system should work)
* High accuracy: Measure elapsed time with minimal drift (use a monotonic clock).
* Low latency: Start, pause, resume, and lap actions should be reflected almost instantly.
* Efficiency: Avoid continuous polling or busy waiting; consume minimal CPU when idle.
* Scalability (if applicable): Support multiple independent stopwatches without creating a thread per stopwatch.
* Reliability: Elapsed time should remain correct regardless of UI refresh rate.

Quick way to remember
A simple rule of thumb:
* Functional Requirements = Features (What?)
    * Start
    * Pause
    * Resume
    * Reset
    * Lap
    * Display time
* Non-Functional Requirements = Qualities (How?)
    * Accurate
    * Fast
    * Efficient
    * Reliable
    * Scalable
This pattern works for almost every system design interview:
* Functional: What should the system do?
* Non-functional: How well should it do it?
