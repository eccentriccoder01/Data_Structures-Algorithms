# Lowest Common Ancestor (LCA) using Binary Lifting

## 1. Introduction
The Lowest Common Ancestor (LCA) of two nodes, P and Q, in a tree is the lowest (deepest) node that has both P and Q as descendants. It implies that the LCA is an ancestor of both P and Q, and no other node deeper than it is also an ancestor of both.

## 2. When is it used?
LCA has numerous applications in computational biology (phylogenetic trees), hierarchical data structures, file system navigation, and network routing. It is also a fundamental subroutine for calculating distances between nodes in a tree, solving range query problems, and various graph algorithms.

## 3. ASCII Diagram

```
         1 (root)
        / \
       2   3
      / \   \
     4   5   6
    /     \   \
   7       8   9

LCA(7, 8) = 2
LCA(7, 9) = 1
LCA(4, 5) = 2
```

## 4. Approaches

### Binary Lifting

Binary Lifting is an efficient technique for LCA queries, especially when many queries are expected on a static tree. It involves precomputing ancestors for each node at powers of two (2^0, 2^1, 2^2, ..., up to 2^logN). To find LCA(P, Q): First, equalize their depths by lifting the deeper node. Then, if they are not the same node, lift both P and Q simultaneously by the largest possible power of two as long as their ancestors are different, until they become siblings of the LCA. The parent of these siblings is the LCA.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_NODES = 100005;
const int LOGN = 17; // ceil(log2(MAX_NODES))
std::vector<int> adj[MAX_NODES];
int parent[MAX_NODES][LOGN]; // parent[u][k] is 2^k-th ancestor of u
int depth[MAX_NODES];

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int k = 1; k < LOGN; ++k) {
        parent[u][k] = parent[parent[u][k-1]][k-1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

int lca(int u, int v) {
    // Ensure u is deeper than or at the same depth as v
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }

    // Lift u to the same depth as v
    for (int k = LOGN - 1; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) {
            u = parent[u][k];
        }
    }

    // If u and v are now the same, that's the LCA
    if (u == v) {
        return u;
    }

    // Lift u and v simultaneously until their parents are the same
    for (int k = LOGN - 1; k >= 0; --k) {
        if (parent[u][k] != parent[v][k]) {
            u = parent[u][k];
            v = parent[v][k];
        }
    }

    // Their common parent is the LCA
    return parent[u][0];
}

int main() {
    int numNodes = 9; // Number of nodes in the example tree
    // Tree structure:
    //         1
    //        / \
    //       2   3
    //      / \   \
    //     4   5   6
    //    /     \   \
    //   7       8   9

    // Add edges for the example tree
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(5); adj[5].push_back(2);
    adj[3].push_back(6); adj[6].push_back(3);
    adj[4].push_back(7); adj[7].push_back(4);
    adj[5].push_back(8); adj[8].push_back(5);
    adj[6].push_back(9); adj[9].push_back(6);

    // Initialize parent[node][0] to 0 for root's parent to avoid issues, or handle root as special case.
    // Here, node 0 can be considered a dummy parent for root 1.
    dfs(1, 0, 0); // Start DFS from root (node 1), with parent 0 (dummy) and depth 0

    std::cout << "LCA(7, 8): " << lca(7, 8) << std::endl; // Expected: 2
    std::cout << "LCA(7, 9): " << lca(7, 9) << std::endl; // Expected: 1
    std::cout << "LCA(4, 5): " << lca(4, 5) << std::endl; // Expected: 2
    std::cout << "LCA(2, 4): " << lca(2, 4) << std::endl; // Expected: 2

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class LCA_BinaryLifting {

    private static final int MAX_NODES = 100005;
    private static final int LOGN = 17; // ceil(log2(MAX_NODES))
    private List<Integer>[] adj;
    private int[][] parent;
    private int[] depth;

    public LCA_BinaryLifting(int numNodes) {
        adj = new ArrayList[numNodes + 1];
        for (int i = 0; i <= numNodes; i++) {
            adj[i] = new ArrayList<>();
        }
        parent = new int[numNodes + 1][LOGN];
        depth = new int[numNodes + 1];
    }

    public void addEdge(int u, int v) {
        adj[u].add(v);
        adj[v].add(u);
    }

    public void dfs(int u, int p, int d) {
        depth[u] = d;
        parent[u][0] = p;
        for (int k = 1; k < LOGN; ++k) {
            parent[u][k] = parent[parent[u][k-1]][k-1];
        }
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    }

    public int lca(int u, int v) {
        // Ensure u is deeper than or at the same depth as v
        if (depth[u] < depth[v]) {
            int temp = u;
            u = v;
            v = temp;
        }

        // Lift u to the same depth as v
        for (int k = LOGN - 1; k >= 0; --k) {
            if (depth[u] - (1 << k) >= depth[v]) {
                u = parent[u][k];
            }
        }

        // If u and v are now the same, that's the LCA
        if (u == v) {
            return u;
        }

        // Lift u and v simultaneously until their parents are the same
        for (int k = LOGN - 1; k >= 0; --k) {
            if (parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }

        // Their common parent is the LCA
        return parent[u][0];
    }

    public static void main(String[] args) {
        int numNodes = 9;
        LCA_BinaryLifting lcaSolver = new LCA_BinaryLifting(numNodes);

        // Tree structure:
        //         1
        //        / \
        //       2   3
        //      / \   \
        //     4   5   6
        //    /     \   \
        //   7       8   9

        lcaSolver.addEdge(1, 2); 
        lcaSolver.addEdge(1, 3); 
        lcaSolver.addEdge(2, 4); 
        lcaSolver.addEdge(2, 5); 
        lcaSolver.addEdge(3, 6); 
        lcaSolver.addEdge(4, 7); 
        lcaSolver.addEdge(5, 8); 
        lcaSolver.addEdge(6, 9); 

        lcaSolver.dfs(1, 0, 0); // Start DFS from root (node 1), with parent 0 (dummy) and depth 0

        System.out.println("LCA(7, 8): " + lcaSolver.lca(7, 8)); // Expected: 2
        System.out.println("LCA(7, 9): " + lcaSolver.lca(7, 9)); // Expected: 1
        System.out.println("LCA(4, 5): " + lcaSolver.lca(4, 5)); // Expected: 2
        System.out.println("LCA(2, 4): " + lcaSolver.lca(2, 4)); // Expected: 2
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
import math

MAX_NODES = 100005
LOGN = 17 # ceil(math.log2(MAX_NODES))

adj = [[] for _ in range(MAX_NODES)]
parent = [[0] * LOGN for _ in range(MAX_NODES)]
depth = [0] * MAX_NODES

def dfs(u, p, d):
    depth[u] = d
    parent[u][0] = p
    for k in range(1, LOGN):
        parent[u][k] = parent[parent[u][k-1]][k-1]
    for v in adj[u]:
        if v != p:
            dfs(v, u, d + 1)

def lca(u, v):
    # Ensure u is deeper than or at the same depth as v
    if depth[u] < depth[v]:
        u, v = v, u

    # Lift u to the same depth as v
    for k in range(LOGN - 1, -1, -1):
        if depth[u] - (1 << k) >= depth[v]:
            u = parent[u][k]
    
    # If u and v are now the same, that's the LCA
    if u == v:
        return u

    # Lift u and v simultaneously until their parents are the same
    for k in range(LOGN - 1, -1, -1):
        if parent[u][k] != parent[v][k]:
            u = parent[u][k]
            v = parent[v][k]

    # Their common parent is the LCA
    return parent[u][0]

if __name__ == "__main__":
    num_nodes = 9

    # Tree structure:
    #         1
    #        / \
    #       2   3
    #      / \   \
    #     4   5   6
    #    /     \   \
    #   7       8   9

    adj[1].append(2); adj[2].append(1);
    adj[1].append(3); adj[3].append(1);
    adj[2].append(4); adj[4].append(2);
    adj[2].append(5); adj[5].append(2);
    adj[3].append(6); adj[6].append(3);
    adj[4].append(7); adj[7].append(4);
    adj[5].append(8); adj[8].append(5);
    adj[6].append(9); adj[9].append(6);

    dfs(1, 0, 0) # Start DFS from root (node 1), with parent 0 (dummy) and depth 0

    print(f"LCA(7, 8): {lca(7, 8)}") # Expected: 2
    print(f"LCA(7, 9): {lca(7, 9)}") # Expected: 1
    print(f"LCA(4, 5): {lca(4, 5)}") # Expected: 2
    print(f"LCA(2, 4): {lca(2, 4)}") # Expected: 2
```

</details>

---

## 5. Time & Space Complexity

Preprocessing: O(N log N) time and O(N log N) space, where N is the number of nodes. Each query: O(log N) time.
