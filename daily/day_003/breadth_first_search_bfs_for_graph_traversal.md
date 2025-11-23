# Breadth-First Search (BFS) for Graph Traversal

## 1. Introduction
Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level. It systematically explores a graph layer by layer, starting from a given source node.

## 2. When is it used?
BFS is primarily used to find the shortest path in unweighted graphs, as it explores nodes in increasing order of distance from the source. Other applications include finding connected components, network broadcast, garbage collection (Cheney's algorithm), and social network analysis.

## 3. ASCII Diagram

```
    A
   / \
  B   C
 /|   |\
D E   F G

BFS starting from A: A -> B -> C -> D -> E -> F -> G
```

## 4. Approaches

### Queue-based Approach

BFS utilizes a queue data structure to manage the order of node visitation. It starts by adding a source node to the queue and marking it as visited. Then, it repeatedly dequeues a node, processes it, and enqueues all its unvisited neighbors, marking them as visited.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <set>

void bfs(int startNode, const std::vector<std::vector<int>>& adj) {
    std::queue<int> q;
    std::set<int> visited;

    q.push(startNode);
    visited.insert(startNode);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        std::cout << u << " ";

        for (int v : adj[u]) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                q.push(v);
            }
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

    std::cout << "BFS Traversal: ";
    bfs(0, adj); // Start BFS from node 0
    std::cout << std::endl;

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class BFS {

    public void bfs(int startNode, List<List<Integer>> adj) {
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.add(startNode);
        visited.add(startNode);

        while (!queue.isEmpty()) {
            int u = queue.poll();
            System.out.print(u + " ");

            for (int v : adj.get(u)) {
                if (!visited.contains(v)) {
                    visited.add(v);
                    queue.add(v);
                }
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

        BFS graphBFS = new BFS();
        System.out.print("BFS Traversal: ");
        graphBFS.bfs(0, adj); // Start BFS from node 0
        System.out.println();
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
from collections import deque

def bfs(start_node, adj):
    queue = deque([start_node])
    visited = {start_node}

    while queue:
        u = queue.popleft()
        print(u, end=" ")

        for v in adj[u]:
            if v not in visited:
                visited.add(v)
                queue.append(v)

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

    print("BFS Traversal: ", end="")
    bfs(0, adj) # Start BFS from node 0
    print()
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges. Each vertex and edge is processed at most once. Space Complexity: O(V) for the queue and the visited set.
