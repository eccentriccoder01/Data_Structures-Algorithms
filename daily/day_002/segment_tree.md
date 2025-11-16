# Segment Tree

## 1. Introduction
A segment tree is a tree-based data structure used for storing information about intervals or segments. It allows answering range queries (e.g., sum, minimum, maximum) and point or range updates on an array efficiently. Each node in the segment tree represents an interval, typically a range from the original array. The root node represents the entire array, and its children represent halves of that range.

## 2. When is it used?
Range Minimum Query (RMQ), Range Sum Query (RSQ), Range Max Query, range updates (lazy propagation), competitive programming problems involving array queries and updates.

## 3. ASCII Diagram

```
                 [0, N-1]  (Root)
               /          \
           [0, M]       [M+1, N-1]
           /    \         /      \
      [0, K] [K+1, M] [M+1, L] [L+1, N-1]
      (Leaf nodes represent single elements)
```

## 4. Approaches

### Standard Segment Tree Implementation

A segment tree is typically built recursively. Each node stores the aggregated value for its represented range. For a query, the tree is traversed, and if a node's range fully overlaps with the query range, its value is returned. Otherwise, the query is recursively sent to children, and results are combined. Updates can be point updates (modifying a single element) or range updates. Range updates often employ 'lazy propagation' to defer updates to child nodes until they are needed, which improves efficiency for large range updates.

#### Code Implementations

<details>
<summary><strong>C++</strong></summary>

```cpp
#include <vector>
#include <algorithm>

// Example: Range Sum Query (RSQ) and Point Update
class SegmentTree {
public:
    std::vector<int> tree;
    std::vector<int> arr;
    int n;

    SegmentTree(const std::vector<int>& input_arr) {
        arr = input_arr;
        n = arr.size();
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        }
        else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
        }
        else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            }
            else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // No overlap, return identity for sum (0)
        }
        if (l <= start && end <= r) {
            return tree[node]; // Complete overlap
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node + 1, start, mid, l, r);
        int p2 = query(2 * node + 2, mid + 1, end, l, r);
        return p1 + p2;
    }
};
```

</details>

<details>
<summary><strong>Java</strong></summary>

```java
import java.util.Arrays;

// Example: Range Sum Query (RSQ) and Point Update
public class SegmentTree {
    private int[] tree;
    private int[] arr;
    private int n;

    public SegmentTree(int[] inputArr) {
        this.arr = inputArr;
        this.n = inputArr.length;
        this.tree = new int[4 * n];
        build(0, 0, n - 1);
    }

    private void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    public void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

    private void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    public int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    private int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // No overlap, return identity for sum (0)
        }
        if (l <= start && end <= r) {
            return tree[node]; // Complete overlap
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node + 1, start, mid, l, r);
        int p2 = query(2 * node + 2, mid + 1, end, l, r);
        return p1 + p2;
    }
}
```

</details>

<details>
<summary><strong>Python</strong></summary>

```python
class SegmentTree:
    def __init__(self, arr):
        self.arr = arr
        self.n = len(arr)
        self.tree = [0] * (4 * self.n)
        self._build(0, 0, self.n - 1)

    def _build(self, node, start, end):
        if start == end:
            self.tree[node] = self.arr[start]
        else:
            mid = (start + end) // 2
            self._build(2 * node + 1, start, mid)
            self._build(2 * node + 2, mid + 1, end)
            self.tree[node] = self.tree[2 * node + 1] + self.tree[2 * node + 2]

    def update(self, idx, val):
        self._update(0, 0, self.n - 1, idx, val)

    def _update(self, node, start, end, idx, val):
        if start == end:
            self.arr[idx] = val
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if start <= idx <= mid:
                self._update(2 * node + 1, start, mid, idx, val)
            else:
                self._update(2 * node + 2, mid + 1, end, idx, val)
            self.tree[node] = self.tree[2 * node + 1] + self.tree[2 * node + 2]

    def query(self, l, r):
        return self._query(0, 0, self.n - 1, l, r)

    def _query(self, node, start, end, l, r):
        if r < start or end < l:
            return 0  # No overlap, return identity for sum (0)
        if l <= start and end <= r:
            return self.tree[node]  # Complete overlap
        mid = (start + end) // 2
        p1 = self._query(2 * node + 1, start, mid, l, r)
        p2 = self._query(2 * node + 2, mid + 1, end, l, r)
        return p1 + p2
```

</details>

---

## 5. Time & Space Complexity

Time Complexity: Build O(N), Query O(log N), Update O(log N). Space Complexity: O(N) for the tree array (typically 4N).
