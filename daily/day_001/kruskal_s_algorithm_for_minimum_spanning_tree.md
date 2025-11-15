# Kruskal's Algorithm for Minimum Spanning Tree

## 1. Introduction
Kruskal's algorithm is a greedy algorithm that finds a Minimum Spanning Tree (MST) for a connected, undirected graph with weighted edges. An MST is a subset of the edges that connects all the vertices together, without any cycles and with the minimum possible total edge weight. The algorithm works by sorting all the edges in non-decreasing order of their weights and then iteratively adding edges to the MST if they do not form a cycle with already added edges.

## 2. When is it used?
Network design (e.g., laying down electrical cables, telecommunication lines with minimum cost), cluster analysis, image segmentation, circuit board design.

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

Edges (sorted by weight):
(A,D,1), (C,E,2), (A,B,4), (E,G,5), (B,E,7), (B,C,8), (A,E,8), (D,E,9), (E,F,10)

MST Construction:
1. Add (A,D,1). Components: {A,D}, {B}, {C}, {E}, {F}, {G}
2. Add (C,E,2). Components: {A,D}, {B}, {C,E}, {F}, {G}
3. Add (A,B,4). Components: {A,B,D}, {C,E}, {F}, {G}
4. Add (E,G,5). Components: {A,B,D}, {C,E,G}, {F}
5. Add (B,E,7). (B is in {A,B,D}, E is in {C,E,G}). Merge {A,B,D} and {C,E,G}.
   Components: {A,B,C,D,E,G}, {F}
6. Add (B,C,8). Skip (creates cycle B-E-C-B).
7. Add (A,E,8). Skip (creates cycle A-B-E-C-A or A-D-E-A).
8. Add (D,E,9). Skip (creates cycle D-A-B-E-D).
9. Add (E,F,10). Merge {A,B,C,D,E,G} and {F}.
   Components: {A,B,C,D,E,F,G} (All connected)

Final MST Edges: (A,D,1), (C,E,2), (A,B,4), (E,G,5), (B,E,7), (E,F,10)
```

## 4. Approaches

### Kruskal's with Disjoint Set Union (DSU)

This approach uses a Disjoint Set Union (DSU) data structure (also known as Union-Find) to efficiently detect cycles. The algorithm first creates a list of all edges in the graph and sorts them by weight in ascending order. Then, it iterates through the sorted edges. For each edge (u, v): if u and v are not already in the same connected component (checked using `find` operation in DSU), the edge is added to the MST, and u and v's components are merged (using `union` operation). This ensures no cycles are formed. The process continues until `V-1` edges are added to the MST, or all edges have been processed.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>
#include <numeric>

// DSU structure
struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

std::vector<Edge> kruskal(int numNodes, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end());

    DSU dsu(numNodes);
    std::vector<Edge> mst_edges;
    long long total_weight = 0;

    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst_edges.push_back(edge);
            total_weight += edge.weight;
            // Optional: if (mst_edges.size() == numNodes - 1) break;
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

class Kruskal {
    static class Edge {
        int u, v, weight;

        public Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }
    }

    static class DSU {
        int[] parent;

        DSU(int n) {
            parent = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int i) {
            if (parent[i] == i)
                return i;
            return parent[i] = find(parent[i]);
        }

        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
            }
        }
    }

    public List<Edge> kruskal(int numNodes, List<Edge> edges) {
        Collections.sort(edges, (e1, e2) -> Integer.compare(e1.weight, e2.weight));

        DSU dsu = new DSU(numNodes);
        List<Edge> mstEdges = new ArrayList<>();
        long totalWeight = 0;

        for (Edge edge : edges) {
            if (dsu.find(edge.u) != dsu.find(edge.v)) {
                dsu.unite(edge.u, edge.v);
                mstEdges.add(edge);
                totalWeight += edge.weight;
                // Optional: if (mstEdges.size() == numNodes - 1) break;
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
class DSU:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def unite(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            self.parent[root_i] = root_j
            return True
        return False

def kruskal(num_nodes, edges):
    # edges: list of tuples (u, v, weight)
    # Sort edges by weight
    edges.sort(key=lambda x: x[2])

    dsu = DSU(num_nodes)
    mst_edges = []
    total_weight = 0

    for u, v, weight in edges:
        if dsu.unite(u, v):
            mst_edges.append((u, v, weight))
            total_weight += weight
            # Optimization: if len(mst_edges) == num_nodes - 1: break
    return mst_edges
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(E log E) or O(E log V). Sorting edges takes O(E log E) time. The DSU operations (find and union) take nearly constant time on average (amortized O(alpha(V))), so E operations take O(E alpha(V)) time. Since E can be at most O(V^2), log E is roughly equivalent to log V^2 = 2 log V, making O(E log E) equivalent to O(E log V) in most graph contexts. Space Complexity: O(V + E) for storing the DSU structure and edges.
