# Advanced Load Balancing: Senior/MTS Interview Q&A

### 1. The HTTP/2 & gRPC Multiplexing Problem
**The Context:** Older protocols like HTTP/1.1 generally open one TCP connection per request (or keep it alive for a few). "Least Connections" worked well because `1 Connection = 1 Request`.
**The Problem:** Modern protocols (HTTP/2, gRPC) use **Multiplexing**. They open *one* persistent TCP connection and stream hundreds of parallel requests through it. An LB looking only at "connection count" is completely blind to how many actual requests are flowing through that single connection.
**The MTS Solution:** 
Instead of connection-level load balancing, you must use **Request-Level Load Balancing (Layer 7)**. Tools like Envoy or modern NGINX parse the HTTP/2 frames and track active *requests/streams*, not just active TCP connections. Alternatively, you use a **Least Outstanding Requests (LOR)** algorithm instead of Least Connections.

---

### 2. The IP Hash "Thundering Herd" & State
**The Context:** IP Hashing pins a user to a specific server (Sticky Sessions). If that server stores user session data (like an in-memory shopping cart) and crashes, Consistent Hashing redistributes those users to new servers.
**The Problem:** The new servers don't have the session data. The users are logged out, they all panic-refresh or auto-reconnect, and thousands of simultaneous login queries slam the primary database, crashing the entire system (The Thundering Herd).
**The MTS Solution:**
**Stateless Architecture + Distributed Cache.** You never store session state in the local memory of a web node. 
1. The Load Balancer uses standard Round Robin or Least Connections (no sticky sessions needed).
2. The web nodes are completely **stateless**.
3. All session state is stored in an ultra-fast, distributed, in-memory cache like **Redis** or **Memcached**.
If a web node dies, the LB just routes the next request to a different node. That new node instantly fetches the user's session from Redis. The user experiences zero interruption, and the database is completely protected.

---

### 3. Layer 4 (L4) vs Layer 7 (L7) Load Balancing
**The Context:** The OSI model defines how networks communicate. L4 is the Transport Layer (TCP/UDP). L7 is the Application Layer (HTTP/HTTPS/WebSockets).
**Layer 4 (Network Load Balancer):**
* **How it works:** It only looks at IP addresses and port numbers. It does not open the packet to look at the HTTP data. It just shuffles raw packets as fast as possible.
* **Trade-off:** Blazing fast, ultra-low latency, consumes almost zero CPU. But it's "dumb"—it can't route based on URLs, cookies, or headers.
* **Use Case:** High-frequency trading, real-time multiplayer gaming, massive raw data streaming.

**Layer 7 (Application Load Balancer):**
* **How it works:** It fully terminates the connection, decrypts the TLS/SSL, reads the HTTP headers, URLs, and cookies, makes a smart routing decision, and then opens a *new* connection to the backend server.
* **Trade-off:** High CPU overhead and slightly higher latency because it has to decrypt and parse every single request. But it is "smart"—it can do URL-based routing (e.g., `/video` goes to Node A, `/text` goes to Node B) and Custom Load algorithms.
* **Use Case:** 95% of modern web architectures, microservices, API Gateways.

---

### 4. The "Post Office" Analogy (L4 vs L7)
* **Layer 4 is the sorting machine at the post office.** It only looks at the outside of the envelope (Zip Code/IP Address) and tosses it into the right bin. It never opens the envelope, making it lightning fast with near-zero overhead.
* **Layer 7 is a Corporate Executive Assistant.** They open the envelope, pull out the paper (Decrypt TLS), and read the request (HTTP Headers/URL). They see it's a request for a refund (`GET /returns`) and hand it specifically to the Returns Department. Because they have to open and read every letter, they are much smarter about routing, but much slower and use far more energy (CPU).

---

### 5. Multi-Tiered Load Balancing (Combining L4 and L7)
Massive-scale applications (Netflix, AWS, Uber) use **both** L4 and L7 in a stacked architecture.
* **Tier 1 (L4 at the Edge):** Sits facing the public internet. Its job is to handle massive throughput and act as an indestructible shield against DDoS attacks (e.g., dropping millions of fake TCP SYN floods instantly without wasting CPU cycles decrypting them).
* **Tier 2 (L7 / API Gateway):** Sits safely inside the private network behind the L4 LB. It receives legitimate TCP traffic, decrypts it, reads the URL, and routes the traffic intelligently to specific microservices.

---

### 6. How L7 Routes Traffic to Microservices
To route a request like `GET /videos` to the correct server, the L7 LB relies on one of two methods:
1. **Static Configuration (Legacy):** Hardcoding IP addresses in an `nginx.conf` file (e.g., `if path == /videos -> route to 10.0.1.5`). This breaks down in the cloud where servers constantly auto-scale and IP addresses change.
2. **Service Discovery (Modern):** Uses a Service Registry (like HashiCorp Consul, Netflix Eureka, or Kubernetes etcd). 
   - A new Video Microservice boots up and registers its IP with the Registry.
   - It sends continuous "heartbeats" to prove it is alive.
   - The L7 LB continuously syncs its memory with the Registry.
   - When `GET /videos` arrives, the LB checks its dynamic map, sees exactly which IPs are currently healthy for the Video Service, and uses a Load Balancing Algorithm (like Round Robin or Least Outstanding Requests) to pick the best IP to forward the request to.

---

### 7. Why Layer 7 is Mandatory for Microservices
Without a Layer 7 Load Balancer, a Microservice architecture is virtually impossible to manage. 
* A "dumb" L4 LB cannot read the URL. If someone asks for `/videos` or `/payments`, the L4 LB can't tell the difference and would randomly route traffic, causing `404 Not Found` errors.
* Without L7, you would be forced to use entirely different domains or ports for every single microservice (e.g., `videos.company.com` vs `payments.company.com`), requiring the frontend client to manage hundreds of connections. 
* An L7 API Gateway provides a **single entry point** (`api.company.com`), seamlessly reading the URL and hiding the complex backend microservice web from the client.
