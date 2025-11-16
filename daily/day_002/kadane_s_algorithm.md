# Kadane's Algorithm

## 1. Introduction
Kadane's Algorithm is a dynamic programming algorithm used to find the maximum sum of a contiguous subarray within a one-dimensional array of numbers. It is a very efficient and classic solution to this problem, offering a linear time complexity.

## 2. When is it used?
Finding the maximum profit from stock transactions, image processing (e.g., finding the brightest rectangle), competitive programming problems involving subarrays.

## 3. ASCII Diagram

```
Array:   [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Indices:  0   1   2  3   4  5  6   7  8

Max Subarray: [4, -1, 2, 1]
Sum: 6
```

## 4. Approaches

### Dynamic Programming Iterative Approach

The algorithm iterates through the array, maintaining two variables: `current_max` (the maximum sum of a subarray ending at the current position) and `global_max` (the overall maximum sum found so far). For each element, `current_max` is updated to be either the current element itself or the current element plus the `current_max` from the previous position. This effectively decides whether to extend the previous subarray or start a new one. `global_max` is updated whenever `current_max` exceeds it. This ensures that even if `current_max` temporarily drops due to negative numbers, `global_max` retains the highest sum seen.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

int kadanesAlgorithm(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int global_max = nums[0];
    int current_max = nums[0];

    for (size_t i = 1; i < nums.size(); ++i) {
        current_max = std::max(nums[i], current_max + nums[i]);
        global_max = std::max(global_max, current_max);
    }

    return global_max;
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
public class KadanesAlgorithm {
    public int maxSubArray(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }

        int globalMax = nums[0];
        int currentMax = nums[0];

        for (int i = 1; i < nums.length; i++) {
            currentMax = Math.max(nums[i], currentMax + nums[i]);
            globalMax = Math.max(globalMax, currentMax);
        }

        return globalMax;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def kadanes_algorithm(nums: list[int]) -> int:
    if not nums:
        return 0

    global_max = nums[0]
    current_max = nums[0]

    for i in range(1, len(nums)):
        current_max = max(nums[i], current_max + nums[i])
        global_max = max(global_max, current_max)

    return global_max
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N) where N is the number of elements in the array, as the algorithm makes a single pass through the array. Space Complexity: O(1) as only a few variables are used to store intermediate results.
