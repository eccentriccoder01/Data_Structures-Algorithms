# Heap Sort

## 1. Introduction
Heap Sort is a comparison-based sorting algorithm that uses a binary heap data structure. It is an in-place algorithm, meaning it requires minimal additional memory. The algorithm works by first transforming the input array into a max-heap (or min-heap) and then repeatedly extracting the maximum (or minimum) element from the heap and placing it at the end of the sorted portion of the array.

## 2. When is it used?
In-place sorting where O(N log N) worst-case performance is required, priority queues (although typically not for sorting itself but as the underlying structure).

## 3. ASCII Diagram

```
Max Heap Example (Array representation):
   [10, 7, 9, 3, 5, 2, 8]

Heapified (tree conceptualization):
      10
     /  \
    7    9
   / \  / \
  3  5 2  8

Sorting process: Swap 10 with last, reduce heap size, heapify.
```

## 4. Approaches

### Standard Heap Sort Implementation

Heap sort consists of two main phases: 1. Build Max-Heap: The input array is rearranged into a max-heap. This is done by starting from the last non-leaf node (index `N/2 - 1`) and sifting down (heapifying) each node upwards to the root. 2. Sort Down: Once the array is a max-heap, the largest element (at the root, index 0) is swapped with the last element of the heap. The heap size is then reduced by one, and the new root is heapified down to restore the max-heap property. This process is repeated until the heap size is 1, at which point the array is sorted.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

// Function to heapify a subtree rooted with node 'i'
// n is size of heap
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
public class HeapSort {
    public void heapSort(int[] arr) {
        int n = arr.length;

        // Build heap (rearrange array)
        // Start from the last non-leaf node and heapify upwards
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // One by one extract an element from heap
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    // Function to heapify a subtree rooted with node 'i'
    // n is size of heap
    void heapify(int[] arr, int n, int i) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // Left child
        int right = 2 * i + 2; // Right child

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def heapify(arr, n, i):
    largest = i  # Initialize largest as root
    left = 2 * i + 1  # Left child
    right = 2 * i + 2  # Right child

    # If left child is larger than root
    if left < n and arr[left] > arr[largest]:
        largest = left

    # If right child is larger than largest so far
    if right < n and arr[right] > arr[largest]:
        largest = right

    # If largest is not root
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # Swap

        # Recursively heapify the affected sub-tree
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)

    # Build a maxheap.
    # The last non-leaf node is at index (n // 2 - 1).
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # One by one extract elements
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # Swap
        heapify(arr, i, 0)
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(N log N) in all cases (worst, average, best) because building the heap takes O(N) and each of the N extractions/heapify operations takes O(log N). Space Complexity: O(1) for in-place sorting.
