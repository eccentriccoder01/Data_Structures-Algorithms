# Topological Sort

## 1. Introduction
Topological sort is an algorithm for ordering the nodes of a directed acyclic graph (DAG) such that for every directed edge from node A to node B, node A comes before node B in the ordering. This ordering is not unique for a given DAG.

## 2. When is it used?
Task scheduling, course prerequisite resolution, compilation dependency resolution, data serialization.

## 3. ASCII Diagram

```
   A --> B --> C
   |     ^
   v     |
   D -----

   Example topological order: A, D, B, C
```

## 4. Approaches

### Kahn's Algorithm (BFS-based)

Kahn's algorithm uses a Breadth-First Search (BFS) approach. It starts by finding all nodes with an in-degree of zero and adds them to a queue. It then dequeues a node, adds it to the topological order, and decrements the in-degree of all its neighbors. If a neighbor's in-degree becomes zero, it is added to the queue. This process continues until the queue is empty. If the number of nodes in the topological order is less than the total number of nodes in the graph, the graph contains a cycle.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>

std::vector<int> topologicalSortKahn(int numNodes, const std::vector<std::vector<int>>& adj)
{
    std::vector<int> inDegree(numNodes, 0);
    for (int u = 0; u < numNodes; ++u)
    {
        for (int v : adj[u])
        {
            inDegree[v]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < numNodes; ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    std::vector<int> result;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : adj[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (result.size() != numNodes)
    {
        // Graph contains a cycle, topological sort not possible
        return {}; 
    }
    return result;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class TopologicalSort {
    public List<Integer> topologicalSortKahn(int numNodes, List<List<Integer>> adj) {
        int[] inDegree = new int[numNodes];
        for (int u = 0; u < numNodes; u++) {
            for (int v : adj.get(u)) {
                inDegree[v]++;
            }
        }

        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < numNodes; i++) {
            if (inDegree[i] == 0) {
                q.add(i);
            }
        }

        List<Integer> result = new ArrayList<>();
        while (!q.isEmpty()) {
            int u = q.poll();
            result.add(u);

            for (int v : adj.get(u)) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.add(v);
                }
            }
        }

        if (result.size() != numNodes) {
            // Graph contains a cycle, topological sort not possible
            return Collections.emptyList();
        }
        return result;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
from collections import deque

def topological_sort_kahn(num_nodes, adj):
    in_degree = [0] * num_nodes
    for u in range(num_nodes):
        for v in adj[u]:
            in_degree[v] += 1

    q = deque()
    for i in range(num_nodes):
        if in_degree[i] == 0:
            q.append(i)

    result = []
    while q:
        u = q.popleft()
        result.append(u)

        for v in adj[u]:
            in_degree[v] -= 1
            if in_degree[v] == 0:
                q.append(v)

    if len(result) != num_nodes:
        # Graph contains a cycle, topological sort not possible
        return []
    return result
```

</details>

---

### DFS-based Algorithm

The DFS-based topological sort uses a Depth-First Search. It explores each node and its descendants fully before adding the node to the topological order. When a DFS call returns from a node, it means all its dependent nodes have been visited. Thus, the node is added to the front of the result list (or pushed onto a stack and then reversed). This naturally places nodes with no outgoing edges first and ensures that a node is added only after all its descendants. Cycle detection can be done by tracking nodes in the current recursion stack.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void dfsTopologicalSort(int u, const std::vector<std::vector<int>>& adj,
                        std::vector<bool>& visited, std::vector<int>& result)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfsTopologicalSort(v, adj, visited, result);
        }
    }
    result.push_back(u);
}

std::vector<int> topologicalSortDFS(int numNodes, const std::vector<std::vector<int>>& adj)
{
    std::vector<bool> visited(numNodes, false);
    std::vector<int> result;

    for (int i = 0; i < numNodes; ++i)
    {
        if (!visited[i])
        {
            dfsTopologicalSort(i, adj, visited, result);
        }
    }
    std::reverse(result.begin(), result.end());
    // Note: Cycle detection needs additional state (recursion stack tracking) which is omitted for brevity.
    // A common way is to use three states: unvisited, visiting, visited.
    return result;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class TopologicalSortDFS {
    private void dfs(int u, List<List<Integer>> adj, boolean[] visited, Deque<Integer> stack) {
        visited[u] = true;
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                dfs(v, adj, visited, stack);
            }
        }
        stack.push(u);
    }

    public List<Integer> topologicalSortDFS(int numNodes, List<List<Integer>> adj) {
        boolean[] visited = new boolean[numNodes];
        Deque<Integer> stack = new ArrayDeque<>(); // Using Deque as a stack

        for (int i = 0; i < numNodes; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, stack);
            }
        }

        List<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            result.add(stack.pop());
        }
        // Note: Cycle detection needs additional state (recursion stack tracking) which is omitted for brevity.
        return result;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def _dfs(u, adj, visited, recursion_stack, result):
    visited[u] = True
    recursion_stack[u] = True

    for v in adj[u]:
        if not visited[v]:
            if not _dfs(v, adj, visited, recursion_stack, result):
                return False # Cycle detected
        elif recursion_stack[v]:
            return False # Cycle detected

    recursion_stack[u] = False
    result.append(u)
    return True

def topological_sort_dfs(num_nodes, adj):
    visited = [False] * num_nodes
    recursion_stack = [False] * num_nodes
    result = []

    for i in range(num_nodes):
        if not visited[i]:
            if not _dfs(i, adj, visited, recursion_stack, result):
                return [] # Cycle detected

    return result[::-1] # Reverse the result to get correct order
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(V + E) where V is the number of vertices and E is the number of edges, as each vertex and edge are visited once. Space Complexity: O(V + E) for adjacency list and O(V) for in-degree array/recursion stack.
