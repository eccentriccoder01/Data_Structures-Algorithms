# Depth-First Search (DFS) for Graph Traversal

## 1. Introduction
Depth-First Search (DFS) is a fundamental algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root (or an arbitrary node in a graph) and explores as far as possible along each branch before backtracking. It systematically explores all reachable nodes from a starting point.

## 2. When is it used?
DFS is employed in various scenarios, including cycle detection in graphs, topological sorting, finding connected components, pathfinding, and solving mazes. In tree structures, it forms the basis for pre-order, in-order, and post-order traversals.

## 3. ASCII Diagram

```
    A
   / \
  B   C
 /|   |\
D E   F G

DFS starting from A: A -> B -> D -> E -> C -> F -> G
```

## 4. Approaches

### Recursive Approach

The recursive approach to DFS leverages the call stack to manage visited nodes and backtracking. A function is called on a node, marks it as visited, and then recursively calls itself for all unvisited neighbors. Once a path is fully explored, the function returns, effectively backtracking.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <set>

void dfsRecursive(int u, const std::vector<std::vector<int>>& adj, std::set<int>& visited) {
    visited.insert(u);
    std::cout << u << " ";

    for (int v : adj[u]) {
        if (visited.find(v) == visited.end()) {
            dfsRecursive(v, adj, visited);
        }
    }
}

int main() {
    // Example graph representation (adjacency list)
    // 0 -- 1
    // |  / |
    // 2 -- 3
    //      |
    //      4
    int numNodes = 5;
    std::vector<std::vector<int>> adj(numNodes);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(0);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);

    std::set<int> visited;
    std::cout << "DFS Traversal (Recursive): ";
    dfsRecursive(0, adj, visited); // Start DFS from node 0
    std::cout << std::endl;

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class DFS {

    public void dfsRecursive(int u, List<List<Integer>> adj, Set<Integer> visited) {
        visited.add(u);
        System.out.print(u + " ");

        for (int v : adj.get(u)) {
            if (!visited.contains(v)) {
                dfsRecursive(v, adj, visited);
            }
        }
    }

    public static void main(String[] args) {
        // Example graph representation (adjacency list)
        // 0 -- 1
        // |  / |
        // 2 -- 3
        //      |
        //      4
        int numNodes = 5;
        List<List<Integer>> adj = new ArrayList<>(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adj.add(new ArrayList<>());
        }
        adj.get(0).add(1);
        adj.get(0).add(2);
        adj.get(1).add(0);
        adj.get(1).add(2);
        adj.get(1).add(3);
        adj.get(2).add(0);
        adj.get(2).add(1);
        adj.get(2).add(3);
        adj.get(3).add(1);
        adj.get(3).add(2);
        adj.get(3).add(4);
        adj.get(4).add(3);

        DFS graphDFS = new DFS();
        Set<Integer> visited = new HashSet<>();
        System.out.print("DFS Traversal (Recursive): ");
        graphDFS.dfsRecursive(0, adj, visited); // Start DFS from node 0
        System.out.println();
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def dfs_recursive(u, adj, visited):
    visited.add(u)
    print(u, end=" ")

    for v in adj[u]:
        if v not in visited:
            dfs_recursive(v, adj, visited)

if __name__ == "__main__":
    # Example graph representation (adjacency list)
    # 0 -- 1
    # |  / |
    # 2 -- 3
    #      |
    #      4
    num_nodes = 5
    adj = [[] for _ in range(num_nodes)]
    adj[0].extend([1, 2])
    adj[1].extend([0, 2, 3])
    adj[2].extend([0, 1, 3])
    adj[3].extend([1, 2, 4])
    adj[4].append(3)

    visited = set()
    print("DFS Traversal (Recursive): ", end="")
    dfs_recursive(0, adj, visited) # Start DFS from node 0
    print()
```

</details>

---

### Iterative Approach

The iterative approach to DFS explicitly uses a stack data structure. It pushes a starting node onto the stack, then repeatedly pops a node, processes it, and pushes its unvisited neighbors onto the stack. This mimics the behavior of the recursive call stack.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <set>

void dfsIterative(int startNode, const std::vector<std::vector<int>>& adj) {
    std::stack<int> s;
    std::set<int> visited;

    s.push(startNode);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (visited.find(u) == visited.end()) {
            visited.insert(u);
            std::cout << u << " ";

            // Push neighbors in reverse order to explore in the same order as recursive DFS
            // (or any consistent order based on problem requirements)
            for (int i = adj[u].size() - 1; i >= 0; --i) {
                int v = adj[u][i];
                if (visited.find(v) == visited.end()) {
                    s.push(v);
                }
            }
        }
    }
}

int main() {
    int numNodes = 5;
    std::vector<std::vector<int>> adj(numNodes);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(0);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);

    std::cout << "DFS Traversal (Iterative): ";
    dfsIterative(0, adj); // Start DFS from node 0
    std::cout << std::endl;

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class DFS_Iterative {

    public void dfsIterative(int startNode, List<List<Integer>> adj) {
        Stack<Integer> stack = new Stack<>();
        Set<Integer> visited = new HashSet<>();

        stack.push(startNode);

        while (!stack.isEmpty()) {
            int u = stack.pop();

            if (!visited.contains(u)) {
                visited.add(u);
                System.out.print(u + " ");

                // Push neighbors in reverse order to explore in the same order as recursive DFS
                // (or any consistent order based on problem requirements)
                for (int i = adj.get(u).size() - 1; i >= 0; --i) {
                    int v = adj.get(u).get(i);
                    if (!visited.contains(v)) {
                        stack.push(v);
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        int numNodes = 5;
        List<List<Integer>> adj = new ArrayList<>(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adj.add(new ArrayList<>());
        }
        adj.get(0).add(1);
        adj.get(0).add(2);
        adj.get(1).add(0);
        adj.get(1).add(2);
        adj.get(1).add(3);
        adj.get(2).add(0);
        adj.get(2).add(1);
        adj.get(2).add(3);
        adj.get(3).add(1);
        adj.get(3).add(2);
        adj.get(3).add(4);
        adj.get(4).add(3);

        DFS_Iterative graphDFS = new DFS_Iterative();
        System.out.print("DFS Traversal (Iterative): ");
        graphDFS.dfsIterative(0, adj); // Start DFS from node 0
        System.out.println();
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def dfs_iterative(start_node, adj):
    stack = [start_node]
    visited = set()

    while stack:
        u = stack.pop()

        if u not in visited:
            visited.add(u)
            print(u, end=" ")

            # Push neighbors in reverse order to explore in the same order as recursive DFS
            # (or any consistent order based on problem requirements)
            for v in reversed(adj[u]):
                if v not in visited:
                    stack.append(v)

if __name__ == "__main__":
    num_nodes = 5
    adj = [[] for _ in range(num_nodes)]
    adj[0].extend([1, 2])
    adj[1].extend([0, 2, 3])
    adj[2].extend([0, 1, 3])
    adj[3].extend([1, 2, 4])
    adj[4].append(3)

    print("DFS Traversal (Iterative): ", end="")
    dfs_iterative(0, adj) # Start DFS from node 0
    print()
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges. Each vertex and edge is visited at most once. Space Complexity: O(V) for the visited set and the recursion stack (or explicit stack for iterative approach).
