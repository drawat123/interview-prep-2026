
### 1. Round Robin

1. **The Core Concept:** Distributes incoming requests sequentially across a list of servers, starting over at the beginning once it reaches the end.
2. **The "Why":** Provides a dead-simple, zero-overhead way to achieve **Horizontal Scaling** across a fleet of identical instances.
3. **How It Works:** Imagine a dealer handing out cards one by one to players around a table.
```text
Client Traffic -> [ Load Balancer ]
                    |-> (Req 1, 4) -> Node A
                    |-> (Req 2, 5) -> Node B
                    |-> (Req 3, 6) -> Node C

```


4. **Key Trade-offs:**
* **Pro:** Trivial to implement; zero state maintenance required on the load balancer.
* **Con:** **Blind to load**; if Node A gets a heavy video upload and Node B gets a simple health check, Node A can be overwhelmed.


5. **Interview Takeaway:** "Round Robin routes traffic sequentially. It’s perfect for stateless microservices running on identical hardware, but it’s a poor choice if request payloads vary wildly in computation time."

---

### 2. Least Connections

1. **The Core Concept:** Sends the next request to the server with the fewest currently active connections.
2. **The "Why":** Prevents traffic jams in high-throughput systems, ensuring **High Availability** when backend processes take varying amounts of time (e.g., mixed read/write database queries).
3. **How It Works:** Like picking the checkout lane at the grocery store with the fewest people currently standing in it.
```text
[ Load Balancer ]
   |-- Node A (5 active connections)
   |-- Node B (1 active connection)   <-- LB routes here
   |-- Node C (3 active connections)

```


4. **Key Trade-offs:**
* **Pro:** Adapts dynamically to real-time workloads; great for long-lived connections (like WebSockets or heavy gRPC streams).
* **Con:** The load balancer must maintain state (track connection counts), which adds overhead.


5. **Interview Takeaway:** "Least Connections tracks active sessions and routes to the quietest node. We use this when our backend processes requests of varying lengths, so a single node doesn't get choked by heavy transactions."

---

### 3. Weighted Round Robin

1. **The Core Concept:** Standard Round Robin, but beefier servers are given a higher "weight" (capacity multiplier) to receive more requests per cycle.
2. **The "Why":** Essential for heterogeneous environments where you mix legacy servers with newer, high-compute cloud instances.
3. **How It Works:** If Node A is twice as powerful as Node B, you give Node A a weight of 2, and Node B a weight of 1.
```text
Sequence: [Node A] -> [Node A] -> [Node B] -> (Repeat)

```


4. **Key Trade-offs:**
* **Pro:** Maximizes hardware utilization across mismatched infrastructure.
* **Con:** Still completely blind to real-time traffic spikes or temporary server degradation.


5. **Interview Takeaway:** "WRR is Round Robin scaled by server capacity. It’s a quick fix when you have mismatched hardware profiles in your cluster, but it doesn't solve sudden, localized traffic spikes."

---

### 4. Weighted Least Connections

1. **The Core Concept:** Routes based on a combination of the lowest active connections *and* the server's hardware capacity weight.
2. **The "Why":** The ultimate balancer for mixed-hardware environments running complex, variable-length tasks (e.g., a modern Java Spring cluster with varying instance sizes).
3. **How It Works:** The load balancer calculates a ratio: `(Active Connections / Weight)`. The server with the lowest score gets the request.
```text
Node A (Weight 4, Conns 8) -> Ratio: 2.0
Node B (Weight 1, Conns 1) -> Ratio: 1.0  <-- LB routes here

```


4. **Key Trade-offs:**
* **Pro:** Highly accurate, dynamic load distribution.
* **Con:** High operational complexity; requires accurate benchmarking to assign proper weights initially.


5. **Interview Takeaway:** "This combines capacity weights with real-time connection tracking. It's the go-to for complex ecosystems where nodes have different CPU profiles and handle long-lived, varied transactions."

---

### 5. IP Hash

1. **The Core Concept:** Uses a cryptographic hash of the client's IP address to map them consistently to the same backend server.
2. **The "Why":** Guarantees **Session Persistence** (sticky sessions) without needing a distributed cache like Redis for state management.
3. **How It Works:**
```text
Hash(Client IP: 192.168.1.10) = 8
8 modulo 3_Servers = Server 2
(Client ALWAYS hits Server 2)
```

4. **Key Trade-offs:**
* **Pro:** Seamless experience for stateful legacy applications (like an in-memory shopping cart).
* **Con:** Adding or removing nodes breaks the hash mapping (unless using Consistent Hashing); creates "hot spots" if many users are behind a single corporate NAT/VPN.


5. **Interview Takeaway:** "IP Hash guarantees a client always hits the same backend node. It's useful for legacy stateful apps, but in modern microservices, we prefer stateless nodes backed by a distributed cache to avoid uneven load."

---

### 6. Least Response Time

1. **The Core Concept:** Routes traffic to the server that is currently responding the fastest.
2. **The "Why":** Optimizes for lowest latency and improves **Fault Tolerance** by automatically routing around degraded or slow-failing nodes.
3. **How It Works:** The LB constantly tracks the Time To First Byte (TTFB) or full response times of its active nodes.
```text
Node A (Avg Response: 50ms)  <-- LB routes here
Node B (Avg Response: 300ms - degraded)

```


4. **Key Trade-offs:**
* **Pro:** Automatically adapts to network degradation and hardware throttling.
* **Con:** Can cause rapid oscillation (flapping) if all nodes are volatile and their response times keep jumping.


5. **Interview Takeaway:** "This routes to the node with the lowest latency. It’s critical for real-time systems like financial trading platforms, where every millisecond counts and we need to automatically bypass slow instances."

---

### 7. Random

1. **The Core Concept:** Picks a backend server entirely at random.
2. **The "Why":** A fast, near-zero-overhead way to distribute traffic when you have a massive cluster of identical, lightweight instances.
3. **How It Works:**
```text
Selected Server = rand() % pool_size
```


4. **Key Trade-offs:**
* **Pro:** Virtually zero compute overhead for the load balancer.
* **Con:** Mathematical variance means short-term load imbalances are guaranteed.


5. **Interview Takeaway:** "Random is exactly what it sounds like. We only use it for massively scaled, homogenous, stateless environments where the law of large numbers smooths out any short-term request imbalances."

---

### 8. Least Bandwidth

1. **The Core Concept:** Routes the request to the server currently consuming the lowest network bandwidth (Mbps).
2. **The "Why":** Prevents network interface card (NIC) saturation in systems serving heavy payloads (like video streaming or massive file downloads).
3. **How It Works:** The LB tracks bytes in/out rather than connection counts or CPU.
```text
Node A (Streaming 5 Gbps)
Node B (Streaming 1 Gbps) <-- LB routes here

```


4. **Key Trade-offs:**
* **Pro:** Avoids network bottlenecks which are fatal to media applications.
* **Con:** Ignores CPU/Memory limits entirely; a node might have low bandwidth but a maxed-out CPU.


5. **Interview Takeaway:** "Least bandwidth focuses entirely on network saturation. It is a niche but essential algorithm for CDNs or media streaming backends where the bottleneck is the network pipe, not the compute."

---

### 9. Custom Load

1. **The Core Concept:** A user-defined algorithm that routes traffic based on specific, combined telemetry metrics (CPU, RAM, queue depth, etc.).
2. **The "Why":** Allows fine-tuning for ultra-specific system bottlenecks that off-the-shelf algorithms can't handle, ensuring maximum **Resource Utilization**.
3. **How It Works:** An agent on the node reports custom metrics to the LB.
```text
Score = (CPU% * 0.5) + (JVM_Garbage_Collection_Time * 0.5)
Route to lowest score.

```


4. **Key Trade-offs:**
* **Pro:** Perfect alignment with specific business/application logic.
* **Con:** High operational complexity; risk of misconfiguration leading to cascading failures.


5. **Interview Takeaway:** "Custom Load lets you write your own routing rules based on telemetry like thread pool exhaustion or JVM garbage collection pauses. It's powerful but only worth the maintenance cost for highly specialized, massive-scale systems."