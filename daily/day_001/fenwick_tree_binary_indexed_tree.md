# Fenwick Tree (Binary Indexed Tree)

## 1. Introduction
A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update elements and calculate prefix sums in an array. It achieves logarithmic time complexity for both point updates and range sum queries, making it superior to naive array approaches (O(N) for updates or queries) and segment trees for certain operations.

## 2. When is it used?
Calculating prefix sums in competitive programming, dynamic range sum queries, counting inversions in an array, 2D range sum queries, implementing frequency arrays where elements are updated frequently.

## 3. ASCII Diagram

```
Array A:  [1, 2, 3, 4, 5, 6, 7, 8]
Index:     1  2  3  4  5  6  7  8

Fenwick Tree (BIT) representation:
(Values represent sums of certain ranges, not direct array elements)

BIT:
Index: 1 2 3 4 5 6 7 8
Val:  C1 C2 C3 C4 C5 C6 C7 C8

C1 = A[1]
C2 = A[1] + A[2]
C3 = A[3]
C4 = A[1] + A[2] + A[3] + A[4]
C5 = A[5]
C6 = A[5] + A[6]
C7 = A[7]
C8 = A[1] + A[2] + A[3] + A[4] + A[5] + A[6] + A[7] + A[8]

Visualizing Parent/Child relations (lowbit concept):
_ _ _ _ _ _ _ _
1 2 3 4 5 6 7 8 (Array Index)

1 is covered by 1, 2, 4, 8
2 is covered by 2, 4, 8
3 is covered by 3, 4, 8
4 is covered by 4, 8
5 is covered by 5, 6, 8
6 is covered by 6, 8
7 is covered by 7, 8
8 is covered by 8

Accessing/Updating an index `i` involves indices `i + (i & -i)`, `i + 2*(i & -i)`, etc.
Querying a prefix sum up to `i` involves indices `i - (i & -i)`, `i - 2*(i & -i)`, etc.
```

## 4. Approaches

### Point Update and Prefix Sum Query

A Fenwick Tree uses the concept of 'lowbit' (`i & -i` in binary, which isolates the rightmost set bit) to navigate its structure. For a point update, when an element at index `idx` is modified by `delta`, we need to update all Fenwick tree nodes that cover `idx`. This involves traversing upwards from `idx` by repeatedly adding `lowbit(idx)` to `idx` until it exceeds the tree's size. For a prefix sum query up to `idx`, we sum the values of Fenwick tree nodes that contribute to this range. This involves traversing downwards from `idx` by repeatedly subtracting `lowbit(idx)` from `idx` until `idx` becomes zero. Both operations take logarithmic time because each step of `lowbit` effectively skips a power of 2 sized segment.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>

class FenwickTree {
private:
    std::vector<int> bit;
    int size;

public:
    FenwickTree(int n) : size(n), bit(n + 1, 0) {}

    // Updates the value at index `idx` by `delta`
    void update(int idx, int delta) {
        // Fenwick tree indices are 1-based
        idx++; 
        while (idx <= size) {
            bit[idx] += delta;
            idx += (idx & -idx); // Move to parent
        }
    }

    // Returns the prefix sum from index 0 to `idx` (inclusive)
    int query(int idx) {
        // Fenwick tree indices are 1-based
        idx++; 
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx); // Move to previous relevant node
        }
        return sum;
    }

    // Returns the sum of range [left, right] (inclusive)
    int queryRange(int left, int right) {
        if (left > right) return 0;
        return query(right) - query(left - 1);
    }
};
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
class FenwickTree {
    private int[] bit;
    private int size;

    public FenwickTree(int n) {
        this.size = n;
        this.bit = new int[n + 1]; // 1-based indexing
    }

    // Updates the value at index `idx` by `delta`
    // `idx` is 0-based, convert to 1-based for BIT
    public void update(int idx, int delta) {
        idx++; // Convert to 1-based index
        while (idx <= size) {
            bit[idx] += delta;
            idx += (idx & -idx);
        }
    }

    // Returns the prefix sum from index 0 to `idx` (inclusive)
    // `idx` is 0-based, convert to 1-based for BIT
    public int query(int idx) {
        idx++; // Convert to 1-based index
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    // Returns the sum of range [left, right] (inclusive)
    // `left`, `right` are 0-based indices
    public int queryRange(int left, int right) {
        if (left > right) return 0;
        return query(right) - query(left - 1);
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
class FenwickTree:
    def __init__(self, n):
        self.size = n
        self.bit = [0] * (n + 1) # 1-based indexing

    # Updates the value at index `idx` by `delta`
    # `idx` is 0-based, convert to 1-based for BIT
    def update(self, idx, delta):
        idx += 1 # Convert to 1-based index
        while idx <= self.size:
            self.bit[idx] += delta
            idx += (idx & -idx)

    # Returns the prefix sum from index 0 to `idx` (inclusive)
    # `idx` is 0-based, convert to 1-based for BIT
    def query(self, idx):
        idx += 1 # Convert to 1-based index
        _sum = 0
        while idx > 0:
            _sum += self.bit[idx]
            idx -= (idx & -idx)
        return _sum

    # Returns the sum of range [left, right] (inclusive)
    # `left`, `right` are 0-based indices
    def query_range(self, left, right):
        if left > right: return 0
        return self.query(right) - self.query(left - 1)
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: O(log N) for both `update` and `query` operations, where N is the size of the array. Building the tree from an existing array takes O(N log N) if done by repeated updates, or O(N) using a specialized construction. Space Complexity: O(N) for storing the Fenwick Tree.
