### 1. The Core Concept

A load balancer (LB) is essentially a traffic director that sits in front of your infrastructure, distributing incoming client requests across a cluster of healthy backend servers so no single machine gets overwhelmed.

### 2. The "Why"

In modern production environments, you can't rely on one massive machine to handle all traffic. Load balancers enable **Horizontal Scaling** (adding more servers rather than bigger ones). They ensure **High Availability** by acting as a shield; if a backend microservice crashes, the LB stops sending it traffic, preventing a backend outage from becoming a system-wide **Single Point of Failure (SPOF)**.

### 3. How It Works

1. A client sends a request intended for your application.
2. The LB intercepts the request and evaluates the current pool of backend servers.
3. Using a specific algorithm (like Round Robin or Least Connections), it forwards the request to the most appropriate, healthy server.
4. The LB continuously performs "health checks" on the backend nodes. If a node fails, it is temporarily removed from the routing pool until it recovers.
5. *Note:* LBs aren't just for external traffic. In a microservices architecture, you place them between layers (e.g., Web Layer $\rightarrow$ LB $\rightarrow$ App Layer $\rightarrow$ LB $\rightarrow$ Database).

```text
       [Clients / Upstream Service]
                   |
                   v
         +-------------------+
         |   Load Balancer   | <======> [Redundant Standby LB]
         +-------------------+          (Prevents LB from being a SPOF)
             |      |      |
       +-----+      |      +-----+
       v            v            v
  [Server A]   [Server B]   [Server C]  
  (Healthy)    (Healthy)    (DEAD - Ignored by LB)

```

### 4. Key Trade-offs

* **Capacity vs. Complexity:** Massively increases your system's throughput and responsiveness, but introduces an extra network hop and more infrastructure to manage.
* **Resilience vs. SPOF Risk:** While it masks backend failures, the LB itself becomes a strict **Single Point of Failure**. You *must* run redundant LBs (usually in an Active-Passive or Active-Active cluster) to mitigate this.
* **Cost vs. Uptime:** Maintaining load balancers and running duplicated backend nodes increases your cloud bill, but it is the required cost of doing business for true **Fault Tolerance**.

### 5. Interview Takeaway

"A load balancer is a critical networking component that distributes incoming traffic across a pool of backend servers. We use it to achieve **Horizontal Scaling** and **Fault Tolerance**. Because it continuously health-checks our microservices, it can instantly route traffic away from dead nodes, ensuring **High Availability**. To guarantee the load balancer itself doesn't become a **Single Point of Failure**, we always deploy them in redundant clusters."