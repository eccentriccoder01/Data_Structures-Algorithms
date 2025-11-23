# A* Search Algorithm

## 1. Introduction
A* (pronounced 'A-star') is an informed search algorithm that finds the shortest path between a start node and a goal node in a graph. It uses a heuristic function to guide its search, prioritizing paths that appear more promising. A* is optimal (guaranteed to find the shortest path) and complete (guaranteed to find a path if one exists) under certain conditions for its heuristic function.

## 2. When is it used?
A* is extensively used in pathfinding for video games, robotics for motion planning, network routing, logistics and supply chain optimization, and abstract problem-solving like the 8-puzzle or Rubik's Cube.

## 3. ASCII Diagram

```
Grid Map (S=Start, G=Goal, #=Obstacle, .=Open):

S . . .
. # # .
. . . G

A* would typically explore paths around obstacles, guided by estimated distance to G.
```

## 4. Approaches

### Priority Queue Based Search

A* operates by maintaining a set of 'open' nodes (nodes to be evaluated) in a priority queue, ordered by their `f(n)` value, which is `f(n) = g(n) + h(n)`. `g(n)` is the actual cost from the start node to node `n`, and `h(n)` is the estimated cost (heuristic) from node `n` to the goal. It also maintains a set of 'closed' nodes (nodes already evaluated). The algorithm repeatedly extracts the node with the lowest `f(n)` from the open set, moves it to the closed set, and then explores its neighbors. For each neighbor, it calculates its `g` and `f` values, updating them if a shorter path is found, and adding/updating the neighbor in the priority queue.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <limits>

// Represents a point in a 2D grid
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Custom comparator for priority queue to order by f_score (lowest first)
struct ComparePoint {
    std::map<Point, double>& f_score;
    ComparePoint(std::map<Point, double>& fs) : f_score(fs) {}
    bool operator()(const Point& a, const Point& b) {
        return f_score[a] > f_score[b];
    }
};

// Heuristic function (Manhattan distance for grid)
double heuristic(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// A* search function
void aStarSearch(
    const std::vector<std::vector<int>>& grid, 
    Point start, Point goal
) {
    int R = grid.size();
    int C = grid[0].size();

    // g_score: actual cost from start to current node
    std::map<Point, double> g_score;
    // f_score: g_score + heuristic from current node to goal
    std::map<Point, double> f_score;
    // came_from: to reconstruct path
    std::map<Point, Point> came_from;

    // Initialize scores to infinity
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            g_score[{r, c}] = std::numeric_limits<double>::infinity();
            f_score[{r, c}] = std::numeric_limits<double>::infinity();
        }
    }

    g_score[start] = 0;
    f_score[start] = heuristic(start, goal);

    std::priority_queue<Point, std::vector<Point>, ComparePoint> open_set(ComparePoint(f_score));
    open_set.push(start);

    int dr[] = {-1, 1, 0, 0}; // Up, Down
    int dc[] = {0, 0, -1, 1}; // Left, Right

    while (!open_set.empty()) {
        Point current = open_set.top();
        open_set.pop();

        if (current == goal) {
            std::cout << "Path found! Reconstructing..." << std::endl;
            std::vector<Point> path;
            Point temp = goal;
            while (!(temp == start)) {
                path.push_back(temp);
                temp = came_from[temp];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());

            for (const auto& p : path) {
                std::cout << "(" << p.x << "," << p.y << ") ";
            }
            std::cout << std::endl;
            return;
        }

        for (int i = 0; i < 4; ++i) {
            Point neighbor = {current.x + dr[i], current.y + dc[i]};

            // Check bounds and if it's an obstacle
            if (neighbor.x >= 0 && neighbor.x < R && neighbor.y >= 0 && neighbor.y < C && grid[neighbor.x][neighbor.y] == 0) {
                double tentative_g_score = g_score[current] + 1; // Cost to move to neighbor is 1

                if (tentative_g_score < g_score[neighbor]) {
                    came_from[neighbor] = current;
                    g_score[neighbor] = tentative_g_score;
                    f_score[neighbor] = g_score[neighbor] + heuristic(neighbor, goal);
                    open_set.push(neighbor); // No need to check if in open_set, priority_queue handles duplicates / better paths
                }
            }
        }
    }

    std::cout << "No path found!" << std::endl;
}

int main() {
    // 0: traversable, 1: obstacle
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    Point start = {0, 0};
    Point goal = {4, 4};

    std::cout << "A* Search on grid from (" << start.x << "," << start.y << ") to (" << goal.x << "," << goal.y << ")" << std::endl;
    aStarSearch(grid, start, goal);

    std::vector<std::vector<int>> grid2 = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    start = {0, 0};
    goal = {4, 0};
    std::cout << "\nA* Search on grid2 from (" << start.x << "," << start.y << ") to (" << goal.x << "," << goal.y << ")" << std::endl;
    aStarSearch(grid2, start, goal); // No path if goal is 4,4 and path blocked. Let's make it 4,0 for a path

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.*;

public class AStarSearch {

    // Represents a point in a 2D grid
    static class Point {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Point point = (Point) o;
            return x == point.x && y == point.y;
        }

        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }
    }

    // Heuristic function (Manhattan distance for grid)
    private static double heuristic(Point a, Point b) {
        return Math.abs(a.x - b.x) + Math.abs(a.y - b.y);
    }

    public static void aStarSearch(
        int[][] grid, 
        Point start, Point goal
    ) {
        int R = grid.length;
        int C = grid[0].length;

        // g_score: actual cost from start to current node
        Map<Point, Double> g_score = new HashMap<>();
        // f_score: g_score + heuristic from current node to goal
        Map<Point, Double> f_score = new HashMap<>();
        // came_from: to reconstruct path
        Map<Point, Point> came_from = new HashMap<>();

        // Initialize scores to infinity
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                g_score.put(new Point(r, c), Double.POSITIVE_INFINITY);
                f_score.put(new Point(r, c), Double.POSITIVE_INFINITY);
            }
        }

        g_score.put(start, 0.0);
        f_score.put(start, heuristic(start, goal));

        PriorityQueue<Point> open_set = new PriorityQueue<>(Comparator.comparingDouble(f_score::get));
        open_set.add(start);

        int[] dr = {-1, 1, 0, 0}; // Up, Down
        int[] dc = {0, 0, -1, 1}; // Left, Right

        while (!open_set.isEmpty()) {
            Point current = open_set.poll();

            if (current.equals(goal)) {
                System.out.println("Path found! Reconstructing...");
                List<Point> path = new ArrayList<>();
                Point temp = goal;
                while (!temp.equals(start)) {
                    path.add(temp);
                    temp = came_from.get(temp);
                }
                path.add(start);
                Collections.reverse(path);

                for (Point p : path) {
                    System.out.print(p + " ");
                }
                System.out.println();
                return;
            }

            for (int i = 0; i < 4; i++) {
                Point neighbor = new Point(current.x + dr[i], current.y + dc[i]);

                // Check bounds and if it's an obstacle
                if (neighbor.x >= 0 && neighbor.x < R && neighbor.y >= 0 && neighbor.y < C && grid[neighbor.x][neighbor.y] == 0) {
                    double tentative_g_score = g_score.getOrDefault(current, Double.POSITIVE_INFINITY) + 1; // Cost to move to neighbor is 1

                    if (tentative_g_score < g_score.getOrDefault(neighbor, Double.POSITIVE_INFINITY)) {
                        came_from.put(neighbor, current);
                        g_score.put(neighbor, tentative_g_score);
                        f_score.put(neighbor, g_score.get(neighbor) + heuristic(neighbor, goal));
                        // If neighbor is already in open_set, it will be handled by Java's PriorityQueue
                        // by adding a new entry with the better f_score. When we poll, the one with best f_score is taken.
                        // Alternatively, one could remove and re-add or implement a decrease-key operation.
                        open_set.add(neighbor);
                    }
                }
            }
        }

        System.out.println("No path found!");
    }

    public static void main(String[] args) {
        // 0: traversable, 1: obstacle
        int[][] grid = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        };
        Point start = new Point(0, 0);
        Point goal = new Point(4, 4);

        System.out.println("A* Search on grid from " + start + " to " + goal);
        aStarSearch(grid, start, goal);

        int[][] grid2 = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0}
        };
        start = new Point(0, 0);
        goal = new Point(4, 0);
        System.out.println("\nA* Search on grid2 from " + start + " to " + goal);
        aStarSearch(grid2, start, goal);
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
import heapq

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return isinstance(other, Point) and self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))

    def __lt__(self, other):
        # Required for heapq. This compares based on coordinates if f_score is equal
        # A better way for A* is to compare based on f_score outside the Point class
        # For this demo, f_score is managed separately, so this default comparison doesn't affect correctness if f_score is unique.
        # If f_score values can be equal, this arbitrary ordering might matter for tie-breaking, but not for correctness.
        if self.x != other.x: return self.x < other.x
        return self.y < other.y

    def __repr__(self):
        return f"({self.x},{self.y})"

# Heuristic function (Manhattan distance for grid)
def heuristic(a, b):
    return abs(a.x - b.x) + abs(a.y - b.y)

def a_star_search(grid, start, goal):
    R = len(grid)
    C = len(grid[0])

    # g_score: actual cost from start to current node
    g_score = {Point(r, c): float('inf') for r in range(R) for c in range(C)}
    # f_score: g_score + heuristic from current node to goal
    f_score = {Point(r, c): float('inf') for r in range(R) for c in range(C)}
    # came_from: to reconstruct path
    came_from = {}

    g_score[start] = 0
    f_score[start] = heuristic(start, goal)

    # Priority queue stores (f_score, point) tuples
    open_set = [(f_score[start], start)] # heapq sorts by first element

    dr = [-1, 1, 0, 0] # Up, Down
    dc = [0, 0, -1, 1] # Left, Right

    while open_set:
        current_f_score, current = heapq.heappop(open_set)

        if current == goal:
            print("Path found! Reconstructing...")
            path = []
            temp = goal
            while temp != start:
                path.append(temp)
                temp = came_from[temp]
            path.append(start)
            path.reverse()

            print(" ".join(str(p) for p in path))
            return

        for i in range(4):
            neighbor = Point(current.x + dr[i], current.y + dc[i])

            # Check bounds and if it's an obstacle
            if 0 <= neighbor.x < R and 0 <= neighbor.y < C and grid[neighbor.x][neighbor.y] == 0:
                tentative_g_score = g_score[current] + 1 # Cost to move to neighbor is 1

                if tentative_g_score < g_score.get(neighbor, float('inf')):
                    came_from[neighbor] = current
                    g_score[neighbor] = tentative_g_score
                    f_score[neighbor] = g_score[neighbor] + heuristic(neighbor, goal)
                    heapq.heappush(open_set, (f_score[neighbor], neighbor))
    
    print("No path found!")

if __name__ == "__main__":
    # 0: traversable, 1: obstacle
    grid1 = [
        [0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 1, 1, 0],
        [0, 0, 0, 0, 0]
    ]
    start1 = Point(0, 0)
    goal1 = Point(4, 4)

    print(f"A* Search on grid1 from {start1} to {goal1}")
    a_star_search(grid1, start1, goal1)

    grid2 = [
        [0, 0, 0, 0, 0],
        [0, 1, 1, 1, 0],
        [0, 1, 0, 1, 0],
        [0, 1, 1, 1, 0],
        [0, 0, 0, 0, 0]
    ]
    start2 = Point(0, 0)
    goal2 = Point(4, 0)
    print(f"\nA* Search on grid2 from {start2} to {goal2}")
    a_star_search(grid2, start2, goal2)
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: In the worst case, A* can visit all nodes in the search space, similar to Dijkstra's, resulting in O(E log V) or O(E + V log V) with a Fibonacci heap, where V is the number of vertices and E is the number of edges. For grid-based maps with non-negative edge weights and an admissible and consistent heuristic, it is often much faster, depending on the quality of the heuristic. Space Complexity: O(V) to store `g_score`, `f_score`, `came_from` maps and the priority queue.
