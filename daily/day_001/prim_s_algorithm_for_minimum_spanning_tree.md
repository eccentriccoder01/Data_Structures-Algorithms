# Prim's Algorithm for Minimum Spanning Tree

## 1. Introduction
Prim's algorithm is a greedy algorithm that finds a Minimum Spanning Tree (MST) for a connected, undirected graph with weighted edges. It builds the MST by starting from an arbitrary initial vertex and growing the tree edge by edge. At each step, it adds the cheapest edge connecting a vertex in the tree to a vertex outside the tree.

## 2. When is it used?
Network design, laying fiber optic cables, designing circuit boards, clustering algorithms. It is particularly efficient for dense graphs.

## 3. ASCII Diagram

```
Graph Example:
  (A)--(4)--(B)--(8)--(C)
  |  \   /  |  /
 (1) (8) (7) (2)
  |   \ /   |
  (D)--(9)--(E)--(10)--(F)
       \
        (5)
         \
          (G)

Start Node: A

Distances (min_weight to tree): A:0, others:inf
Parent: A:null, others:null
Visited: { }
PQ: [(0, A)]

1. Extract (0, A). Visited: {A}
   Neighbors of A: B(4), D(1), E(8)
   Update: B:4 (parent A), D:1 (parent A), E:8 (parent A)
   PQ: [(1, D), (4, B), (8, E)]

2. Extract (1, D). Visited: {A, D}
   Neighbors of D: A(1) [skip], E(9)
   Update: E: min(8, 9) = 8 (parent A remains)
   PQ: [(4, B), (8, E)]

3. Extract (4, B). Visited: {A, D, B}
   Neighbors of B: A(4) [skip], C(8), E(7)
   Update: C:8 (parent B), E: min(8, 7) = 7 (parent B)
   PQ: [(7, E), (8, C)]

4. Extract (7, E). Visited: {A, D, B, E}
   Neighbors of E: C(2), D(9) [skip], G(5), B(7) [skip], F(10)
   Update: C: min(8, 2) = 2 (parent E), G:5 (parent E), F:10 (parent E)
   PQ: [(2, C), (5, G), (8, C_old), (10, F)] -- C_old entry is stale, will be skipped.

5. Extract (2, C). Visited: {A, D, B, E, C}
   Neighbors of C: B(8) [skip], E(2) [skip]
   PQ: [(5, G), (10, F)]

6. Extract (5, G). Visited: {A, D, B, E, C, G}
   Neighbors of G: E(5) [skip]
   PQ: [(10, F)]

7. Extract (10, F). Visited: {A, D, B, E, C, G, F}
   Neighbors of F: E(10) [skip]
   PQ: []

MST Edges: (A,D,1), (B,A,4), (E,B,7), (C,E,2), (G,E,5), (F,E,10)
```

## 4. Approaches

### Prim's with Priority Queue (Adjacency List)

This approach is generally preferred for sparse graphs and uses a min-priority queue to efficiently select the next edge. It maintains a `min_weight` array (or map) for each vertex, storing the minimum weight of an edge connecting it to the growing MST, and a `parent` array to reconstruct the MST. Initially, the source's `min_weight` is 0, and others are infinity. The priority queue stores `(weight, vertex)` pairs. When a vertex `u` is extracted from the PQ, it's added to the MST. Then, for each neighbor `v` of `u`, if `v` is not yet in the MST and `u` to `v` edge weight is less than `min_weight[v]`, `min_weight[v]` is updated, `parent[v]` is set to `u`, and `v` is added/updated in the PQ.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <queue>
#include <limits>
#include <map>

const long long INF = std::numeric_limits<long long>::max();

// Pair of (weight, vertex)
typedef std::pair<long long, int> pii;

std::vector<std::pair<int, int>> prim(int startNode, int numNodes, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::vector<long long> min_weight(numNodes, INF);
    std::vector<int> parent(numNodes, -1);
    std::vector<bool> in_mst(numNodes, false);

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

    min_weight[startNode] = 0;
    pq.push({0, startNode});

    std::vector<std::pair<int, int>> mst_edges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (in_mst[u]) {
            continue;
        }
        in_mst[u] = true;

        if (parent[u] != -1) {
            mst_edges.push_back({parent[u], u});
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!in_mst[v] && weight < min_weight[v]) {
                min_weight[v] = weight;
                parent[v] = u;
                pq.push({min_weight[v], v});
            }
        }
    }
    return mst_edges;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

class Prim {
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
        long weight;

        public Node(int vertex, long weight) {
            this.vertex = vertex;
            this.weight = weight;
        }

        @Override
        public int compareTo(Node other) {
            return Long.compare(this.weight, other.weight);
        }
    }

    public List<AbstractMap.SimpleEntry<Integer, Integer>> prim(int startNode, int numNodes, List<List<Edge>> adj) {
        long[] minWeight = new long[numNodes];
        Arrays.fill(minWeight, Long.MAX_VALUE);
        int[] parent = new int[numNodes];
        Arrays.fill(parent, -1);
        boolean[] inMST = new boolean[numNodes];

        PriorityQueue<Node> pq = new PriorityQueue<>();

        minWeight[startNode] = 0;
        pq.add(new Node(startNode, 0));

        List<AbstractMap.SimpleEntry<Integer, Integer>> mstEdges = new ArrayList<>();

        while (!pq.isEmpty()) {
            int u = pq.poll().vertex;

            if (inMST[u]) {
                continue;
            }
            inMST[u] = true;

            if (parent[u] != -1) {
                mstEdges.add(new AbstractMap.SimpleEntry<>(parent[u], u));
            }

            for (Edge edge : adj.get(u)) {
                int v = edge.target;
                int weight = edge.weight;

                if (!inMST[v] && weight < minWeight[v]) {
                    minWeight[v] = weight;
                    parent[v] = u;
                    pq.add(new Node(v, minWeight[v]));
                }
            }
        }
        return mstEdges;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
import heapq

def prim(start_node, num_nodes, adj):
    # adj: list of lists, where adj[u] contains (v, weight) for edges from u to v
    min_weight = {i: float('inf') for i in range(num_nodes)}
    parent = {i: -1 for i in range(num_nodes)}
    in_mst = {i: False for i in range(num_nodes)}

    pq = [(0, start_node)] # (weight, vertex)
    min_weight[start_node] = 0

    mst_edges = []

    while pq:
        w, u = heapq.heappop(pq)

        if in_mst[u]:
            continue
        in_mst[u] = True

        if parent[u] != -1:
            mst_edges.append((parent[u], u, min_weight[u])) # (u,v,w) form of edge

        for v, weight in adj[u]:
            if not in_mst[v] and weight < min_weight[v]:
                min_weight[v] = weight
                parent[v] = u
                heapq.heappush(pq, (min_weight[v], v))

    return mst_edges
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(E log V) or O(E + V log V) with a binary heap (priority queue), where V is the number of vertices and E is the number of edges. If using an adjacency matrix and an array to find minimums, it's O(V^2), which is better for dense graphs (E ~ V^2). Space Complexity: O(V + E) for storing the graph, `min_weight` and `parent` arrays, and the priority queue.
