# Merge Sort Algorithm

## 1. Introduction
Merge Sort is a stable, comparison-based sorting algorithm that follows the divide and conquer paradigm. It works by recursively dividing an unsorted list into two halves until each sublist contains only one element (which is by definition sorted). Then, it repeatedly merges these sublists to produce new sorted sublists until there is only one sorted list remaining.

## 2. When is it used?
Sorting linked lists efficiently (due to O(1) memory access), external sorting (when data does not fit in memory), inversion counting problems, ensuring stability of sort order (e.g., sorting by name, then by age, preserving name order for same ages).

## 3. ASCII Diagram

```
Initial Array:
[38, 27, 43, 3, 9, 82, 10]

Divide:
[38, 27, 43, 3]  |  [9, 82, 10]
[38, 27] | [43, 3]  |  [9, 82] | [10]
[38]|[27] | [43]|[3]  |  [9]|[82] | [10]

Conquer (Merge):
[27, 38] | [3, 43]  |  [9, 82] | [10]
[3, 27, 38, 43]  |  [9, 10, 82]
[3, 9, 10, 27, 38, 43, 82]
```

## 4. Approaches

### Recursive Merge Sort (Top-Down)

The standard recursive approach for Merge Sort involves two main functions: `mergeSort` and `merge`. The `mergeSort` function recursively divides the array into two halves until individual elements are reached. Once the base case (single-element array) is met, the `merge` function is called to combine the sorted halves. The `merge` function takes two sorted sub-arrays and merges them into a single sorted array by comparing elements from both halves and placing the smaller one into a temporary array, then copying back to the original.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return; // Base case: single element or empty array
    }
    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class MergeSort {
    void merge(int[] arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[] L = new int[n1];
        int[] R = new int[n2];

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0;
        int k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSortRecursive(int[] arr, int left, int right) {
        if (left >= right) {
            return; // Base case
        }
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def merge_sort_recursive(arr, left, right):
    if left >= right:
        return # Base case

    mid = left + (right - left) // 2
    merge_sort_recursive(arr, left, mid)
    merge_sort_recursive(arr, mid + 1, right)
    _merge(arr, left, mid, right)

def _merge(arr, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid

    L = [0] * n1
    R = [0] * n2

    for i in range(n1):
        L[i] = arr[left + i]
    for j in range(n2):
        R[j] = arr[mid + 1 + j]

    i = 0
    j = 0
    k = left

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1
```

</details>

---

### Iterative Merge Sort (Bottom-Up)

The iterative (bottom-up) approach for Merge Sort starts by merging adjacent elements, then merging adjacent pairs of two elements, then adjacent pairs of four elements, and so on. The `curr_size` variable controls the size of the subarrays being merged (1, 2, 4, 8, ...), and `left_start` iterates through the array to define the starting points of these subarrays. This approach avoids recursion overhead and can be beneficial in certain environments or for very deep recursion. The `_merge` helper function remains the same as in the recursive version.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

// Helper merge function (same as recursive version)
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortIterative(std::vector<int>& arr) {
    int n = arr.size();

    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = std::min(left_start + curr_size - 1, n - 1);
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class MergeSort {
    // Helper merge function (same as recursive version)
    void merge(int[] arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[] L = new int[n1];
        int[] R = new int[n2];

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0;
        int k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSortIterative(int[] arr) {
        int n = arr.length;

        for (int currSize = 1; currSize <= n - 1; currSize = 2 * currSize) {
            for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
                int mid = Math.min(leftStart + currSize - 1, n - 1);
                int rightEnd = Math.min(leftStart + 2 * currSize - 1, n - 1);
                merge(arr, leftStart, mid, rightEnd);
            }
        }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def merge_sort_iterative(arr):
    n = len(arr)
    curr_size = 1

    while curr_size <= n - 1:
        left_start = 0
        while left_start < n - 1:
            mid = min(left_start + curr_size - 1, n - 1)
            right_end = min(left_start + 2 * curr_size - 1, n - 1)
            _merge(arr, left_start, mid, right_end)
            left_start += 2 * curr_size
        curr_size *= 2

# Helper merge function (same as recursive version)
def _merge(arr, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid

    L = [0] * n1
    R = [0] * n2

    for i in range(n1):
        L[i] = arr[left + i]
    for j in range(n2):
        R[j] = arr[mid + 1 + j]

    i = 0
    j = 0
    k = left

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N log N) in all cases (best, average, worst) due to the consistent division of the array and linear time merging. Space Complexity: O(N) auxiliary space is required for the temporary arrays used during the merge operation in both approaches.
