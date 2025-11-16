# Floyd-Warshall Algorithm

## 1. Introduction
The Floyd-Warshall algorithm is a dynamic programming algorithm used to find the shortest paths between all pairs of vertices in a weighted, directed graph. It can handle both positive and negative edge weights, but not negative cycles. Its core idea is to iteratively improve an estimate of the shortest path between two vertices, considering an increasing set of intermediate vertices.

## 2. When is it used?
Finding all-pairs shortest paths in a graph, detecting negative cycles, transitive closure of a graph, routing in computer networks.

## 3. ASCII Diagram

```
Graph:
   A --(3)--> B
   ^           |
   |           (1)
   (2)         v
   D <--(4)---- C

Iteration k=0: Only direct edges.
Iteration k=1 (via A): Update paths using A as intermediate.
Iteration k=2 (via B): Update paths using B as intermediate.
...
```

## 4. Approaches

### Dynamic Programming Iterative Approach

The algorithm uses a 3D array, or a 2D array by optimizing space, `dp[k][i][j]` representing the shortest path from `i` to `j` using only vertices `0, 1, ..., k-1` as intermediate vertices. The recurrence relation is `dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])`. This means the shortest path from `i` to `j` using intermediate vertices up to `k` is either the shortest path without using `k` as an intermediate, or the path from `i` to `k` and then `k` to `j` (both using intermediate vertices up to `k-1`). By iterating `k` from `0` to `N-1`, all possible intermediate vertices are considered. For negative cycle detection, if `dist[i][i]` becomes negative at any point, a negative cycle exists.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

const int INF = 1e9; // Represents infinity

void floydWarshall(int numNodes, std::vector<std::vector<int>>& dist)
{
    // Initialize dist matrix: direct edge weights or INF if no direct edge, 0 for self loops
    // Input 'dist' is assumed to be the adjacency matrix, where dist[i][j] is weight or INF.
    // Ensure dist[i][i] is 0.

    for (int k = 0; k < numNodes; ++k)
    {
        for (int i = 0; i < numNodes; ++i)
        {
            for (int j = 0; j < numNodes; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Optional: Detect negative cycles
    // for (int i = 0; i < numNodes; ++i) {
    //     if (dist[i][i] < 0) {
    //         // Graph contains a negative cycle involving node i
    //     }
    // }
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

public class FloydWarshall {
    final static int INF = 1_000_000_000; // Represents infinity

    public void floydWarshall(int numNodes, int[][] dist) {
        // Initialize dist matrix: direct edge weights or INF if no direct edge, 0 for self loops
        // Input 'dist' is assumed to be the adjacency matrix, where dist[i][j] is weight or INF.
        // Ensure dist[i][i] is 0.

        for (int k = 0; k < numNodes; k++) {
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // Optional: Detect negative cycles
        // for (int i = 0; i < numNodes; i++) {
        //     if (dist[i][i] < 0) {
        //         // Graph contains a negative cycle involving node i
        //     }
        // }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
INF = float('inf')

def floyd_warshall(num_nodes, dist):
    # Initialize dist matrix: direct edge weights or INF if no direct edge, 0 for self loops
    # Input 'dist' is assumed to be the adjacency matrix, where dist[i][j] is weight or INF.
    # Ensure dist[i][i] is 0.

    for k in range(num_nodes):
        for i in range(num_nodes):
            for j in range(num_nodes):
                if dist[i][k] != INF and dist[k][j] != INF:
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    # Optional: Detect negative cycles
    # for i in range(num_nodes):
    #     if dist[i][i] < 0:
    #         # Graph contains a negative cycle involving node i
    #         pass
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(V^3) where V is the number of vertices, due to three nested loops. Space Complexity: O(V^2) for storing the distance matrix.
