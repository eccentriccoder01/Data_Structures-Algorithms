# Bellman-Ford Algorithm

## 1. Introduction
The Bellman-Ford algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted digraph. Unlike Dijkstra's, it can handle graphs with negative edge weights. It works by repeatedly relaxing all edges in the graph, attempting to improve path estimates. It can also detect negative cycles, which would imply that shortest paths are undefined for nodes reachable from such cycles.

## 2. When is it used?
Routing protocols in networks (e.g., RIP), detecting arbitrage opportunities in financial markets, any shortest path problem involving graphs with negative edge weights.

## 3. ASCII Diagram

```
Graph Example:
      (6)
(0) --[5]--> (1)
|           /\ 
|           \/
[4]        (-3)
|           /\
\/          \/
(2) --[3]--> (3)
     <--[2]--

Start Node: 0

Distances (Initial):
0: 0
1: inf
2: inf
3: inf

Iteration 1 (Relax all edges):
  Edge (0,1,5): dist[1] = min(inf, dist[0]+5) = 5
  Edge (0,2,4): dist[2] = min(inf, dist[0]+4) = 4
  Edge (1,3,-3): dist[3] = min(inf, dist[1]-3) = 2 (if dist[1]=5)
  Edge (2,1,-3): dist[1] = min(5, dist[2]-3) = 1 (if dist[2]=4)
  Edge (3,2,2): dist[2] = min(4, dist[3]+2) = 4 (if dist[3]=2)

Distances after Iteration 1:
0: 0
1: 1 (from 2)
2: 4 (from 0)
3: 2 (from 1)

... Repeat V-1 times. Then one final check for negative cycles.
```

## 4. Approaches

### Standard Relaxation with Negative Cycle Detection

The algorithm initializes all distances to infinity (except the source, which is 0). It then iterates `V-1` times (where V is the number of vertices). In each iteration, it relaxes every edge in the graph. Relaxing an edge `(u, v)` with weight `w` means checking if `dist[u] + w` is less than `dist[v]`. If it is, `dist[v]` is updated. After `V-1` iterations, all shortest paths (if no negative cycles are reachable from the source) are guaranteed to be found. A `V`-th iteration is then performed; if any distance can still be relaxed, it indicates the presence of a negative cycle reachable from the source, and shortest paths are undefined.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <limits>
#include <tuple>

const long long INF = std::numeric_limits<long long>::max();

// Edge representation: {u, v, weight}
struct Edge { 
    int u, v, weight; 
};

std::vector<long long> bellmanFord(int startNode, int numNodes, const std::vector<Edge>& edges) {
    std::vector<long long> dist(numNodes, INF);
    dist[startNode] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < numNodes - 1; ++i) {
        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative cycles
    for (const auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            // A negative cycle is detected
            // For competitive programming, you might set dist[v] to -INF or throw an exception
            // For this example, we'll return an empty vector or a special indicator.
            // A more robust solution might propagate -INF to all nodes reachable from cycle.
            std::vector<long long> result;
            result.push_back(-1); // Indicator for negative cycle
            return result;
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

class BellmanFord {
    static class Edge {
        int u, v, weight;

        Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }
    }

    public List<Long> bellmanFord(int startNode, int numNodes, List<Edge> edges) {
        List<Long> dist = new ArrayList<>(Collections.nCopies(numNodes, Long.MAX_VALUE));
        dist.set(startNode, 0L);

        // Relax all edges V-1 times
        for (int i = 0; i < numNodes - 1; ++i) {
            for (Edge edge : edges) {
                int u = edge.u;
                int v = edge.v;
                int weight = edge.weight;

                if (dist.get(u) != Long.MAX_VALUE && dist.get(u) + weight < dist.get(v)) {
                    dist.set(v, dist.get(u) + weight);
                }
            }
        }

        // Check for negative cycles
        for (Edge edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            if (dist.get(u) != Long.MAX_VALUE && dist.get(u) + weight < dist.get(v)) {
                // Negative cycle detected
                List<Long> result = new ArrayList<>();
                result.add(-1L); // Indicator for negative cycle
                return result;
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
def bellman_ford(start_node, num_nodes, edges):
    # edges: list of tuples (u, v, weight)
    dist = {i: float('inf') for i in range(num_nodes)}
    dist[start_node] = 0

    # Relax all edges V-1 times
    for _ in range(num_nodes - 1):
        for u, v, weight in edges:
            if dist[u] != float('inf') and dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight

    # Check for negative cycles
    for u, v, weight in edges:
        if dist[u] != float('inf') and dist[u] + weight < dist[v]:
            # Negative cycle detected
            return [-1] # Indicator for negative cycle
    return list(dist.values())
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(V*E), where V is the number of vertices and E is the number of edges. This is because the algorithm iterates V-1 times, and in each iteration, it processes all E edges. Space Complexity: O(V) for storing distances and O(E) for storing edges.
