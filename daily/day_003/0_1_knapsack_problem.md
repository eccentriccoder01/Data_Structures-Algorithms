# 0/1 Knapsack Problem

## 1. Introduction
The 0/1 Knapsack Problem is a classic optimization problem. Given a set of items, each with a weight and a value, determine which items to include in a collection such that the total weight does not exceed a given capacity (W), and the total value is maximized. Each item can either be entirely included or excluded (0 or 1, no fractions).

## 2. When is it used?
This problem has applications in resource allocation, investment portfolio optimization, cargo loading, cutting stock problems, and selecting tasks for a project with time constraints.

## 3. ASCII Diagram

```
Items:  { (Weight: 2, Value: 3), (Weight: 3, Value: 4), (Weight: 4, Value: 5), (Weight: 5, Value: 6) }
Capacity: W = 5

DP Table (Value for W capacity with i items):
  W=0 1 2 3 4 5
i=0:  0 0 0 0 0 0
i=1:  0 0 3 3 3 3  (Item 1: W=2, V=3)
i=2:  0 0 3 4 7 7  (Item 2: W=3, V=4)
i=3:  0 0 3 4 7 8  (Item 3: W=4, V=5)
i=4:  0 0 3 4 7 9  (Item 4: W=5, V=6)

Maximum Value for W=5 is 9.
```

## 4. Approaches

### Dynamic Programming (Iterative with 2D Array)

This approach builds a 2D DP table, `dp[i][w]`, representing the maximum value that can be obtained using the first `i` items with a knapsack capacity of `w`. For each item `i` and capacity `w`, two choices are considered: either exclude the `i`-th item (value is `dp[i-1][w]`), or include the `i`-th item if its weight does not exceed `w` (value is `item[i].value + dp[i-1][w - item[i].weight]`). The maximum of these two options is stored.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int knapsack2D(int W, const std::vector<int>& weights, const std::vector<int>& values) {
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            // If current item's weight is less than or equal to current capacity
            if (weights[i-1] <= w) {
                // Option 1: Include item i
                // Value = value of item i + max value for remaining capacity (w - weights[i-1]) with previous items (i-1)
                int val_if_included = values[i-1] + dp[i-1][w - weights[i-1]];
                // Option 2: Exclude item i
                // Value = max value for current capacity (w) with previous items (i-1)
                int val_if_excluded = dp[i-1][w];
                dp[i][w] = std::max(val_if_included, val_if_excluded);
            } else {
                // Cannot include item i due to weight constraint
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    std::vector<int> values = {60, 100, 120}; // Values of items
    std::vector<int> weights = {10, 20, 30}; // Weights of items
    int W = 50; // Knapsack capacity

    std::cout << "Maximum value in Knapsack (2D DP): " << knapsack2D(W, weights, values) << std::endl; // Expected: 220

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

public class Knapsack01 {

    public int knapsack2D(int W, int[] weights, int[] values) {
        int n = weights.length;
        int[][] dp = new int[n + 1][W + 1];

        // Build table dp[][] in bottom up manner
        for (int i = 1; i <= n; i++) {
            for (int w = 1; w <= W; w++) {
                // If current item's weight is less than or equal to current capacity
                if (weights[i-1] <= w) {
                    // Option 1: Include item i
                    // Value = value of item i + max value for remaining capacity (w - weights[i-1]) with previous items (i-1)
                    int valIfIncluded = values[i-1] + dp[i-1][w - weights[i-1]];
                    // Option 2: Exclude item i
                    // Value = max value for current capacity (w) with previous items (i-1)
                    int valIfExcluded = dp[i-1][w];
                    dp[i][w] = Math.max(valIfIncluded, valIfExcluded);
                } else {
                    // Cannot include item i due to weight constraint
                    dp[i][w] = dp[i-1][w];
                }
            }
        }

        return dp[n][W];
    }

    public static void main(String[] args) {
        int[] values = {60, 100, 120}; // Values of items
        int[] weights = {10, 20, 30}; // Weights of items
        int W = 50; // Knapsack capacity

        Knapsack01 solver = new Knapsack01();
        System.out.println("Maximum value in Knapsack (2D DP): " + solver.knapsack2D(W, weights, values)); // Expected: 220
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def knapsack_2d(W, weights, values):
    n = len(weights)
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, W + 1):
            # If current item's weight is less than or equal to current capacity
            if weights[i-1] <= w:
                # Option 1: Include item i
                # Value = value of item i + max value for remaining capacity (w - weights[i-1]) with previous items (i-1)
                val_if_included = values[i-1] + dp[i-1][w - weights[i-1]]
                # Option 2: Exclude item i
                # Value = max value for current capacity (w) with previous items (i-1)
                val_if_excluded = dp[i-1][w]
                dp[i][w] = max(val_if_included, val_if_excluded)
            else:
                # Cannot include item i due to weight constraint
                dp[i][w] = dp[i-1][w]

    return dp[n][W]

if __name__ == "__main__":
    values = [60, 100, 120] # Values of items
    weights = [10, 20, 30] # Weights of items
    W = 50 # Knapsack capacity

    print(f"Maximum value in Knapsack (2D DP): {knapsack_2d(W, weights, values)}") # Expected: 220
```

</details>

---

### Dynamic Programming (Space-Optimized 1D Array)

The 2D DP table can be optimized to use only a 1D array, `dp[w]`, representing the maximum value for capacity `w` using items considered so far. When iterating through items, to avoid using the current item multiple times (which would be for unbounded knapsack), iterate the capacity `w` from `W` down to `weights[i-1]`. This ensures that when `dp[w - weights[i-1]]` is accessed, it contains the value from the previous item's row (or earlier) rather than the current item's row.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int knapsack1D(int W, const std::vector<int>& weights, const std::vector<int>& values) {
    int n = weights.size();
    std::vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; ++i) { // Iterate through items
        // Iterate capacity from W down to weights[i]
        // This ensures that dp[w - weights[i]] uses values from the previous iteration (i-1)
        for (int w = W; w >= weights[i]; --w) {
            dp[w] = std::max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }

    return dp[W];
}

int main() {
    std::vector<int> values = {60, 100, 120}; // Values of items
    std::vector<int> weights = {10, 20, 30}; // Weights of items
    int W = 50; // Knapsack capacity

    std::cout << "Maximum value in Knapsack (1D DP): " << knapsack1D(W, weights, values) << std::endl; // Expected: 220

    return 0;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

public class Knapsack01_1D {

    public int knapsack1D(int W, int[] weights, int[] values) {
        int n = weights.length;
        int[] dp = new int[W + 1];

        // dp array is initialized to 0 by default

        for (int i = 0; i < n; i++) { // Iterate through items
            // Iterate capacity from W down to weights[i]
            // This ensures that dp[w - weights[i]] uses values from the previous iteration (i-1)
            for (int w = W; w >= weights[i]; w--) {
                dp[w] = Math.max(dp[w], values[i] + dp[w - weights[i]]);
            }
        }

        return dp[W];
    }

    public static void main(String[] args) {
        int[] values = {60, 100, 120}; // Values of items
        int[] weights = {10, 20, 30}; // Weights of items
        int W = 50; // Knapsack capacity

        Knapsack01_1D solver = new Knapsack01_1D();
        System.out.println("Maximum value in Knapsack (1D DP): " + solver.knapsack1D(W, weights, values)); // Expected: 220
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def knapsack_1d(W, weights, values):
    n = len(weights)
    dp = [0] * (W + 1)

    for i in range(n): # Iterate through items
        # Iterate capacity from W down to weights[i]
        # This ensures that dp[w - weights[i]] uses values from the previous iteration (i-1)
        for w in range(W, weights[i] - 1, -1):
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]])

    return dp[W]

if __name__ == "__main__":
    values = [60, 100, 120] # Values of items
    weights = [10, 20, 30] # Weights of items
    W = 50 # Knapsack capacity

    print(f"Maximum value in Knapsack (1D DP): {knapsack_1d(W, weights, values)}") # Expected: 220
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N * W), where N is the number of items and W is the knapsack capacity. Space Complexity: O(N * W) for the 2D DP approach, and O(W) for the space-optimized 1D DP approach.
