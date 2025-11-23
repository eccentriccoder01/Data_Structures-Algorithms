# Tarjan's Algorithm for Strongly Connected Components (SCC)

## 1. Introduction
Tarjan's algorithm is an efficient method to find the Strongly Connected Components (SCCs) in a directed graph. An SCC is a maximal subgraph such that for every pair of vertices (u, v) in the subgraph, there is a path from u to v and a path from v to u.

## 2. When is it used?
SCCs are crucial in analyzing network structures, dependency graphs (e.g., build systems, task scheduling), compiler design (call graphs), and in reducing complex graphs for further analysis by treating each SCC as a single node in a 'condensation graph'.

## 3. ASCII Diagram

```
Example Directed Graph:
1 --> 2
^   / |
|  /  v
4 <-- 3

SCCs: { {1,2,3,4} }

Another Example:
1 --> 2 --> 3
^         /
|         |
4 <-------5

SCCs: { {1}, {2}, {3}, {4,5} }
(Assuming path 3 -> 4, and 5 -> 2)
```

## 4. Approaches

### Tarjan's Algorithm (DFS-based)

Tarjan's algorithm uses a single Depth-First Search (DFS) traversal. It maintains two important values for each node `u`: `disc[u]` (discovery time, or 'low-link' value) and `low[u]` (the lowest discovery time reachable from `u` through its subtree, including back-edges). A stack is used to keep track of nodes currently in the DFS path. When `disc[u] == low[u]`, it indicates that `u` is the root of an SCC, and all nodes on the stack from `u` downwards form an SCC. These nodes are then popped from the stack and marked as part of the found SCC.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

const int MAXN = 100005;
std::vector<int> adj[MAXN];
int disc[MAXN]; // Discovery time
int low[MAXN];  // Lowest discovery time reachable from node or its subtree
bool onStack[MAXN];
std::stack<int> s;
int timer = 0;

void findSCCs(int u, int& sccCount) {
    disc[u] = low[u] = ++timer;
    s.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == 0) { // If v is not visited
            findSCCs(v, sccCount);
            low[u] = std::min(low[u], low[v]);
        } else if (onStack[v]) { // If v is visited and on stack, it's a back-edge to an ancestor in current DFS tree
            low[u] = std::min(low[u], disc[v]);
        }
    }

    // If u is the root of an SCC
    if (low[u] == disc[u]) {
        sccCount++;
        std::cout << "SCC " << sccCount << ": ";
        while (true) {
            int node = s.top();
            s.pop();
            onStack[node] = false;
            std::cout << node << " ";
            if (u == node) break;
        }
        std::cout << std::endl;
    }
}

void tarjanSCC(int numNodes) {
    // Initialize arrays
    for (int i = 0; i <= numNodes; ++i) {
        disc[i] = 0;
        low[i] = 0;
        onStack[i] = false;
    }
    timer = 0;
    int sccCount = 0;

    for (int i = 1; i <= numNodes; ++i) { // Iterate through all nodes (1-indexed)
        if (disc[i] == 0) { // If node i not visited, start DFS from it
            findSCCs(i, sccCount);
        }
    }
}

int main() {
    int numNodes = 8;
    // Example graph (from Wikipedia for SCC)
    // Nodes are 1-indexed for convenience
    adj[1].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[3].push_back(4);
    adj[4].push_back(5);
    adj[5].push_back(6);
    adj[6].push_back(4);
    adj[7].push_back(6);
    adj[7].push_back(8);
    adj[8].push_back(7);

    std::cout << "Finding SCCs using Tarjan's Algorithm:" << std::endl;
    tarjanSCC(numNodes);
    // Expected SCCs (order may vary):
    // {1, 3, 2}
    // {4, 6, 5}
    // {7, 8}

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class TarjanSCC {

    private static final int MAXN = 100005;
    private List<Integer>[] adj;
    private int[] disc; // Discovery time
    private int[] low;  // Lowest discovery time reachable from node or its subtree
    private boolean[] onStack;
    private Stack<Integer> stack;
    private int timer;
    private int sccCount;

    public TarjanSCC(int numNodes) {
        adj = new ArrayList[numNodes + 1];
        for (int i = 0; i <= numNodes; i++) {
            adj[i] = new ArrayList<>();
        }
        disc = new int[numNodes + 1];
        low = new int[numNodes + 1];
        onStack = new boolean[numNodes + 1];
        stack = new Stack<>();
        timer = 0;
        sccCount = 0;
    }

    public void addEdge(int u, int v) {
        adj[u].add(v);
    }

    private void findSCCs(int u) {
        disc[u] = low[u] = ++timer;
        stack.push(u);
        onStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == 0) { // If v is not visited
                findSCCs(v);
                low[u] = Math.min(low[u], low[v]);
            } else if (onStack[v]) { // If v is visited and on stack, it's a back-edge to an ancestor in current DFS tree
                low[u] = Math.min(low[u], disc[v]);
            }
        }

        // If u is the root of an SCC
        if (low[u] == disc[u]) {
            sccCount++;
            System.out.print("SCC " + sccCount + ": ");
            while (true) {
                int node = stack.pop();
                onStack[node] = false;
                System.out.print(node + " ");
                if (u == node) break;
            }
            System.out.println();
        }
    }

    public void tarjanSCC(int numNodes) {
        for (int i = 1; i <= numNodes; i++) { // Iterate through all nodes (1-indexed)
            if (disc[i] == 0) { // If node i not visited, start DFS from it
                findSCCs(i);
            }
        }
    }

    public static void main(String[] args) {
        int numNodes = 8;
        TarjanSCC solver = new TarjanSCC(numNodes);

        // Example graph (from Wikipedia for SCC)
        // Nodes are 1-indexed for convenience
        solver.addEdge(1, 2);
        solver.addEdge(2, 3);
        solver.addEdge(3, 1);
        solver.addEdge(3, 4);
        solver.addEdge(4, 5);
        solver.addEdge(5, 6);
        solver.addEdge(6, 4);
        solver.addEdge(7, 6);
        solver.addEdge(7, 8);
        solver.addEdge(8, 7);

        System.out.println("Finding SCCs using Tarjan's Algorithm:");
        solver.tarjanSCC(numNodes);
        // Expected SCCs (order may vary):
        // {1, 3, 2}
        // {4, 6, 5}
        // {7, 8}
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
import sys

# Increase recursion limit for deep DFS in Python
sys.setrecursionlimit(10**6)

MAXN = 100005
adj = [[] for _ in range(MAXN)]
disc = [0] * MAXN # Discovery time
low = [0] * MAXN  # Lowest discovery time reachable from node or its subtree
on_stack = [False] * MAXN
s = [] # Stack
timer = 0
scc_count = 0

def find_sccs(u):
    global timer, scc_count
    timer += 1
    disc[u] = low[u] = timer
    s.append(u)
    on_stack[u] = True

    for v in adj[u]:
        if disc[v] == 0: # If v is not visited
            find_sccs(v)
            low[u] = min(low[u], low[v])
        elif on_stack[v]: # If v is visited and on stack, it's a back-edge to an ancestor in current DFS tree
            low[u] = min(low[u], disc[v])

    # If u is the root of an SCC
    if low[u] == disc[u]:
        scc_count += 1
        print(f"SCC {scc_count}: ", end="")
        while True:
            node = s.pop()
            on_stack[node] = False
            print(node, end=" ")
            if u == node: break
        print()

def tarjan_scc(num_nodes):
    global timer, scc_count
    # Reset global variables for multiple runs or consistent state
    for i in range(1, num_nodes + 1):
        disc[i] = 0
        low[i] = 0
        on_stack[i] = False
    s.clear()
    timer = 0
    scc_count = 0

    for i in range(1, num_nodes + 1): # Iterate through all nodes (1-indexed)
        if disc[i] == 0: # If node i not visited, start DFS from it
            find_sccs(i)

if __name__ == "__main__":
    num_nodes = 8

    # Example graph (from Wikipedia for SCC)
    # Nodes are 1-indexed for convenience
    adj[1].append(2)
    adj[2].append(3)
    adj[3].append(1)
    adj[3].append(4)
    adj[4].append(5)
    adj[5].append(6)
    adj[6].append(4)
    adj[7].append(6)
    adj[7].append(8)
    adj[8].append(7)

    print("Finding SCCs using Tarjan's Algorithm:")
    tarjan_scc(num_nodes)
    # Expected SCCs (order may vary):
    # {1, 3, 2}
    # {4, 6, 5}
    # {7, 8}
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges. Each vertex and edge is visited a constant number of times during the DFS traversal. Space Complexity: O(V + E) for the adjacency list, `disc`, `low`, `onStack` arrays, and the explicit stack.
