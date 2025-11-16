# Disjoint Set Union (Union-Find)

## 1. Introduction
The Disjoint Set Union (DSU) data structure, also known as Union-Find, manages a collection of disjoint sets. It supports two primary operations: Find (determining which set an element belongs to, typically by returning a representative of that set) and Union (merging two sets into a single set). DSU is highly optimized using techniques like path compression and union by rank/size.

## 2. When is it used?
Finding connected components in a graph, Kruskal's algorithm for MST, checking for cycles in an undirected graph, solving various connectivity problems in competitive programming.

## 3. ASCII Diagram

```
Initial sets: {A}, {B}, {C}, {D}
Union(A, B): {A, B}, {C}, {D}
Union(C, D): {A, B}, {C, D}
Union(B, D): {A, B, C, D}

Representative elements for {A,B,C,D} could be A, B, C, or D.
```

## 4. Approaches

### Union-Find with Path Compression and Union by Rank/Size

The core of DSU is represented by a `parent` array where `parent[i]` stores the parent of element `i`. If `parent[i] == i`, then `i` is the representative of its set. The `Find` operation recursively traverses parent pointers until it finds the root (representative). Path compression optimizes `Find` by making all nodes encountered during the traversal point directly to the root. The `Union` operation merges two sets by linking the root of one to the root of the other. Union by rank (or size) optimizes `Union` by always attaching the smaller tree under the root of the larger tree, which keeps the tree height minimal and ensures logarithmic time complexity for operations.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <numeric>

class DSU {
public:
    std::vector<int> parent;
    std::vector<int> rank; // Or size

    DSU(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0); // Initialize ranks to 0 (or sizes to 1)
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); // Path compression
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Union by rank
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            }
            else if (rank[root_j] < rank[root_i]) {
                parent[root_j] = root_i;
            }
            else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

public class DSU {
    private int[] parent;
    private int[] rank; // Or size

    public DSU(int n) {
        parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        rank = new int[n]; // Initialize ranks to 0 (or sizes to 1)
    }

    public int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); // Path compression
    }

    public void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Union by rank
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_j] < rank[root_i]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
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
        self.rank = [0] * n # Or size

    def find(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i]) # Path compression
        return self.parent[i]

    def unite(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j);

        if root_i != root_j:
            # Union by rank
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_j] < self.rank[root_i]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1
            return True # Successfully united
        return False # Already in the same set
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: Nearly O(alpha(N)) for `Find` and `Union` operations on average, where alpha is the inverse Ackermann function, which grows extremely slowly (practically constant for all realistic N). Initializing is O(N). Space Complexity: O(N) for parent and rank arrays.
