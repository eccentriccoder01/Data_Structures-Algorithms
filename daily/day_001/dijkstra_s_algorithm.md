# Dijkstra's Algorithm

## 1. Introduction
Dijkstra's algorithm is a single-source shortest path algorithm for graphs with non-negative edge weights. It finds the shortest paths from a single source node to all other nodes in the graph. The algorithm maintains a set of visited nodes and iteratively selects the unvisited node with the smallest known distance from the source, updates the distances of its neighbors, and adds it to the visited set.

## 2. When is it used?
Network routing protocols (e.g., OSPF), finding the shortest path in GPS navigation systems, resource allocation, shortest path in various graph-based problems where edge weights represent costs or distances and are non-negative.

## 3. ASCII Diagram

```
Graph Example:
(A)--(1)--(B)--(2)--(D)
|      / \      |
(7)  (4) (5)   (6)
|  /     \    |
(C)-------(3)----(E)

Start Node: A

Distances (Iteration 0):
A: 0
B: inf
C: inf
D: inf
E: inf

Visited: {}

Priority Queue: [(0, A)]

Processing A (dist=0):
  Visit A. Update neighbors:
  B: dist(A)+1 = 1. PQ: [(1, B)]
  C: dist(A)+7 = 7. PQ: [(1, B), (7, C)]

Visited: {A}

Processing B (dist=1):
  Visit B. Update neighbors:
  C: dist(B)+4 = 5. PQ: [(5, C), (7, C)] (updated dist for C)
  D: dist(B)+2 = 3. PQ: [(3, D), (5, C), (7, C)]

Visited: {A, B}

Processing D (dist=3):
  Visit D. Update neighbors:
  E: dist(D)+6 = 9. PQ: [(5, C), (7, C), (9, E)]

...
```

## 4. Approaches

### Dijkstra with Priority Queue (Adjacency List)

This is the most common and efficient implementation for sparse graphs. It uses an adjacency list to represent the graph and a min-priority queue to efficiently retrieve the unvisited node with the smallest current distance. The priority queue stores pairs `(distance, node)`, ordered by distance. When a node is extracted from the priority queue, it is marked as visited, and its neighbors' distances are relaxed (updated) if a shorter path is found. If a neighbor's distance is updated, it's re-added or updated in the priority queue.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <queue>
#include <limits>
#include <map>

const long long INF = std::numeric_limits<long long>::max();

// Pair of (distance, vertex)
typedef std::pair<long long, int> pii;

std::map<int, long long> dijkstra(int startNode, int numNodes, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::map<int, long long> dist;
    for (int i = 0; i < numNodes; ++i) {
        dist[i] = INF;
    }
    dist[startNode] = 0;

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If we found a shorter path to u already, skip this entry
        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

class Dijkstra {
    static class Edge {
        int target; 
        int weight;

        public Edge(int target, int weight) {
            this.target = target;
            this.weight = weight;
        }
    }

    static class Node implements Comparable<Node> {
        int vertex;
        long distance;

        public Node(int vertex, long distance) {
            this.vertex = vertex;
            this.distance = distance;
        }

        @Override
        public int compareTo(Node other) {
            return Long.compare(this.distance, other.distance);
        }
    }

    public Map<Integer, Long> dijkstra(int startNode, int numNodes, List<List<Edge>> adj) {
        Map<Integer, Long> dist = new HashMap<>();
        for (int i = 0; i < numNodes; ++i) {
            dist.put(i, Long.MAX_VALUE);
        }
        dist.put(startNode, 0L);

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node(startNode, 0));

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            int u = current.vertex;
            long d = current.distance;

            if (d > dist.get(u)) {
                continue;
            }

            for (Edge edge : adj.get(u)) {
                int v = edge.target;
                int weight = edge.weight;

                if (dist.get(u) + weight < dist.get(v)) {
                    dist.put(v, dist.get(u) + weight);
                    pq.add(new Node(v, dist.get(v)));
                }
            }
        }
        return dist;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
import heapq

def dijkstra(start_node, num_nodes, adj):
    # adj: list of lists, where adj[u] contains (v, weight) for edges from u to v
    dist = {i: float('inf') for i in range(num_nodes)}
    dist[start_node] = 0

    pq = [(0, start_node)] # (distance, vertex)

    while pq:
        d, u = heapq.heappop(pq)

        # If we found a shorter path to u already, skip this entry
        if d > dist[u]:
            continue

        for v, weight in adj[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                heapq.heappush(pq, (dist[v], v))
    return dist
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(E log V) or O(E + V log V) when using a binary heap (priority queue), where V is the number of vertices and E is the number of edges. If using a Fibonacci heap, it can be O(E + V log V). If using an array and linear scan to find minimum (for dense graphs, effectively an adjacency matrix), it's O(V^2). Space Complexity: O(V + E) for storing the graph and distances, and O(V) for the priority queue.
