# Quick Sort Algorithm

## 1. Introduction
Quick Sort is an efficient, in-place, comparison-based sorting algorithm that also follows the divide and conquer paradigm. It picks an element as a pivot and partitions the array around the chosen pivot. All elements smaller than the pivot are moved to its left, and all greater elements to its right. The sub-arrays are then recursively sorted.

## 2. When is it used?
General-purpose sorting, efficient for large datasets due to its average-case performance, typically faster than Merge Sort and Heap Sort in practice for arrays due to better cache performance and lower constant factors.

## 3. ASCII Diagram

```
Initial Array:
[10, 80, 30, 90, 40, 50, 70]
Pivot = 70 (last element)

Partition (Lomuto, i=-1, j=0 to N-2):
[10, 80, 30, 90, 40, 50, 70]
 i=-1                   p=70
  j=0: 10 < 70 => i=0, swap(arr[0], arr[0]) -> [10, 80, 30, 90, 40, 50, 70]
  j=1: 80 > 70 => no swap
  j=2: 30 < 70 => i=1, swap(arr[1], arr[2]) -> [10, 30, 80, 90, 40, 50, 70]
  j=3: 90 > 70 => no swap
  j=4: 40 < 70 => i=2, swap(arr[2], arr[4]) -> [10, 30, 40, 90, 80, 50, 70]
  j=5: 50 < 70 => i=3, swap(arr[3], arr[5]) -> [10, 30, 40, 50, 80, 90, 70]

After loop, swap(arr[i+1], arr[high]):
[10, 30, 40, 50, 70, 90, 80]
                  ^ (Pivot in place at index 4)

Recursively sort left and right sub-arrays:
[10, 30, 40, 50]  |  [90, 80]
```

## 4. Approaches

### Lomuto Partition Scheme

In the Lomuto partition scheme, a pivot element (typically the last element of the array segment) is chosen. The algorithm then iterates through the array from the beginning up to (but not including) the pivot. It maintains a pointer `i` which tracks the boundary of elements smaller than or equal to the pivot. If an element `arr[j]` is found to be less than or equal to the pivot, `i` is incremented, and `arr[i]` is swapped with `arr[j]`. Finally, the pivot element (`arr[high]`) is swapped with `arr[i+1]`, placing the pivot in its correct sorted position. This returns the index of the pivot.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

int lomutoPartition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortLomuto(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = lomutoPartition(arr, low, high);
        quickSortLomuto(arr, low, pi - 1);
        quickSortLomuto(arr, pi + 1, high);
    }
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class QuickSort {
    int lomutoPartition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }

    void quickSortLomuto(int[] arr, int low, int high) {
        if (low < high) {
            int pi = lomutoPartition(arr, low, high);
            quickSortLomuto(arr, low, pi - 1);
            quickSortLomuto(arr, pi + 1, high);
        }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def lomuto_partition(arr, low, high):
    pivot = arr[high] # Choose last element as pivot
    i = (low - 1) # Index of smaller element

    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return (i + 1)

def quick_sort_lomuto(arr, low, high):
    if low < high:
        pi = lomuto_partition(arr, low, high)
        quick_sort_lomuto(arr, low, pi - 1)
        quick_sort_lomuto(arr, pi + 1, high)
```

</details>

---

### Hoare Partition Scheme

The Hoare partition scheme, generally more efficient than Lomuto, works by choosing a pivot (e.g., the first element). It uses two pointers, `i` and `j`, starting from `low - 1` and `high + 1` respectively. `i` moves right, `j` moves left. `i` stops at an element greater than or equal to the pivot, `j` stops at an element less than or equal to the pivot. If `i` and `j` haven't crossed, `arr[i]` and `arr[j]` are swapped. Once they cross, `j` is returned as the partition index. This scheme partitions the array such that elements to the left of `j` are smaller than or equal to the pivot, and elements to the right of `j` are greater than or equal to the pivot.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

int hoarePartition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Choose first element as pivot
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}

void quickSortHoare(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class QuickSort {
    int hoarePartition(int[] arr, int low, int high) {
        int pivot = arr[low];
        int i = low - 1;
        int j = high + 1;

        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);

            do {
                j--;
            } while (arr[j] > pivot);

            if (i >= j) {
                return j;
            }
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    void quickSortHoare(int[] arr, int low, int high) {
        if (low < high) {
            int pi = hoarePartition(arr, low, high);
            quickSortHoare(arr, low, pi);
            quickSortHoare(arr, pi + 1, high);
        }
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
def hoare_partition(arr, low, high):
    pivot = arr[low] # Choose first element as pivot
    i = low - 1
    j = high + 1

    while True:
        i += 1
        while arr[i] < pivot:
            i += 1

        j -= 1
        while arr[j] > pivot:
            j -= 1

        if i >= j:
            return j

        arr[i], arr[j] = arr[j], arr[i]

def quick_sort_hoare(arr, low, high):
    if low < high:
        pi = hoare_partition(arr, low, high)
        quick_sort_hoare(arr, low, pi)
        quick_sort_hoare(arr, pi + 1, high)
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: Average O(N log N). Worst-case O(N^2) (e.g., when the array is already sorted and the pivot is always chosen as the smallest/largest element). This can be mitigated by choosing a random pivot or median-of-three pivot. Space Complexity: O(log N) on average due to recursion stack space. Worst-case O(N) if the partitioning is highly unbalanced.
