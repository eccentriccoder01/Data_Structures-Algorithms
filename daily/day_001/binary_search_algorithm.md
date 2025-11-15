# Binary Search Algorithm

## 1. Introduction
Binary search is an efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half. If the value of the search key is less than the item in the middle of the interval, the algorithm narrows the interval to the lower half. Otherwise, it narrows it to the upper half. This process continues until the value is found or the interval is empty.

## 2. When is it used?
Finding an element in a sorted array, finding the first or last occurrence of an element, finding the ceiling or floor of an element, solving problems that involve searching for a specific value within a monotonic function range (e.g., finding square roots, finding optimal solutions within a search space).

## 3. ASCII Diagram

```
Sorted Array:
[2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
Target = 23

Initial: [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
           L                      M                     R

Step 1: Mid (16) < Target (23). Shift L = M + 1
          [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
                                L  M           R

Step 2: Mid (38) > Target (23). Shift R = M - 1
          [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
                                L M  R

Step 3: Mid (23) == Target (23). Found!
          [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
                                M
```

## 4. Approaches

### Iterative Binary Search

The iterative approach uses a `while` loop to repeatedly adjust the `low` and `high` pointers. In each iteration, it calculates the middle index. If the element at the middle index matches the target, the index is returned. If the middle element is less than the target, the search continues in the right half (by setting `low = mid + 1`). If the middle element is greater than the target, the search continues in the left half (by setting `high = mid - 1`). The loop terminates when `low` becomes greater than `high`, indicating the element is not present.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>

int binarySearchIterative(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevent overflow

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Element not found
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class BinarySearch {
    public int binarySearchIterative(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent overflow

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1; // Element not found
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def binary_search_iterative(arr, target):
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = low + (high - low) // 2

        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1 # Element not found
```

</details>

---

### Recursive Binary Search

The recursive approach divides the problem into smaller subproblems. The base case for the recursion is when `low` > `high`, indicating the search space is exhausted. In the recursive step, it calculates the middle index. If the middle element is the target, its index is returned. Otherwise, the function calls itself recursively on either the left half (if `arr[mid] > target`) or the right half (if `arr[mid] < target`). The initial call would be `binarySearchRecursive(arr, target, 0, arr.length - 1)`.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>

int binarySearchRecursive(const std::vector<int>& arr, int target, int low, int high) {
    if (low > high) {
        return -1; // Element not found
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, high);
    } else {
        return binarySearchRecursive(arr, target, low, mid - 1);
    }
}

// Wrapper function
int binarySearchRecursiveWrapper(const std::vector<int>& arr, int target) {
    return binarySearchRecursive(arr, target, 0, arr.size() - 1);
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class BinarySearch {
    public int binarySearchRecursive(int[] arr, int target, int low, int high) {
        if (low > high) {
            return -1; // Element not found
        }

        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return binarySearchRecursive(arr, target, mid + 1, high);
        } else {
            return binarySearchRecursive(arr, target, low, mid - 1);
        }
    }

    // Wrapper function
    public int binarySearchRecursiveWrapper(int[] arr, int target) {
        return binarySearchRecursive(arr, target, 0, arr.length - 1);
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def binary_search_recursive(arr, target, low, high):
    if low > high:
        return -1  # Element not found

    mid = low + (high - low) // 2

    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_recursive(arr, target, mid + 1, high)
    else:
        return binary_search_recursive(arr, target, low, mid - 1)

# Wrapper function
def binary_search_recursive_wrapper(arr, target):
    return binary_search_recursive(arr, target, 0, len(arr) - 1)
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(log N) for both iterative and recursive approaches. This is because the search space is halved in each step. Space Complexity: O(1) for iterative approach, O(log N) for recursive approach due to recursion stack space.
